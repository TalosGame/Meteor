#include "mtrpch.h"
#include "window.h"
#include "meteor/events/app_event.h"

__MTR_NS_BEGIN__

class MTR_API Application
{
public:
	Application();
	~Application();

	void run();

	void handle_event(Event& e);

private:
	bool handle_window_close(WindowCloseEvent& evt);

private:
	std::unique_ptr<Window> window_;
	bool running_ = true;
};

Application* create_application();

__MTR_NS_END__