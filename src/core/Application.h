#pragma once

//Third
#include <glm/glm.hpp>

//std
#include <iostream>
#include <string>
#include <cstdlib>
#include <stdexcept>

//Heaven
#include "Window.h"
#include "Vulkan.h"

using namespace std;

namespace Heaven
{
	class Application
	{
	public:
		void run();

		const int WIDTH = 800;
		const int HEIGHT = 600;
		const string WINDOW_TITLE = "Haven Engine";

		Window ApplicationWindow{WIDTH, HEIGHT, WINDOW_TITLE};
	};
}
