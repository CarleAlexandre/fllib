#ifndef FLGL_HH
# define FLGL_HH

//GL FOR GAME LIBRARY;
# define VK_NO_PROTOTYPES
# include <vulkan/vulkan.h>
# include <Volk/volk.h>
//# include <GLFW/glfw3.h>

typedef struct s_window {
	int height;
	int width;
	const char *title;
	VkInstance instance;
	VkPhysicalDevice phy_device;
	VkDevice device;
	VkSurfaceKHR surface;
} window_t;

typedef struct s_swapchainsupportdetails {
	VkSurfaceCapabilitiesKHR capabilities;
	uint32_t formatCount;
	VkSurfaceFormatKHR *formats;
	uint32_t presentModesCount;
	VkPresentModeKHR *presentModes;
} swapChainSupportDetails;

typedef struct vec2{
	float x, y;
} vec2;

typedef struct vec3 {
	float x, y, z;
} vec3;

typedef struct mat3{
	float
	m1, m2, m3,
	m4, m5, m6,
	m7, m8, m9;
} mat3;

typedef struct mat4{
	float
	m1,  m2,  m3,  m4,
	m5,  m6,  m7,  m8,
	m9,  m10, m11, m12,
	m13, m14, m15, m16;
} mat4;

window_t *flinitWindow(const int height, const int width, const char *title);
void fldestroyWindow(window_t *window);

#endif
