#pragma once

#ifdef DE_PLATFORM_WINDOWS

extern DrEngine::Application* DrEngine::CreateApplication();

int main(int argc, char** argv)
{
	DrEngine::Log::Init();
	DE_CORE_WARN("Initialized Log!");
	DE_CORE_INFO("Welcome to DrEngine! Created by AvnishGameDev.");

	auto app = DrEngine::CreateApplication();
	app->Run();
	delete app;
	
	return 0;
}

#endif
