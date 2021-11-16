// Heaven.h: arquivo de inclusão para arquivos de inclusão padrão do sistema,
// ou arquivos de inclusão específicos a um projeto.

#pragma once

//std
#include <iostream>
#include <string>

//Heaven
#include "Window.h"
#include "Pipeline.h"

using namespace std;

namespace Heaven
{
	class Application
	{
	public:
		Application();
		~Application();

		void Run();

		const int WIDTH = 800;
		const int HEIGHT = 600;
		const string WINDOW_TITLE = "Haven Engine";

		Window ApplicationWindow{WIDTH, HEIGHT, WINDOW_TITLE};
		Pipeline ApplicationPipeline{"C:\\Users\\muril\\Documents\\GitHub\\HeavenEngine\\HeavenEngine\\Shaders\\SimpleShader.vert.spv",
									 "C:\\Users\\muril\\Documents\\GitHub\\HeavenEngine\\HeavenEngine\\Shaders\\SimpleShader.frag.spv"};
	};
}
