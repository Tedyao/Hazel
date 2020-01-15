#pragma once
#include "Hazel/Core/Log.h"

namespace Hazel {

	enum class ShaderDataType
	{
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4
	};

	static unsigned int getShadeDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
			case Hazel::ShaderDataType::Float:          return 4 * 1;
			case Hazel::ShaderDataType::Float2:         return 4 * 2;
			case Hazel::ShaderDataType::Float3:			return 4 * 3;
			case Hazel::ShaderDataType::Float4:			return 4 * 4;
			case Hazel::ShaderDataType::Mat3:			return 4 * 3 * 3;	
			case Hazel::ShaderDataType::Mat4:			return 4 * 4 * 4;			
			case Hazel::ShaderDataType::Int:			return 4 * 1;			
			case Hazel::ShaderDataType::Int2:			return 4 * 2;
			case Hazel::ShaderDataType::Int3:			return 4 * 3;
			case Hazel::ShaderDataType::Int4:			return 4 * 4;
			
			HZ_CORE_ASSERT(false, "Unknown ShaderDataType!");
			return 0;
		}
	}

	static unsigned int getShadeDataTypeCount(ShaderDataType type)
	{
		switch (type)
		{
		case Hazel::ShaderDataType::Float:          return 1;
		case Hazel::ShaderDataType::Float2:         return 2;
		case Hazel::ShaderDataType::Float3:			return 3;
		case Hazel::ShaderDataType::Float4:			return 4;
		case Hazel::ShaderDataType::Mat3:			return 3 * 3;
		case Hazel::ShaderDataType::Mat4:			return 4 * 4;
		case Hazel::ShaderDataType::Int:			return 1;
		case Hazel::ShaderDataType::Int2:			return 2;
		case Hazel::ShaderDataType::Int3:			return 3;
		case Hazel::ShaderDataType::Int4:			return 4;

		HZ_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
		}
	}

	struct BufferElement
	{
		ShaderDataType type;
		std::string name;
		unsigned int size;
		unsigned int count;
		unsigned int offset;
		bool normalized;
		BufferElement() {}
		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			:type(type), name(name), count(getShadeDataTypeCount(type)), size(getShadeDataTypeSize(type)), offset(0), normalized(normalized)
		{

		}

	};

	class BufferLayout
	{
	public:
		BufferLayout() {}
		BufferLayout(const std::initializer_list<BufferElement>& elements)
			:m_Elements(elements), m_Stride(0)
		{
			unsigned int offset = 0;
			for (BufferElement& element: this->m_Elements)
			{
				element.offset = offset;
				offset += element.size;
				m_Stride += element.size;
			}
		}

		inline unsigned int getStride() const { return m_Stride; }
		inline const std::vector<BufferElement>& getElements() const { return m_Elements; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }

		/*const std::vector<BufferElement>::const_iterator begin() { return m_Elements.begin(); }
		const std::vector<BufferElement>::const_iterator end() { return m_Elements.end(); }*/

	private:
		std::vector<BufferElement> m_Elements;
		unsigned int m_Stride;
	};


	class VertexBuffer
	{
	public:
		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		static VertexBuffer* Create(float* vertices, unsigned int size);
		inline void setLayout(BufferLayout layout) { m_Layout = layout; }
		inline const BufferLayout& getLayout() { return m_Layout; }

	private:
		BufferLayout m_Layout;
	};

	class IndexBuffer
	{
	public:
		virtual unsigned int getCount() const = 0;
		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		static IndexBuffer* Create(unsigned int* indices, unsigned int count);

	
	};
}
