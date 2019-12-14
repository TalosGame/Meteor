/*!
 * FileName: 	sandbox_app.cpp
 * Copyright:	TalosGame Studio Co., Ltd
 * Data: 		2019/11/09 13:20
 * Author: 		miller
 * Desc:
 */

#include <meteor.h>

class TestLayer : public mtr::Layer
{
public:
	TestLayer() 
	{
		
	}

	~TestLayer() = default;

	virtual void Update() override
	{

	}

	virtual void HandleEvent(mtr::Event& evt) override 
	{
		if (evt.get_event_type() == mtr::EventType::kKeyPressed) 
		{
			auto e = (mtr::KeyPressedEvent&)evt;
			MTR_INFO(e.get_key_code());
		}
	}
};

class Sandbox : public mtr::Application
{
public:
	Sandbox()
	{
		PushLayer(new TestLayer());
	}

	~Sandbox()
	{

	}

private:

};

mtr::Application* mtr::CreateApplication() 
{
	return new Sandbox();
}
