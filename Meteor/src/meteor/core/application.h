#include "mtrpch.h"
#include "window.h"
#include "meteor/events/app_event.h"
#include "layer_stack.h"

__MTR_NS_BEGIN__

class MTR_API Application
{
public:
	Application();
	~Application() = default;

	Window& get_window() { return *window_; }

	void run();

	void handle_event(Event& e);

	void push_layer(Layer* layer);
	void push_overlay(Layer* layer);

	inline static Application* get_instance();
private:
	bool handle_window_close(WindowCloseEvent& evt);

private:
	std::unique_ptr<Window> window_;
	LayerStack layer_stack_;
	bool running_ = true;
private:
	static Application* instance_;
};

Application* create_application();

__MTR_NS_END__