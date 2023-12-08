#include "DxFrameWork.h"

int main()
{
	FW::Window window(800, 600, "Example");

	while (window.IsOpen())
	{
		window.SwapBuffers();
		window.PoolEvents();
	}

	FW::Window::Terminate();

	return 0;
}