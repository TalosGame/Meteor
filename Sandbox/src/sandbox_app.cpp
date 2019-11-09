/*!
 * FileName: 	sandbox_app.cpp
 * Copyright:	TalosGame Studio Co., Ltd
 * Data: 		2019/11/09 13:20
 * Author: 		miller
 * Desc:
 */
 
#include "meteor.h"

__MTR_NS_BEGIN__

class Sandbox : public Application
{
public:
	Sandbox()
	{
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
