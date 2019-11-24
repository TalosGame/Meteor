/*!
 * FileName: 	sandbox_app.cpp
 * Copyright:	TalosGame Studio Co., Ltd
 * Data: 		2019/11/09 13:20
 * Author: 		miller
 * Desc:
 */
 
#include "meteor.h"

__MTR_NS_BEGIN__

class TestLayer : public Layer
{
public:
	TestLayer() 
	{
		
	}

	~TestLayer() = default;

	virtual void update() override
	{

	}

	virtual void handle_event(Event& evt) override 
	{
		if (evt.get_event_type() == EventType::kKeyPressed) 
		{
			auto e = (mtr::KeyPressedEvent&)evt;
			MTR_INFO(e.get_key_code());
		}
	}
};

class Sandbox : public Application
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

Application* create_application() 
{
	return new Sandbox();
}

__MTR_NS_END__
