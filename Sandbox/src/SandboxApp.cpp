#include "DrEngine.h"

class Sandbox : public DrEngine::Application
{
public:
	Sandbox() : DrEngine::Application("Sandbox")
	{
	}

	~Sandbox()
	{

	}
};

DrEngine::Application* DrEngine::CreateApplication()
{
	return new Sandbox();
}