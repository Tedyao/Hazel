#include "hzpch.h"

#include "Renderer.h"

namespace Hazel {
	
	SceneData* Renderer::data = new SceneData();

	void Renderer::Init()
	{
		RendererCommand::Init();
	}

	void Renderer::setViewPort(unsigned int width, unsigned int height)
	{
		RendererCommand::setViewPort(0, 0, width, height);
	}

	void Renderer::beginScene(OrthoGraphicCamera& camera)
	{
		data->viewProjectionMatrix = camera.getViewProjectionMatrix();
	}

	void Renderer::endScene()
	{

	}

	void Renderer::submit(Ref<Shader>& shader, Ref<VertexArray>& vertexArray, glm::mat4 transform)
	{
		shader->bind();
		shader->setUniformMat4f("u_ViewProjectionMatrix", data->viewProjectionMatrix);
		shader->setUniformMat4f("u_TransformMatrix",transform);		
		vertexArray->bind();
		vertexArray->getIndexBuffer()->bind();
		RendererCommand::drawIndexed(vertexArray);
	}

}