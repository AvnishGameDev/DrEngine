#pragma once

#ifdef DE_PLATFORM_WINDOWS

extern DrEngine::Application* DrEngine::CreateApplication();

int main(int argc, char** argv)
{
	DrEngine::Log::Init();
	DE_CORE_WARN("Initialized Log!");
	int a = 69;
	DE_INFO("Hello! Var={0}", a);

	auto app = DrEngine::CreateApplication();
	app->Run();
	delete app;
}

#endif
