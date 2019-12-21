#include "window.h"
#include "meteor/events/app_event.h"
#include "layer_stack.h"
#include "meteor/renderer/shader.h"
#include "meteor/renderer/buffer.h"
#include "meteor/renderer/vertex_array.h"
#include "meteor/renderer/orthographic_camera.h"

__MTR_NS_BEGIN__

class MTR_API Application
{
public:
	Application();
	~Application() = default;

	Window& GetWindow() { return *window_; }

	void Run();

	void HandleEvent(Event& e);

	void PushLayer(Layer* layer);
	void PushOverlay(Layer* layer);

	inline static Application* get_instance() { return instance_; }
private:
	bool HandleWindowClose(WindowCloseEvent& evt);

private:
	std::unique_ptr<Window> window_;
	LayerStack layer_stack_;
	bool running_ = true;

	OrthographicCamera camera_;

	std::shared_ptr<VertexArray> vertex_array_;
	std::shared_ptr<Shader> shader_;
private:
	static Application* instance_;
};

Application* CreateApplication();

__MTR_NS_END__