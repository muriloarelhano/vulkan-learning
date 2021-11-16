#include "Window.h"

namespace Heaven {
	Window::Window(int Width, int Height, string Title) : Width{ Width }, Height{ Height }, WindowTitle{ Title } {
		InitWindow();
	};

	Window::~Window() {
		glfwDestroyWindow(WindowContex);
		glfwTerminate();
	}

	void Window::InitWindow()
	{
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		WindowContex = glfwCreateWindow(Width, Height, WindowTitle.c_str(), nullptr, nullptr);
	}
}