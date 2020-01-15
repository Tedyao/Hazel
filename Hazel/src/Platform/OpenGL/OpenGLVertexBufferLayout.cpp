#include "hzpch.h"
#include "OpenGLVertexBufferLayout.h"
#include "Glad/glad.h"

namespace Hazel {

	OpenGLVertexBufferLayout::OpenGLVertexBufferLayout()
		:m_Stride (0)
	{

	}

	OpenGLVertexBufferLayout::~OpenGLVertexBufferLayout()
	{

	}

	unsigned int OpenGLVertexBufferLayout::getTypeSize(unsigned int type) const
	{
		switch (type)
		{
		case GL_FLOAT:
			return 4;
			
		case GL_UNSIGNED_INT:
			return 4;
		case GL_UNSIGNED_BYTE:
			return 1;
		default:
			return -1;
			break;
		}
	}
	void OpenGLVertexBufferLayout::addLayoutElement(VertexBufferLayoutElement element)
	{
		m_Elements.emplace_back(element);
		m_Stride += element.count * getTypeSize(element.type);
	}

}