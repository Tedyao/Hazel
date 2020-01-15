#include "Sandbox2D.h"



Sandbox2D::Sandbox2D()
	:Hazel::Layer("Sandbox2D"), m_CameraController(std::make_shared<Hazel::OrthographicCameraController>(16.0f / 9.0f, true))
{
	onAttach();
}

Sandbox2D::~Sandbox2D()
{
	onDetach();
}

void Sandbox2D::onAttach()
{
	float vertices[] = {
			-100.f, -100.f, 0.5f,
			 100.f, -100.f,	0.5f,
			 100.f,  100.f,	0.5f,
			-100.f,  100.f,	0.5f
	};

	unsigned int indices[] = {
		0, 1, 2,
		0, 2, 3
	};

	Hazel::BufferLayout layout = {
		{ Hazel::ShaderDataType::Float3, "a_Position", false }
	};
	Hazel::Ref<Hazel::VertexBuffer> vertexBuffer;
	Hazel::Ref<Hazel::IndexBuffer> indexBuffer;

	indexBuffer = Hazel::IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int));
	vertexBuffer = Hazel::VertexBuffer::Create(vertices, sizeof(vertices));

	vertexBuffer->setLayout(layout);
	m_VertexArray = Hazel::VertexArray::CreateVertexArray();
	m_VertexArray->addVertexBuffer(vertexBuffer);
	m_VertexArray->setIndexBuffer(indexBuffer);


	m_FlatColorShader = Hazel::Shader::CreateShader("Assets/shaders/flatColor.glsl");
	Hazel::ShaderLibrary::add(m_FlatColorShader);

}

void Sandbox2D::onDetach()
{

}

void Sandbox2D::onUpdate(Hazel::TimeStep time)
{
	m_CameraController->onUpdate(time);
	Hazel::RendererCommand::clearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	Hazel::RendererCommand::clear();

	Hazel::Renderer2D::beginScene(m_CameraController);
	Hazel::Renderer2D::drawQuad(m_Position, m_Size, m_FlatColor);

	Hazel::Renderer::endScene();

}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("ColorPicker");
	ImGui::SliderFloat2("SquarePosition", glm::value_ptr(m_Position), -1000.0f, 1000.0f);
	ImGui::SliderFloat2("SquareSize", glm::value_ptr(m_Size), 5.0f, 1000.0f);
	ImGui::ColorEdit4("SquareColor", glm::value_ptr(m_FlatColor));
	ImGui::End();
}

void Sandbox2D::onEvent(Hazel::Event& event)
{
	m_CameraController->OnEvent(event);
}
