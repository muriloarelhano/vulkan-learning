#pragma once
#include "Application.h"

namespace Heaven {

	void Application::run()
	{
		Vulkan vulkanInstance;
		vulkanInstance.createInstance();
		vulkanInstance.setupDebugMessenger();
		vulkanInstance.getPhysicalDevice();
		vulkanInstance.createLogicalDevice();

		while (!ApplicationWindow.shouldClose()) {
			glfwPollEvents();
		}

		vulkanInstance.cleanup();
		ApplicationWindow.~Window();

	}
}


int main()
{
	cout << "Starting Heaven Engine!" << endl;
	try {
		Heaven::Application application;
		application.run();
	}
	catch (const exception& e) {
		cerr << e.what() << endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}


