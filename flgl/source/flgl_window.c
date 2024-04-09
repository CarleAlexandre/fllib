# include <stddef.h>
# include <stdint.h>
# include <stdbool.h>
# include <stdlib.h>
# include "../include/flgl.h"

inline
VkInstance createInstance(
	const char *app_name
) {
	VkInstance instance;

	// only one layer used for now maybe if later not changed, use const char **layers instead of fl::vec<const char *>
	const char *layers[1] = {
		"VK_LAYER_KHRONOS_validation"
	};

	const char *exts[4] = {
		"VK_KHR_surface",
		#if defined (_WIN32)
		"VK_KHR_win32_surface",
		#endif
		#if defined (__APPLE__)
		"VK_MVK_macos_surface",
		#elif defined (__linux__)
		"VK_KHR_xcb_surface",
		#endif
		VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
		VK_EXT_DEBUG_REPORT_EXTENSION_NAME
	};

	const VkApplicationInfo app_info = {
		.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
		.pNext = 0x00,
		.pApplicationName = app_name,
		.applicationVersion = VK_MAKE_VERSION(1, 0, 0),
		.pEngineName = "NoHeavenEngine",
		.engineVersion = VK_MAKE_VERSION(1, 0, 0),
		.apiVersion = VK_API_VERSION_1_3
	};

	const VkInstanceCreateInfo create_info = {
		.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
		.pNext = 0x00,
		.flags = 0,
		.pApplicationInfo = &app_info,
		.enabledLayerCount = 1,
		.ppEnabledLayerNames = layers,
		.enabledExtensionCount = 4,
		.ppEnabledExtensionNames = exts,
	};

	if (vkCreateInstance(&create_info, NULL, &instance) != VK_SUCCESS) {
		return (0x00);
	}

	return (instance);
}

inline
VkResult findSuitablePhysicalDevice(
	VkInstance instance,
	int (*selector)(VkPhysicalDevice),
	VkPhysicalDevice physicalDevice
) {
	uint32_t deviceCount = 0;
	if (vkEnumeratePhysicalDevices(instance, &deviceCount, 0x00)) {
		return (VK_ERROR_INITIALIZATION_FAILED);
	}
	if (!deviceCount) {
		return(VK_ERROR_INITIALIZATION_FAILED);
	}
	VkPhysicalDevice devices[deviceCount];

	if (vkEnumeratePhysicalDevices(instance, &deviceCount, devices)) {
		return (VK_ERROR_INITIALIZATION_FAILED);
	}
	for (uint32_t i = 0; i < deviceCount; i++) {
		if (selector(devices[i])) {
			physicalDevice = devices[i];
			return (VK_SUCCESS);
		}
	}

	return (VK_ERROR_INITIALIZATION_FAILED);
}

inline
uint32_t findQueueFamily(
	VkPhysicalDevice device,
	VkQueueFlags desiredFlags
){
	uint32_t familyCount;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &familyCount, 0x00);
	VkQueueFamilyProperties families[familyCount];
	vkGetPhysicalDeviceQueueFamilyProperties(device, &familyCount, families);

	for (uint32_t i = 0; i < familyCount; i++) {
		if (families[i].queueCount && (families[i].queueFlags & desiredFlags)) {
			return i;
		}
	}
	return (0);
}

inline
VkResult createDevice(
	VkPhysicalDevice physical_device,
	VkPhysicalDeviceFeatures device_features,
	uint32_t graphic_family,
	VkDevice device
) {
	const char *extension = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME,
	};
	const float queuePriority = 1.0f;

	const VkDeviceQueueCreateInfo queue_create_info = {
		.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
		.pNext = 0x00,
		.flags = 0,
		.queueFamilyIndex = graphic_family,
		.queueCount = 1,
		.pQueuePriorities = &queuePriority,
	};

	const VkDeviceCreateInfo create_info = {
		.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
		.pNext = 0x00,
		.flags = 0,
		.queueCreateInfoCount = 1,
		.pQueueCreateInfos = &queue_create_info,
		.enabledLayerCount = 0,
		.ppEnabledLayerNames = 0x00,
		.enabledExtensionCount = 1,
		.ppEnabledExtensionNames = &extension,
		.pEnabledFeatures = &device_features,
	};

	if (vkCreateDevice(physical_device, &create_info, NULL, &device)) {
		return (VK_ERROR_OUT_OF_DEVICE_MEMORY);
	}

	return (VK_SUCCESS);
}

inline
int selectDevice(VkPhysicalDevice device) {
	if (device) {
		return (1);
	}
	return (0);
}

inline
swapChainSupportDetails querySwapchainSupport(
	VkPhysicalDevice device,
	VkSurfaceKHR surface
){
	swapChainSupportDetails details;
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(
		device, surface, &details.capabilities);

	vkGetPhysicalDeviceSurfaceFormatsKHR(
		device, surface, &details.formatCount, 0x00);
	if (details.formatCount) {
		details.formats = malloc(
			sizeof(VkSurfaceFormatKHR) * details.formatCount);//need to free size in win destroy
		vkGetPhysicalDeviceSurfaceFormatsKHR(
			device, surface, &details.formatCount, details.formats);
	} else {
		return (details);
	}

	vkGetPhysicalDeviceSurfacePresentModesKHR(
		device, surface, &details.presentModesCount, 0x00);
	if (details.presentModesCount) {
		details.presentModes = malloc(
			sizeof(VkPresentModeKHR) * details.presentModesCount);
		vkGetPhysicalDeviceSurfacePresentModesKHR(
			device, surface, &details.presentModesCount, details.presentModes);
	} else {
		free(details.formats);
		return (details);
	}
	return (details);
}

inline
VkSurfaceFormatKHR chooseSwapSurfaceFormat(
	const VkSurfaceFormatKHR *availableFormats
){
	(void)availableFormats;
	return ((VkSurfaceFormatKHR){
		VK_FORMAT_B8G8R8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR
	});
}

inline
VkPresentModeKHR chooseSwapPresentMode(
	const VkPresentModeKHR *availablePresentModes,
	const uint32_t presentModeCount
){
	(void)availablePresentModes;
	for (uint32_t i = 0; i < presentModeCount; i++) {
		if (availablePresentModes[i] == VK_PRESENT_MODE_MAILBOX_KHR)
			return (availablePresentModes[i]);
	}
	return (VK_PRESENT_MODE_FIFO_KHR);
}

//returned pointer is unsafe, don't free it yourself, call the destroy window function
window_t *flinitWindow(
	const int height,
	const int width,
	const char *title
) {
	if (volkInitialize() != VK_SUCCESS) {
		return (0x00);
	};
	window_t *window = malloc(sizeof(window_t));
	window->height = height;
	window->width = width;
	window->title = title;

	window->instance = createInstance(title);
	volkLoadInstance(window->instance);

	findSuitablePhysicalDevice(
		window->instance, selectDevice, window->phy_device);

	VkPhysicalDeviceFeatures deviceFeatures = {};
	if (createDevice(window->phy_device, deviceFeatures, findQueueFamily(
			window->phy_device, VK_QUEUE_GRAPHICS_BIT), window->device)) {
		return (0x00);
	}
	return (window);
}


void fldestroyWindow(window_t *window) {
	free(window);
}
