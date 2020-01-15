#pragma once
#include "Hazel/Core/Log.h"
#include "Buffer.h"
#include "Buffer.h"
#include "VertexBufferLayout.h"
namespace Hazel {
	class VertexArray
	{
	public:

		virtual void bind() const = 0;
		virtual void unbind() const = 0;
		virtual void addVertexBuffer(Ref<VertexBuffer>& vertexBuffer) = 0;
		virtual void setIndexBuffer(Ref<IndexBuffer>& indexBuffer) = 0;
		virtual const std::vector<Ref<VertexBuffer>> getVertexBuffers() const = 0;
		virtual const Ref<IndexBuffer> getIndexBuffer() const = 0;
		static Ref<VertexArray> CreateVertexArray();

	};
}