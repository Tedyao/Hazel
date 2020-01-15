#pragma once
#include "vector"
namespace Hazel {


	struct VertexBufferLayoutElement
	{
		unsigned int count;
		unsigned int type;
		bool normalized;
	};


	class VertexBufferLayout
	{
	public:
		virtual unsigned int getTypeSize(unsigned int type) const = 0;
		virtual unsigned int getStride() const = 0;
		virtual std::vector<VertexBufferLayoutElement> getElements() const = 0;
		virtual void addLayoutElement(VertexBufferLayoutElement element) = 0;
		static VertexBufferLayout* CreateBufferLayout();
	};
}