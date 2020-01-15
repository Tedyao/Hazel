#pragma once
#include "Hazel/Renderer/VertexBufferLayout.h"
#include "vector"
namespace Hazel {
	class OpenGLVertexBufferLayout
		:public VertexBufferLayout
	{
	public:
		OpenGLVertexBufferLayout();
		~OpenGLVertexBufferLayout();
		virtual unsigned int getTypeSize(unsigned int type) const override;
		virtual void addLayoutElement(VertexBufferLayoutElement element);
		inline unsigned int getStride() const override { return m_Stride; }
		inline std::vector<VertexBufferLayoutElement> getElements() const override { return m_Elements; }
	private:
		std::vector<VertexBufferLayoutElement> m_Elements;
		unsigned int m_Stride = 0;
	};
}