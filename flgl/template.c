#include "include/flgl.h"

int main () {
	window_t *window;
	int shouldClose = 0;

	window = flinitWindow(4480, 720, "game");

	while (!shouldClose) {

	}
	fldestroyWindow(window);
	return (0);
}
