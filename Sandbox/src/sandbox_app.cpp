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

	virtual void update() override
	{

	}

	virtual void handle_event(mtr::Event& evt) override 
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
		push_layer(new TestLayer());
	}

	~Sandbox()
	{

	}

private:

};

mtr::Application* mtr::create_application() 
{
	return new Sandbox();
}
