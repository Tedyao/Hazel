#pragma once
#include "Hazel/Renderer/Texture.h"
#include "Hazel/Core.h"
#include "Hazel/Log.h"

namespace Hazel {
	class OpenGLTexture2D :public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D();
		virtual unsigned int getWidth() const override { return m_Width; }
		virtual unsigned int getHeight() const override { return m_Height; }
		virtual void bind(unsigned int slot = 0) override;
	private:
		unsigned int m_Width;
		unsigned int m_Height;
		unsigned int m_RendererID;

	};
}