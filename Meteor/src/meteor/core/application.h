#include "core.h"
#include "window.h"

__MTR_NS_BEGIN__

class MTR_API Application
{
public:
	Application();
	~Application();

	void run();

private:
	std::unique_ptr<Window> window_;
	bool running_ = true;
};

Application* create_application();

__MTR_NS_END__