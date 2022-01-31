#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>
using namespace std;


namespace Heaven
{
	class Window
	{

	public:
		Window(int Width, int Height, string Title);
		~Window();

		Window(const Window &) = delete;
		Window &operator=(const Window &) = delete;

		bool shouldClose() { return glfwWindowShouldClose( windowContex); }

	private:
		void initWindow();

		const int Width;
		const int Height;

		string WindowTitle;
		GLFWwindow * windowContex;
	};
}