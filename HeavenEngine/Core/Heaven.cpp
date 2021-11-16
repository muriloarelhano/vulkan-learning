// Heaven.cpp: define o ponto de entrada para o aplicativo.
// Includes Heaven
#include "Heaven.h"
#include <glm/glm.hpp>
using namespace Heaven;

// Includes std
#include <iostream>
#include <cstdlib>
#include <stdexcept>

namespace Heaven {
	Application::Application()
	{
	}
	Application::~Application()
	{
	}
	void Heaven::Application::Run()
	{
		while (!ApplicationWindow.ShouldClose()) {
			glfwPollEvents();
		}
	}
}


int main()
{
	cout << "Hello Vulkan!" << endl;
	try {
		Application Application;
		Application.Run();
	}
	catch (const exception& e) {
		cerr << e.what() << endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}


