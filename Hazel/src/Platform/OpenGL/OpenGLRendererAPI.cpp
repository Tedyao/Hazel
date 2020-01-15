#include "hzpch.h"
#include "OpenGLRendererAPI.h"
#include "Glad/glad.h"

namespace Hazel {

	OpenGLRenderAPI::OpenGLRenderAPI()
	{

	}

	OpenGLRenderAPI::~OpenGLRenderAPI()
	{

	}

	void OpenGLRenderAPI::Init()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void OpenGLRenderAPI::clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRenderAPI::setViewPort(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
	{
		glViewport(x, y, width, height);
	}

	void OpenGLRenderAPI::clearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRenderAPI::drawIndexed(const Ref<VertexArray>& vertexArray)
	{

		glDrawElements(GL_TRIANGLES, vertexArray->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
	}

}