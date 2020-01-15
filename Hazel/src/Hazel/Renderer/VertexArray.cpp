#include "hzpch.h"
#include "VertexArray.h"
#include "Hazel/Renderer/RendererAPI.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Hazel {



	Hazel::VertexArray* VertexArray::CreateVertexArray()
	{
		RenderAPI api = RendererAPI::API();
		switch (api)
		{
		case Hazel::RenderAPI::None:
			HZ_CORE_ASSERT(false, "None api has not been supported yet!");
			return nullptr;
			break;
		case Hazel::RenderAPI::OpenGL:
			return new OpenGLVertexArray();
			break;
		default:
			HZ_CORE_ASSERT(false, "Invalid api!");
			return nullptr;
			break;
		}
	}

}