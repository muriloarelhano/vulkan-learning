#pragma once
#include "Window.h"

namespace Heaven {
	Window::Window(int Width, int Height, string Title) : Width{ Width }, Height{ Height }, WindowTitle{ Title } {
		initWindow();
	};

	Window::~Window() {
		glfwDestroyWindow(windowContex);
		glfwTerminate();
	}

	void Window::initWindow()
	{
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		windowContex = glfwCreateWindow(Width, Height, WindowTitle.c_str(), nullptr, nullptr);
	}
}