
//this includes <vulkan/vulkan.h> from within the glfw3.h header file.
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>
//for strcmp
#include <cstring>
const int WIDTH = 800;
const int HEIGHT = 600;

const std::vector<const char*> validationLayers =
        {"VK_LAYER_LUNARG_standard_validation"};

#ifdef NDEBUG
    const bool enableValidationLayers = false;
#else
    const bool enableValidationLayers = true;
#endif

GLFWwindow* window;
VkInstance instance;
VkDebugUtilsMessengerEXT debugMessenger;

void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator)
{
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");

    if (func != nullptr)
    {
        func(instance, debugMessenger, pAllocator);
    }
}

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData)
{
    std::cerr<<"validation layer: "<<pCallbackData->pMessage<<std::endl;
    return VK_FALSE;
}

//this function actually creates the messenger with creation info.
VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger)
{
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");

    if (func != nullptr)
    {
        return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
    }
    else
    {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
}

//basically what is says, setup the Debug messenger than create it with a function call to "CreateDebugUtilsMessengerEXT"
void setupDebugMessenger()
{
    //don't waste time calling the rest of the function if validation layers are turned off
    if(!enableValidationLayers) return;

    VkDebugUtilsMessengerCreateInfoEXT createInfo = {};
    //telling vulkan what kind of struct this is.
    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    //specifying the message severities that we would like to be warned about.
    createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    //same as messageSeverity, but with the type of message.
    createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    //giving the messenger a function pointer to our callback function
    createInfo.pfnUserCallback = debugCallback;
    //doesn't have to be here.
    createInfo.pUserData = nullptr;

    if (CreateDebugUtilsMessengerEXT(instance, &createInfo, nullptr, &debugMessenger) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to set up debug messenger!");
    }

}

//this function returns a vector with all of the required extensions we need for the program.
std::vector<const char*> getRequiredExtensions()
{
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;
    //this gets how many extensions glfw needs for vulkan to work with it.
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    //check wtf is happening here
    //now we put the needed glfw vulkan extensions in the vector of extensions
    std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

    //if we are using validation layers, push the validation layer extension in the extension vector.
    if(enableValidationLayers)
    {
        //this pushes back the extension we need for validation layers, it is just a macro with a string.
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }

    return extensions;
}

//this function checks if the layers we want specified in the "validationLayers" vector is actually supported
bool checkValidationLayerSupport()
{
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> avalibleLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, avalibleLayers.data());

    //iterate through the wanted validation layers
    for(const char* layerName : validationLayers)
    {
        bool layerFound = false;

        for(const auto& layerProperties : avalibleLayers)
        {
            //check if layer name in wanted validation layers is found in the supported validation layers.
            //strcmp returns 0 if the strings match.
            if(strcmp(layerName, layerProperties.layerName) == 0)
            {
                layerFound = true;
                break;
            }
        }

        if(!layerFound)
            return false;
    }
    return true;
}

//inits GLFW and makes a window
void initWindow()
{
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
}

//creates a Vulkan instance.
void createInstance()
{
    //if the wanted validation layers are not found and we want to use validation layers, throw a runtime error.
    if(enableValidationLayers && !checkValidationLayerSupport())
        throw std::runtime_error("Requested validation layers are not available.");

    VkApplicationInfo appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Application Name";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    if(enableValidationLayers)
    {
        //cast how many validation layers we want to a 32 bit int because that is what the Vulkan API wants.
        createInfo.enabledLayerCount = static_cast<uint32_t >(validationLayers.size());
        //actually give vulkan the validation layers we want to use.
        createInfo.ppEnabledLayerNames = validationLayers.data();
    }
    else
        createInfo.enabledLayerCount = 0;

    //finally give vulkan the extensions we want to use.
    std::vector<const char*> extensions = getRequiredExtensions();
    createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    createInfo.ppEnabledExtensionNames = extensions.data();

    if(vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
        throw std::runtime_error("Vulkan instance failed to create.");
    }
    else
        std::clog<<"Vulkan instance created!"<<std::endl;
}
void initVulkan()
{
    createInstance();
    setupDebugMessenger();
}

//the main program loop
void mainLoop()
{
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
    }
}

//cleanup when the program exits, (delete vulkan objects and destroy windows)
void cleanup()
{
    if (enableValidationLayers) {
        DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
    }

    vkDestroyInstance(instance, nullptr);

    glfwTerminate();
}

//the program flow
void run()
{
    initWindow();
    initVulkan();
    mainLoop();
    cleanup();
}

//duh
int main()
{
    run();
    return EXIT_SUCCESS;
}
