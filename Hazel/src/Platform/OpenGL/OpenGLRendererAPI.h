#pragma once
#include "Hazel/Renderer/RendererAPI.h"


namespace Hazel {
	class OpenGLRenderAPI
		:public RendererAPI
	{
	public:
		OpenGLRenderAPI();
		~OpenGLRenderAPI();
		virtual void Init() override;
		virtual void clear() override;
		virtual void setViewPort(unsigned int x, unsigned int y, unsigned int width, unsigned int height) override;
		virtual void clearColor(const glm::vec4& color) override;
		virtual void drawIndexed(const Ref<VertexArray>& vertexArray) override;
	};
}