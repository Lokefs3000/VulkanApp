const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;
const std::string MODEL_PATH = "models/viking_room.obj";
const std::string TEXTURE_PATH = "textures/viking_room.png";

#include <windows.h>

#include "Window.h"

int main(int argc, char* argv[])
{
	try
	{
		system("sh C:/Users/Loke/source/repos/VulkanApp/VulkanApp/shaders/compile.bat");

		Window window(WIDTH, HEIGHT, "Vulkan");

		while (!window.IsClosed()) {
			window.processEvents();
		}

		window.Dispose();
		//EraseAll();
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
		OutputDebugStringA((std::string(ex.what()) + "\n").c_str());

#ifdef _WIN32 
		int feed = MessageBoxA(NULL, ex.what(), "An exception occured!", MB_RETRYCANCEL | MB_ICONERROR);

		switch (feed)
		{
		case IDRETRY:
			//Relaunch app...
			break;
		}
#endif
		//cleanup();
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}