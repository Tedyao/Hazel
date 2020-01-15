#pragma once
#include "glm.hpp"
#include "Hazel/Events/Event.h"
#include "Hazel/Events/KeyEvent.h"
#include "Hazel/Events/MouseEvent.h"
#include "Hazel/Events/ApplicationEvent.h"
#include "Core.h"
#include "Input.h"
#include "HazelKeycode.h"
#include "HazelMouseBottonCode.h"
namespace Hazel {
	class Camera
	{
	public:
		Camera();
		~Camera();
		void onEvent(Event& event);
		glm::mat4 getProjMat();
		glm::mat4 getViewMat();
		bool mouseMoveCallBack(MouseMovedEvent& event);
		bool KeyPressedCallBack(KeyPressedEvent& event);
		bool Camera::mouseScrolledCallBack(MouseScrolledEvent& event);
		
	private:
		float x, y, z;
		float rx, ry, rz;
		float offsetX, offsetY, offsetZ;
		glm::mat4 trans;
		static bool Initialized;

	};
}