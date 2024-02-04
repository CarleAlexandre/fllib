#ifndef FLGL_HH
# define FLGL_HH

//GL FOR GAME LIBRARY;

# define VK_NO_PROTOTYPES
# include <vulkan/vulkan.h>
# include <GLFW/glfw3.h>
# include <fltype.h>
# include <flvector.hh>
# include <Volk/volk.h>

typedef struct s_window {
	int height;
	int width;
	const char *title;
	VkInstance *instance;
	VkPhysicalDevice phy_device;
	VkDevice *device;
	VkSurfaceKHR *surface;
} window_t;

#endif
