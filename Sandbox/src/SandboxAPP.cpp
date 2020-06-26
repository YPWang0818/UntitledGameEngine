
#include "UGE.h"

UGE::InputHandler& handler = UGE::InputHandler::getInputHandler();

class ExampleLayer : public UGE::Layer
{
public:
	ExampleLayer()
		:Layer("Example"),  m_camera{ -2.56f, 2.56f, -1.44f, 1.44f }
	{
	
		float vertices[3 * 7] = {
				-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
				 0.0f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
				 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f
		};

		float square_vertices[3 * 4] = {
			-0.75f, -0.75f, 0,
			-0.75f,  0.75f, 0,
			 0.75f,  0.75f, 0,
			 0.75f, -0.75f, 0
		};


		UGE::VertexBuffer* vertex_buffer = UGE::VertexBuffer::Create(vertices, sizeof(vertices));
		UGE::VertexBuffer* square_vb = UGE::VertexBuffer::Create(square_vertices, sizeof(square_vertices));;


		UGE::BufferLayout layout = {
				{UGE::ShaderDataType::Float3, "a_position" },
				{UGE::ShaderDataType::Float4, "a_color" }
		};

		UGE::BufferLayout square_layout = {
				{UGE::ShaderDataType::Float3, "a_position" },
		};

		vertex_buffer->setBufferLayout(layout);
		square_vb->setBufferLayout(square_layout);

		int indices[3] = { 0, 1, 2 };
		int square_indices[6] = { 0, 1, 2, 2, 3, 0 };

		UGE::IndexBuffer* index_buffer = UGE::IndexBuffer::Create(indices, 3);
		UGE::IndexBuffer* square_ib = UGE::IndexBuffer::Create(square_indices, 6);


		m_vertex_array.reset(UGE::VertexArray::Create());
		m_vertex_array->AddVertexBuffer(std::shared_ptr<UGE::VertexBuffer>(vertex_buffer));
		m_vertex_array->SetIndexBuffer(std::shared_ptr<UGE::IndexBuffer>(index_buffer));


		m_VAsquare.reset(UGE::VertexArray::Create());
		m_VAsquare->AddVertexBuffer(std::shared_ptr<UGE::VertexBuffer>(square_vb));
		m_VAsquare->SetIndexBuffer(std::shared_ptr<UGE::IndexBuffer>(square_ib));


		UGE::ShaderProgramSource src = UGE::Shader::ParseFile("C:/Dev/UntitledGameEngine/UntitledGameEngine/Resources/Shaders/testshader.shader");
		UGE::ShaderProgramSource blue_src = UGE::Shader::ParseFile("C:/Dev/UntitledGameEngine/UntitledGameEngine/Resources/Shaders/blueshader.shader");

		m_shader.reset(UGE::Shader::Create(src));
		m_blue_shader.reset(UGE::Shader::Create(blue_src));
	
	
	
	
	};

	void onUpdate(UGE::TimeStep ts) override {

		UGE_INFO("TimeStep: {0}, {1}ms", ts.getSecond(), ts.getMillisecond());


		if (handler.isKeyDown(UGE_KEY_UP)) {

			m_camera_position.y += m_camera_speed * ts;

		}else if(handler.isKeyDown(UGE_KEY_DOWN)) {

			m_camera_position.y -= m_camera_speed * ts;
		};

		if (handler.isKeyDown(UGE_KEY_RIGHT)) {

			m_camera_position.x += m_camera_speed * ts;

		}else if(handler.isKeyDown(UGE_KEY_LEFT)) {

			m_camera_position.x -= m_camera_speed * ts;
		};

		if (handler.isKeyDown(UGE_KEY_A)) {

			m_camera_rotation += m_camera_rotation_speed * ts;

		}else if(handler.isKeyDown(UGE_KEY_D)) {

			m_camera_rotation -= m_camera_rotation_speed * ts;
		};


		m_camera.setPosition(m_camera_position);
		m_camera.setRotation(m_camera_rotation);

		UGE::RendererCommand::setClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });
		UGE::RendererCommand::Clear();

		UGE::Renderer::BeginScene(m_camera);
		UGE::Renderer::Submit(m_blue_shader, m_VAsquare);
		UGE::Renderer::Submit(m_shader, m_vertex_array);

		UGE::Renderer::EndScene();

	};

	void onEvent(UGE::Event& e) override {

	};


private:

	std::shared_ptr<UGE::VertexArray> m_vertex_array;
	std::shared_ptr<UGE::VertexArray> m_VAsquare;
	std::shared_ptr<UGE::Shader> m_shader;
	std::shared_ptr<UGE::Shader> m_blue_shader;

	UGE::OrthographicCamera m_camera;

	glm::vec3 m_camera_position = {0, 0, 0};
	float m_camera_speed = 3.0f;
	float m_camera_rotation = 0.0f;
	float m_camera_rotation_speed = 1.0f;
};

class Sandbox : public UGE::Application
{
public:
	Sandbox() {

		PushLayer(new ExampleLayer);
		PushLayer(new UGE::ImguiLayer);

	}
	~Sandbox() {

	}


};

UGE::Application* UGE::createApp()
{

	return new Sandbox();
}