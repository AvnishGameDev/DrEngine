#include "DrEngine.h"

class Sandbox : public DrEngine::Application
{
public:
	Sandbox()
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