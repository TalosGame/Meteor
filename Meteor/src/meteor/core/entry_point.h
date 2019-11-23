/*!
 * FileName: 	entry_point.h
 * Copyright:	TalosGame Studio Co., Ltd
 * Data: 		2019/11/09 13:12
 * Author: 		miller
 * Desc:
 */

#ifdef MTR_PLATFORM_WINDOWS

#include "log.h"

extern mtr::Application* mtr::create_application();

int main(int argc, char** argv)
{
	mtr::Log::init();

	MTR_WARN("Meteor Engine!");

	auto app = mtr::create_application();
	app->run();
	delete app;

	return 0;
}

#endif