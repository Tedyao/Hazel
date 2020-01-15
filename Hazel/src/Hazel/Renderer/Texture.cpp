#include "hzpch.h"
#include "RendererAPI.h"
#include "Hazel/Core/Log.h"
#include "Texture.h"
#include "Platform/OpenGL/OpenGLTexture2D.h"

namespace Hazel {

	Hazel::Ref<Hazel::Texture2D> Texture2D::Create(const std::string& path)
	{
		RenderAPI api = RendererAPI::API();
		switch (api)
		{
		case RenderAPI::None:
			HZ_CORE_ASSERT(false, "None is not support yet!");
			return nullptr;
		case RenderAPI::OpenGL:
			return std::make_shared<OpenGLTexture2D>(path);
		default:
			HZ_CORE_ASSERT(false, "Invalid api!");
			return nullptr;
		}
	}

}