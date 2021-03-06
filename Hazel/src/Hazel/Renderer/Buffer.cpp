#include "hzpch.h"
#include "Hazel/Renderer/RendererAPI.h"
#include "Hazel/Renderer/Buffer.h"
#include "Hazel/Core/Log.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Hazel {


	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, unsigned int size)
	{
		RenderAPI api = RendererAPI::API();
		switch (api)
		{
		case RenderAPI::None:
			HZ_CORE_ASSERT(false, "None is not support yet!");
			return nullptr;
		case RenderAPI::OpenGL:
			return std::make_shared<OpenGLVertexBuffer>(vertices, size);
		default:
			HZ_CORE_ASSERT(false, "Invalid api!");
			return nullptr;
		}
	}

	Ref<IndexBuffer> IndexBuffer::Create(unsigned int* indices, unsigned int count)
	{
		RenderAPI api = RendererAPI::API();
		switch (api)
		{
		case RenderAPI::None:
			HZ_CORE_ASSERT(false, "None is not support yet!");
			return nullptr;
		case RenderAPI::OpenGL:
			return std::make_shared<OpenGLIndexBuffer>(indices, count);
		}
	}

}