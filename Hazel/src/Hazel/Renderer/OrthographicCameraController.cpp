#include "hzpch.h"
#include "Hazel/Renderer/OrthographicCameraController.h"
#include "Hazel/Core/Log.h"
#include "Hazel/Core/Input.h"
#include "Hazel/Core/TimeStep.h"

namespace Hazel {

	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotate = false)
		:m_AspectRatio(aspectRatio), m_Camera(OrthoGraphicCamera(m_AspectRatio * -m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel)),m_Rotate(rotate)
	{

	}

	OrthographicCameraController::~OrthographicCameraController()
	{

	}

	void OrthographicCameraController::onUpdate(TimeStep timestep)
	{
		if (Input::isKeyPressed(HZ_KEY_W))
		{
			m_Camera.setPosition(m_Camera.getPosition().x, m_Camera.getPosition().y + m_CameraMoveSpeed * timestep, m_Camera.getPosition().z);
		}
		if (Input::isKeyPressed(HZ_KEY_S))
		{
			m_Camera.setPosition(m_Camera.getPosition().x, m_Camera.getPosition().y - m_CameraMoveSpeed * timestep, m_Camera.getPosition().z);
		}
		if (Input::isKeyPressed(HZ_KEY_A))
		{
			m_Camera.setPosition(m_Camera.getPosition().x - m_CameraMoveSpeed * timestep, m_Camera.getPosition().y, m_Camera.getPosition().z);
		}
		if (Input::isKeyPressed(HZ_KEY_D))
		{
			m_Camera.setPosition(m_Camera.getPosition().x + m_CameraMoveSpeed * timestep, m_Camera.getPosition().y, m_Camera.getPosition().z);
		}

		if(m_Rotate) 
		{
			if (Input::isKeyPressed(HZ_KEY_Q))
			{
				m_Camera.setZRotate(m_Camera.getZRotaion() + m_CameraRotateSpeed * timestep);
			}

			if (Input::isKeyPressed(HZ_KEY_E))
			{
				m_Camera.setZRotate(m_Camera.getZRotaion() - m_CameraRotateSpeed * timestep);
			}
		}

	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowResizeEvent>(HZ_BIND_EVENT_CALLBACK_FN(OrthographicCameraController::onWindowResizeEvent));
		dispatcher.Dispatch<MouseScrolledEvent>(HZ_BIND_EVENT_CALLBACK_FN(OrthographicCameraController::onMouseScrollEvent));

	}

	bool OrthographicCameraController::onWindowResizeEvent(WindowResizeEvent& event)
	{
		m_AspectRatio = event.getWidth() / event.getHeight();
		m_Camera.setProjectMatrix(m_AspectRatio * -m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	bool OrthographicCameraController::onMouseScrollEvent(MouseScrolledEvent& event)
	{
		m_ZoomLevel -= event.getYOffset() * 20.0f;
		m_Camera.setProjectMatrix(m_AspectRatio * -m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

}