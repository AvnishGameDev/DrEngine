#pragma once

#ifdef DE_PLATFORM_WINDOWS

extern DrEngine::Application* DrEngine::CreateApplication();

int main(int argc, char** argv)
{
	auto app = DrEngine::CreateApplication();
	app->Run();
	delete app;
}

#endif
