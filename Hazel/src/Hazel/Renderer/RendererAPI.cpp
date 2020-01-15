#include "hzpch.h"

#include "RendererAPI.h"

namespace Hazel {


	Hazel::RenderAPI RendererAPI::API()
	{
		return RenderAPI::OpenGL;
	}

}