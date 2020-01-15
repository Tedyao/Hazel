#pragma once
#include "RendererAPI.h"

namespace Hazel {
	class RendererCommand
	{
	public:
		inline static void Init() { s_RenderAPI->Init(); }
		inline static void clear() { s_RenderAPI->clear(); }
		inline static void clearColor(const glm::vec4& color) { s_RenderAPI->clearColor(color); }
		inline static void drawIndexed(const Ref<VertexArray>& vertexArray) { s_RenderAPI->drawIndexed(vertexArray); }
		inline static void setViewPort(unsigned int x, unsigned int y, unsigned int width, unsigned int height) { s_RenderAPI->setViewPort(x, y, width, height);}

		static RendererAPI* s_RenderAPI;
	};
}