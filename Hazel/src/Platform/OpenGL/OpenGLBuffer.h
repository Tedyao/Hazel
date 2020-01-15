#pragma once
#include "Hazel/Renderer/Buffer.h"

namespace Hazel {
	class OpenGLVertexBuffer
		:public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, unsigned int size);
		virtual ~OpenGLVertexBuffer();
		virtual void bind() const override;
		virtual void unbind() const override;
	private:
		unsigned int m_RenderID;
	};

	class OpenGLIndexBuffer
		:public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(unsigned* indices, unsigned int count);
		virtual ~OpenGLIndexBuffer();
		virtual void bind() const override;
		virtual void unbind() const override;
		virtual unsigned int getCount() const override;
	private:
		unsigned int m_Count;
		unsigned int m_RenderID;
	};
}