#include "window.h"
#include "meteor/events/app_event.h"
#include "layer_stack.h"
#include "meteor/renderer/shader.h"
#include "meteor/renderer/buffer.h"

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

	inline static Application* get_instance() { return instance_; }
private:
	bool handle_window_close(WindowCloseEvent& evt);

private:
	std::unique_ptr<Window> window_;
	LayerStack layer_stack_;
	bool running_ = true;

	uint32 vertexArray_;

	std::unique_ptr<VertexBuffer> vertex_buffer_;
	std::unique_ptr<IndexBuffer> index_buffer_;

	std::unique_ptr<Shader> shader_;
private:
	static Application* instance_;
};

Application* create_application();

__MTR_NS_END__