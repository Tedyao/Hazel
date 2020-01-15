#include "hzpch.h"

#include "OrthoGraphicCamera.h"

namespace Hazel {

	OrthoGraphicCamera::OrthoGraphicCamera(float left, float right, float bottom, float top)
		:m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(glm::mat4(1.0f)), m_ViewProjectionMatrx(m_ProjectionMatrix * m_ViewMatrix),
		m_Position(0.0F, 0.0F, 0.0F), m_ZRotation(0.0f)
	{

	}

	OrthoGraphicCamera::~OrthoGraphicCamera()
	{

	}

	void OrthoGraphicCamera::setProjectMatrix(float left, float right, float bottom, float top)
	{
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top);
		m_ViewProjectionMatrx = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthoGraphicCamera::calcViewProjectMatrix()
	{
		m_ViewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(m_Position)) *
			glm::rotate(glm::mat4(1.0f), glm::radians(m_ZRotation), glm::vec3(0.0f, 0.0f, 1.0f));
		m_ViewMatrix = glm::inverse(m_ViewMatrix);
		m_ViewProjectionMatrx = m_ProjectionMatrix * m_ViewMatrix;

	}

	bool OrthoGraphicCamera::mouseScrolledCallBack(MouseScrolledEvent& event)
	{
		float xOffset = event.getXOffset();
		float yOffset = event.getYOffset();
		if (Input::isKeyPressed(HZ_KEY_LEFT_ALT))
		{
			setZRotate(m_ZRotation + yOffset);
		}
		return false;
	}

	bool OrthoGraphicCamera::mouseMovedCallBack(MouseMovedEvent& event)
	{
		return false;
	}

	bool OrthoGraphicCamera::keyPressedCallBack(KeyPressedEvent& event)
	{
		int keycode = event.getKeyCode();
		switch (keycode)
		{
		case HZ_KEY_W:
			setPosition(m_Position.x, m_Position.y + 5.0f, m_Position.z);
			break;
		case HZ_KEY_UP:
			setPosition(m_Position.x, m_Position.y + 5.0f, m_Position.z);
			break;
		case HZ_KEY_A:
			setPosition(m_Position.x - 5.0f, m_Position.y, m_Position.z);
			break;
		case HZ_KEY_D:
			setPosition(m_Position.x + 5.0f, m_Position.y, m_Position.z);
			break;
		case HZ_KEY_S:
			setPosition(m_Position.x, m_Position.y - 5.0f, m_Position.z);
			break;
		default:
			break;
		}
		return false;
	}
}