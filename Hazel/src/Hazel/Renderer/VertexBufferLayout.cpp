#include "hzpch.h"
#include "VertexBufferLayout.h"
#include "Hazel/Renderer/Renderer.h"
#include "Hazel/Core/Log.h"
#include "Platform/OpenGL/OpenGLVertexBufferLayout.h"

namespace Hazel {


	VertexBufferLayout* VertexBufferLayout::CreateBufferLayout()
	{
		RenderAPI api = RendererAPI::API();
		switch (api)
		{
		case Hazel::RenderAPI::None:
			HZ_CORE_ASSERT(false, "None api has not been supported yet!");
			return nullptr;
			break;
		case Hazel::RenderAPI::OpenGL:
			return new OpenGLVertexBufferLayout();
			break;
		default:
			HZ_CORE_ASSERT(false, "Invalid api!");
			return nullptr;
			break;
		}
	}

}