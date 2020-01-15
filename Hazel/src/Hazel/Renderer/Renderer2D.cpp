#include "hzpch.h"
#include "Renderer2D.h"

namespace Hazel {

	struct renderer2DStorage
	{
		Ref<VertexArray> vertexArray;
		Ref<Shader> shader;
		glm::mat4 viewProjectionMat;
	};

	static renderer2DStorage* data;

	void Renderer2D::Init()
	{
		data = new renderer2DStorage();
		data->shader = Shader::CreateShader("Assets/shaders/flatColor.glsl");
		float vertices[] = {
			-100.f, -100.f, 0.0f,
			 100.f, -100.f,	0.0f,
			 100.f,  100.f,	0.0f,
			-100.f,  100.f,	0.0f
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

		indexBuffer  = Hazel::IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int));
		vertexBuffer = Hazel::VertexBuffer::Create(vertices, sizeof(vertices));

		vertexBuffer->setLayout(layout);
		data->vertexArray = Hazel::VertexArray::CreateVertexArray();
		data->vertexArray->addVertexBuffer(vertexBuffer);
		data->vertexArray->setIndexBuffer(indexBuffer);

	}

	void Renderer2D::beginScene(const Ref<OrthographicCameraController>& camera)
	{
		data->viewProjectionMat = camera->getCamera().getViewProjectionMatrix();
	}

	void Renderer2D::endScene()
	{

	}

	void Renderer2D::drawQuad(glm::vec2 position, glm::vec2 size, glm::vec4 color)
	{
		drawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::drawQuad(glm::vec3 position, glm::vec2 size, glm::vec4 color)
	{
		data->shader->bind();
		data->shader->setUniform4f("u_Color", color.r, color.g, color.b, color.a);
		data->shader->setUniformMat4f("u_ViewProjectionMatrix", data->viewProjectionMat);
		glm::mat4 transform = glm::mat4(1.0f);
		transform = transform * glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), glm::vec3(size.x / 200.0f, size.y / 200.0f, 1.0f));
		data->shader->setUniformMat4f("u_TransformMatrix", transform);
		data->vertexArray->bind();
		data->vertexArray->getIndexBuffer()->bind();
		RendererCommand::drawIndexed(data->vertexArray);
	}

}