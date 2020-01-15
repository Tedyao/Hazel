#pragma once

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "Hazel/Events/Event.h"
#include "Hazel/Events/KeyEvent.h"
#include "Hazel/Events/MouseEvent.h"
#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Core/Core.h"
#include "Hazel/Core/Input.h"
#include "Hazel/Core/HazelKeycode.h"
#include "Hazel/Core/HazelMouseBottonCode.h"
#include "Hazel/Core/TimeStep.h"

namespace Hazel {
	class OrthoGraphicCamera
	{
	public:
		OrthoGraphicCamera(float left, float right, float bottom, float top);
		~OrthoGraphicCamera();

		void setPosition(float x, float y, float z) { m_Position = { x, y, z }; calcViewProjectMatrix(); }

		void setZRotate(float r) { m_ZRotation = r; calcViewProjectMatrix(); }

		void setProjectMatrix(float left, float right, float bottom, float top);
		

		glm::vec3 getPosition() const { return m_Position; }
		float getZRotaion() const { return m_ZRotation; }
		glm::mat4 getProjectionMatrix() const { return m_ProjectionMatrix; }
		glm::mat4 getViewMatrix() const { return m_ViewMatrix; }
		glm::mat4 getViewProjectionMatrix() const { return m_ViewProjectionMatrx; }

	private:
		void calcViewProjectMatrix();

		bool mouseScrolledCallBack(MouseScrolledEvent& event);
		bool mouseMovedCallBack(MouseMovedEvent& event);
		bool keyPressedCallBack(KeyPressedEvent& event);
	

	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrx;

		glm::vec3 m_Position;
		float m_ZRotation;

	};

}