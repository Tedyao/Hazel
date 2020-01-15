#include "hzpch.h"
#include "Camera.h"
#include "Hazel/Core/Log.h"
#include "ext/matrix_clip_space.inl"
#include "ext/matrix_transform.inl"
namespace Hazel {

	bool Camera::Initialized;
	Camera::Camera()
		:x(0.0f), y(0.0f), z(0.0f)
	{
		Initialized = false;
		trans = glm::mat4(1.0f);
	}

	Camera::~Camera()
	{

	}

	void Camera::onEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseMovedEvent>(HZ_BIND_EVENT_CALLBACK_FN(Camera::mouseMoveCallBack));
		dispatcher.Dispatch<KeyPressedEvent>(HZ_BIND_EVENT_CALLBACK_FN(Camera::KeyPressedCallBack));

	}

	glm::mat4 Camera::getProjMat()
	{
		return glm::mat4(1.0f);
	}

	glm::mat4 Camera::getViewMat()
	{
		trans = glm::mat4(1.0f);
		trans = glm::translate(trans, glm::vec3(x, y, 0.0f));
		return trans;
	}

	bool Camera::mouseMoveCallBack(MouseMovedEvent& event)
	{
		if (true)
		{
			HZ_CORE_INFO("Camera is moving...");
			//MouseMovedEvent& e = (MouseMovedEvent&)event;
			HZ_CORE_TRACE(event.toString());
			HZ_CORE_INFO("X: {0}, Y: {1}", Input::getMouseX(), Input::getMouseY());
			x = event.getX() - 640.0f;
			y =  - event.getY() + 360.0f;
			
		}
		return false;
	}

	bool Camera::mouseScrolledCallBack(MouseScrolledEvent& event)
	{
		//MouseScrolledEvent& e = (MouseScrolledEvent&)event;
		z += event.getXOffset();
		return false;
	}

	bool Camera::KeyPressedCallBack(KeyPressedEvent& event)
	{
		//KeyPressedEvent& e = (KeyPressedEvent&)event;
		switch (event.getKeyCode())
		{
		case HZ_KEY_UP:
			break;
		case HZ_KEY_LEFT:
			break;
		case HZ_KEY_RIGHT:
			break;
		case HZ_KEY_DOWN:
			break;
		default:
			break;
		}
		return false;



		return false;
	}

}