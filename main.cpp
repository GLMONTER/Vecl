
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


    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;

    //this function gets all of the required vulkan extensions glfw needs to create a window surface.
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;
    createInfo.enabledLayerCount = 0;

    if(vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
        throw std::runtime_error("Vulkan instance failed to create.");
    }
    else
        std::clog<<"Vulkan instance created!"<<std::endl;


    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    std::vector<VkExtensionProperties> extensions(extensionCount);

    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

    std::cout<<"extensions : "<<std::endl;

    for(const auto& extension : extensions)
    {
        std::cout<<extension.extensionName<<std::endl;
    }

}
void initVulkan()
{
    createInstance();
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
