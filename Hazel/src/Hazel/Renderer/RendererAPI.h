#pragma once
#include "VertexArray.h"
#include "glm.hpp"
namespace Hazel {
	enum class RenderAPI
	{
		None = 0, OpenGL = 1
	};

	class RendererAPI
	{
	public:
		~RendererAPI() = default;
		virtual void Init() = 0;
		virtual void setViewPort(unsigned int x, unsigned int y, unsigned int width, unsigned int height) = 0;
		virtual void clear() = 0;
		virtual void clearColor(const glm::vec4& color) = 0;
		virtual void drawIndexed(const Ref<VertexArray>& vertexArray) = 0;
		static RenderAPI API();
	};
}