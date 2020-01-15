#pragma once
#include "Hazel/Renderer/OrthoGraphicCamera.h"
#include "glm.hpp"
#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Events/MouseEvent.h"
#include "Hazel/Events/KeyEvent.h"



namespace Hazel {
	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotate);
		~OrthographicCameraController();
		void onUpdate(TimeStep ts);
		void OnEvent(Event& e);
		OrthoGraphicCamera getCamera() { return m_Camera; }
		const OrthoGraphicCamera getCamera() const { return m_Camera; }
		bool onWindowResizeEvent(WindowResizeEvent& event);
		bool onMouseScrollEvent(MouseScrolledEvent& event);

	private:
		float m_AspectRatio;
		float m_ZoomLevel = 360.0f;
		OrthoGraphicCamera m_Camera;
		float m_CameraMoveSpeed = 500.0f;
		float m_CameraRotateSpeed = 180.0f;
		bool m_Rotate;

	
	};


}