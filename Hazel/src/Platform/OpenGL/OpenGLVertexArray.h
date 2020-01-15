#pragma once
#include "Hazel/Renderer/VertexArray.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Platform/OpenGL/OpenGLVertexBufferLayout.h"
#include "vector"
#include "memory"

namespace Hazel {
	class OpenGLVertexArray
		:public VertexArray
	{
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();
		virtual void bind() const override;
		virtual void unbind() const override;
		virtual void addVertexBuffer(Ref<VertexBuffer>& vertexBuffer) override;
		virtual void setIndexBuffer(Ref<IndexBuffer>& indexBuffer) override;
		virtual const std::vector<Ref<VertexBuffer>> getVertexBuffers() const override;
		virtual const Ref<IndexBuffer> getIndexBuffer() const override;
	private:
		unsigned int m_RendererID;
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;
	};

}