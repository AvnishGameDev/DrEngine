#pragma once

#include "Core.h"

namespace DrEngine {

	class DRENGINE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in client
	Application* CreateApplication();

}

