#pragma once

#include "core.h"

__MTR_NS_BEGIN__

class MTR_API Application
{
public:
	Application();
	~Application();

	void run();
};

Application* create_application();

__MTR_NS_END__