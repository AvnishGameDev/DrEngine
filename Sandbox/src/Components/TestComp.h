#pragma once

#include "DrEngine.h"

class TestComp : public DrEngine::ECS::Component
{
public:

    TestComp(int testno)
    {
        DE_INFO("TestNo: {0}", testno);
        TestCompNo = testno;
    }

    ~TestComp()
    {
        
    }
    
    void BeginPlay() override
    {
        Component::BeginPlay();
    }

    void Update() override
    {
        Component::Update();
    }

    void PrintID()
    {
        DE_INFO("TestComp ID: {0}", TestCompNo);
    }

private:

    int TestCompNo{0};
};
