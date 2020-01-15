#include "Hazel.h"
#include "Hazel/Core/EntryPoint.h"
#include "Sandbox2D.h"

class ExampleLayer
	:public Hazel::Layer
{
public:
	ExampleLayer(const std::string& name = "Example Layer")
		:Layer(name), m_CameraController(Hazel::OrthographicCameraController(16.0f / 9.0f, true))
	{

		float vertices[] = {
			-100.f, -100.f, 0.5f, 0.0f, 0.0f,
			 100.f, -100.f, 0.5f, 1.0f, 0.0f,
			 100.f,  100.f, 0.5f, 1.0f, 1.0f,
			-100.f,  100.f, 0.5f, 0.0f, 1.0f
		};

		unsigned int indices[] = {
			0, 1, 2,
			0, 2, 3
		};

		Hazel::BufferLayout layout = {
			{ Hazel::ShaderDataType::Float3, "a_Position", false },
			{ Hazel::ShaderDataType::Float2, "a_TextureCoord", false }
		};
		Hazel::Ref<Hazel::VertexBuffer> vertexBuffer;
		Hazel::Ref<Hazel::IndexBuffer> indexBuffer;

		indexBuffer = Hazel::IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int));
		vertexBuffer = Hazel::VertexBuffer::Create(vertices, sizeof(vertices));

		vertexBuffer->setLayout(layout);
		m_VertexArray = Hazel::VertexArray::CreateVertexArray();
		m_VertexArray->addVertexBuffer(vertexBuffer);
		m_VertexArray->setIndexBuffer(indexBuffer);
	

		std::string TextureVertexSrc = R"(
			#version 330 core
			layout(location = 0) in vec4 a_Position;
			layout(location = 1) in vec2 a_TextureCoord;
			out vec2 v_TextureCoord;
			uniform mat4 u_TransformMatrix;
			uniform mat4 u_ViewProjectionMatrix;
			void main()
			{	
				gl_Position = u_ViewProjectionMatrix * u_TransformMatrix * a_Position;
				v_TextureCoord = a_TextureCoord;
			}
		)";
		std::string TextureFragmentSrc = R"(
			#version 330 core
			layout(location = 0) out vec4 color;
			in vec2 v_TextureCoord;
			uniform sampler2D u_Texture;
			void main()
			{	
				color = texture(u_Texture, v_TextureCoord);
			}
		)";

		m_Texture = Hazel::Texture2D::Create("Assets/textures/Checkerboard.png");
		chernoLogo = Hazel::Texture2D::Create("Assets/textures/ChernoLogo.png");
		m_BirdText = Hazel::Texture2D::Create("Assets/textures/bird.png");
		m_TestShader = Hazel::Shader::CreateShader("Assets/shaders/shader.glsl");
		Hazel::ShaderLibrary::add(m_TestShader);
		m_TextureShader = Hazel::Shader::CreateShader(TextureVertexSrc, TextureFragmentSrc);
		m_Texture->bind();

		m_TextureShader->bind();
		m_TextureShader->setUniform1i("u_Texture", 0);

		m_TestShader->bind();
		m_TestShader->setUniform1i("u_Texture", 0);


		std::string vertexSrc = R"(
			#version 330 core
			layout(location = 0) in vec4 a_Position;
			layout(location = 1) in vec2 a_TextureCoord;
			uniform mat4 u_TransformMatrix;
			uniform mat4 u_ViewProjectionMatrix;
			void main()
			{	
				gl_Position = u_ViewProjectionMatrix * u_TransformMatrix * a_Position;
			}
		)";
		std::string fragmentSrc = R"(
			#version 330 core
			layout(location = 0) out vec4 color;
			uniform vec4 u_Color;
			void main()
			{	
				color = u_Color;
			}
		)";

		m_Shader = Hazel::Shader::CreateShader("flatColorShader", vertexSrc, fragmentSrc);
		Hazel::ShaderLibrary::add(m_Shader);
	}
	~ExampleLayer()
	{

	}

	void OnImGuiRender() override
	{
		ImGui::Begin("ColorPicker");
		ImGui::SliderFloat3("SquarePosition", glm::value_ptr(m_SquarePosition), -50.0F, 50.0f);
		ImGui::ColorEdit3("SquareColor", glm::value_ptr(m_FlatColor));
		ImGui::End();

	}
	void onEvent(Hazel::Event& event) override
	{
		m_CameraController.OnEvent(event);
		if (event.getEventType() == Hazel::EventType::KeyPressed)
		{
			Hazel::KeyPressedEvent& e = (Hazel::KeyPressedEvent&)event;
			HZ_TRACE("key {} is pressed.", (char)e.getKeyCode());
		}
	}

	void onUpdate(Hazel::TimeStep timeStep) override
	{
		m_CameraController.onUpdate(timeStep);
		static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.2f));

		glm::vec4 color = { 0.1f, 0.1f, 0.1f, 1.0f };
		Hazel::RendererCommand::clearColor(color);
		Hazel::RendererCommand::clear();

		Hazel::Renderer::beginScene(m_CameraController.getCamera());

		m_BirdText->bind();
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				if (true) 
					Hazel::ShaderLibrary::getShader("flatColorShader")->setUniform4f("u_Color", m_FlatColor.x, m_FlatColor.y, m_FlatColor.z, 1.0f);
				glm::vec3 position(i * 45, j * 45, 0.0f);
				Hazel::Renderer::submit(Hazel::ShaderLibrary::getShader("flatColorShader"), m_VertexArray, glm::translate(glm::mat4(1.0f), position) * scale);

			}
		}
		m_Texture->bind();
		Hazel::Renderer::submit(m_TextureShader, m_VertexArray, glm::translate(glm::mat4(1.0f), m_SquarePosition) * glm::scale(glm::mat4(1.0f), glm::vec3(2.0f)));

		chernoLogo->bind();
		Hazel::Renderer::submit(m_TextureShader, m_VertexArray, glm::translate(glm::mat4(1.0f), m_SquarePosition) * glm::scale(glm::mat4(1.0f), glm::vec3(2.0f)));
		Hazel::Renderer::endScene();
	}

private:
	Hazel::Ref<Hazel::Shader> m_Shader;
	Hazel::Ref<Hazel::Shader> m_TextureShader;
	Hazel::Ref<Hazel::Shader> m_TestShader;

	Hazel::Ref <Hazel::VertexArray> m_VertexArray;
	Hazel::Ref <Hazel::VertexArray> m_TextureVertexArray;

	Hazel::OrthographicCameraController m_CameraController;
	glm::vec3 m_Position = glm::vec3(0.0f);
	float m_ObjectSpeed = 50.0f;
	glm::vec3 m_FlatColor = glm::vec3(0.8f, 0.3f, 0.2f);
	glm::vec3 m_SquarePosition = glm::vec3(0.0f, 0.0f, 0.0f);

	Hazel::Ref<Hazel::Texture> chernoLogo;
	Hazel::Ref<Hazel::Texture> m_BirdText;
	Hazel::Ref<Hazel::Texture> m_Texture;
};


class SandBox
	:public Hazel::Application
{
public:
	SandBox()
	{
		//pushLayer(new ExampleLayer("layer1"));
		pushLayer(new Sandbox2D());
		
	}
	~SandBox()
	{

	}


private:

	



};

Hazel::Application* Hazel::createApplication()
{
	return new SandBox();
	
}






