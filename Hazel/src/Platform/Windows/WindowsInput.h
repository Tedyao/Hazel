#pragma once
#include "Hazel/Core/Input.h"

namespace Hazel {
	class HAZEL_API WindowsInput
		:public Input
	{
	public:
	protected:
		virtual bool iskeyPressedImpl(int keyCode) override;
		virtual bool isMouseButtonPressedImpl(int button) override;
		virtual std::pair<float, float> getMousePositionImpl() override;
		virtual float getMouseXImpl() override;
		virtual float getMouseYImpl() override;

	};
}