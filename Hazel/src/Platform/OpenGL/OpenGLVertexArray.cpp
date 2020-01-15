#include "hzpch.h"
#include "OpenGLVertexArray.h"
#include "Glad/glad.h"

namespace Hazel {

	static GLuint ToGLShaderType(ShaderDataType type)
	{
		switch (type)
		{
		case Hazel::ShaderDataType::Float:          return GL_FLOAT;
		case Hazel::ShaderDataType::Float2:         return GL_FLOAT;
		case Hazel::ShaderDataType::Float3:			return GL_FLOAT;
		case Hazel::ShaderDataType::Float4:			return GL_FLOAT;
		case Hazel::ShaderDataType::Mat3:			return GL_FLOAT;
		case Hazel::ShaderDataType::Mat4:			return GL_FLOAT;
		case Hazel::ShaderDataType::Int:			return GL_INT;
		case Hazel::ShaderDataType::Int2:			return GL_INT;
		case Hazel::ShaderDataType::Int3:			return GL_INT;
		case Hazel::ShaderDataType::Int4:			return GL_INT;

			HZ_CORE_ASSERT(false, "Unknown ShaderDataType!");
			return 0;
		}
	}


	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::bind() const
	{
		glBindVertexArray(m_RendererID);

	}

	void OpenGLVertexArray::unbind() const
	{
		glBindVertexArray(0);

	}

	void OpenGLVertexArray::addVertexBuffer(Ref<VertexBuffer>& vertexBuffer)
	{
		glBindVertexArray(m_RendererID);
		vertexBuffer->bind();
		glBindVertexArray(m_RendererID);
		BufferLayout layout = vertexBuffer->getLayout();
		HZ_CORE_ASSERT(layout.getElements().size(), "No layout specified in vertexArray!");
		unsigned int index = 0;
		for (BufferElement& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, element.count, ToGLShaderType(element.type),
				element.normalized, layout.getStride(), (const void*)element.offset);
			index++;
		}
		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::setIndexBuffer(Ref<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->bind();
		m_IndexBuffer = indexBuffer;
	}

	const std::vector<Ref<Hazel::VertexBuffer>> OpenGLVertexArray::getVertexBuffers() const
	{
		return m_VertexBuffers;
	}

	const Ref<Hazel::IndexBuffer> OpenGLVertexArray::getIndexBuffer() const
	{
		return m_IndexBuffer;
	}

}