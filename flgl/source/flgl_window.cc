# include "../include/flgl.hh"

VkInstance *createInstance(
	const char *app_name
) {
	VkInstance *instance = new VkInstance;

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
		.pNext = NULLPTR,
		.pApplicationName = app_name,
		.applicationVersion = VK_MAKE_VERSION(1, 0, 0),
		.pEngineName = "NoHeavenEngine",
		.engineVersion = VK_MAKE_VERSION(1, 0, 0),
		.apiVersion = VK_API_VERSION_1_3
	};

	const VkInstanceCreateInfo create_info = {
		.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
		.pNext = NULLPTR,
		.flags = 0,
		.pApplicationInfo = &app_info,
		.enabledLayerCount = 1,
		.ppEnabledLayerNames = layers,
		.enabledExtensionCount = 4,
		.ppEnabledExtensionNames = exts,
	};

	if (vkCreateInstance(&create_info, NULL, instance) != VK_SUCCESS) {
		delete instance;
		return (NULLPTR);
	}

	return (instance);
}

VkResult findSuitablePhysicalDevice(
	VkInstance instance,
	bool (*selector)(VkPhysicalDevice),
	VkPhysicalDevice *physicalDevice
) {
	uint32_t deviceCount = 0;
	if (vkEnumeratePhysicalDevices(instance, &deviceCount, NULLPTR)) {
		return (VK_ERROR_INITIALIZATION_FAILED);
	}
	if (!deviceCount) {
		return(VK_ERROR_INITIALIZATION_FAILED);
	}
	VkPhysicalDevice devices[deviceCount];

	if (vkEnumeratePhysicalDevices(instance, &deviceCount, devices)) {
		return (VK_ERROR_INITIALIZATION_FAILED);
	}
	for (const auto& device : devices) {
		if (selector(device)) {
			*physicalDevice = device;
			return (VK_SUCCESS);
		}
	}

	return (VK_ERROR_INITIALIZATION_FAILED);
}

uint32_t findQueueFamily(
	VkPhysicalDevice device,
	VkQueueFlags desiredFlags
){
	uint32_t familyCount;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &familyCount, NULLPTR);
	VkQueueFamilyProperties families[familyCount];
	vkGetPhysicalDeviceQueueFamilyProperties(device, &familyCount, families);

	for (uint32_t i = 0; i < familyCount; i++) {
		if (families[i].queueCount && (families[i].queueFlags & desiredFlags)) {
			return i;
		}
	}
	return (0);
}

VkResult createDevice(
	VkPhysicalDevice physical_device,
	VkPhysicalDeviceFeatures device_features,
	u32 graphic_family,
	VkDevice *device
) {
	device = new VkDevice;
	const char *extension = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME,
	};
	const float queuePriority = 1.0f;

	const VkDeviceQueueCreateInfo queue_create_info = {
		.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
		.pNext = NULLPTR,
		.flags = 0,
		.queueFamilyIndex = graphic_family,
		.queueCount = 1,
		.pQueuePriorities = &queuePriority,
	};

	const VkDeviceCreateInfo create_info = {
		.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
		.pNext = NULLPTR,
		.flags = 0,
		.queueCreateInfoCount = 1,
		.pQueueCreateInfos = &queue_create_info,
		.enabledLayerCount = 0,
		.ppEnabledLayerNames = NULLPTR,
		.enabledExtensionCount = 1,
		.ppEnabledExtensionNames = &extension,
		.pEnabledFeatures = &device_features,
	};

	if (vkCreateDevice(physical_device, &create_info, NULL, device)) {
		delete device;
		return (VK_ERROR_OUT_OF_DEVICE_MEMORY);
	}

	return (VK_SUCCESS);
}

bool selectDevice(VkPhysicalDevice device) {
	if (device) {
		return (true);
	}
	return (false);
}

window_t *initWindow(
	const int height,
	const int width,
	const char *title
) {
	if (volkInitialize() != VK_SUCCESS) {
		return (NULLPTR);
	};

	window_t *window = new window_t;
	window->height = height;
	window->width = width;
	window->title = title;

	window->instance = createInstance(title);
	volkLoadInstance(*window->instance);

	findSuitablePhysicalDevice(*window->instance, selectDevice, &window->phy_device);

	VkPhysicalDeviceFeatures deviceFeatures = {};
	createDevice(window->phy_device, deviceFeatures, findQueueFamily(window->phy_device, VK_QUEUE_GRAPHICS_BIT), window->device);
	return (window);
}
