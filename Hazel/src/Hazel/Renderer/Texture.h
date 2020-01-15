#pragma once
#include "Hazel/Core.h"
namespace Hazel {
	class Texture
	{
	public:
		~Texture() = default;
		virtual unsigned int getWidth() const = 0;
		virtual unsigned int getHeight() const = 0;
		virtual void bind(unsigned int slot = 0) = 0;

	};

	class Texture2D :public Texture
	{
	public:
		static Ref<Texture2D> Create(const std::string& path);

	};
}