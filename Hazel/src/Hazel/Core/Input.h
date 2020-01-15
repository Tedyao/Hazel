#pragma once
#include "Core.h"

namespace Hazel {
	class HAZEL_API Input
	{
	public:
		inline static bool isKeyPressed(int keyCode) { return s_Instance->iskeyPressedImpl(keyCode); }
		inline static bool isMouseButtonPressed(int button) { return s_Instance->isMouseButtonPressedImpl(button); }
		inline static std::pair<float, float> getMousePosition() { return s_Instance->getMousePositionImpl(); }
		inline static float getMouseX() { return s_Instance->getMouseXImpl(); }
		inline static float getMouseY() { return s_Instance->getMouseYImpl(); }
		static void Init();

	private:
	protected:
		static Input* s_Instance; 
		virtual bool iskeyPressedImpl(int keyCode) = 0;
		virtual bool isMouseButtonPressedImpl(int button) = 0;
		virtual std::pair<float, float> getMousePositionImpl() = 0;
		virtual float getMouseXImpl() = 0;
		virtual float getMouseYImpl() = 0;

	};
}