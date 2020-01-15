#include "hzpch.h"
#include "RendererAPI.h"
#include "Buffer.h"
#include "Hazel/Log.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Hazel {


	Hazel::VertexBuffer* VertexBuffer::Create(float* vertices, unsigned int size)
	{
		RenderAPI api = RendererAPI::API();
		switch (api)
		{
		case RenderAPI::None:
			HZ_CORE_ASSERT(false, "None is not support yet!");
			return nullptr;
		case RenderAPI::OpenGL:
			return new OpenGLVertexBuffer(vertices, size);
		default:
			HZ_CORE_ASSERT(false, "Invalid api!");
			return nullptr;
		}
	}

	Hazel::IndexBuffer* IndexBuffer::Create(unsigned int* indices, unsigned int count)
	{
		RenderAPI api = RendererAPI::API();
		switch (api)
		{
		case RenderAPI::None:
			HZ_CORE_ASSERT(false, "None is not support yet!");
			return nullptr;
		case RenderAPI::OpenGL:
			return new OpenGLIndexBuffer(indices, count);
		}
	}

}