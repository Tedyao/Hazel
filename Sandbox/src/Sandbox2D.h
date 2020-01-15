#pragma once
#include "Hazel.h"
#include "glm.hpp"
#include "gtc/type_ptr.hpp"
#include "imgui/imgui.h"


class Sandbox2D
	:public Hazel::Layer
{
public:
	Sandbox2D();
	~Sandbox2D();
	virtual void onAttach() override;
	virtual void onDetach() override;
	virtual void onUpdate(Hazel::TimeStep time) override;
	virtual void OnImGuiRender() override;
	virtual void onEvent(Hazel::Event& event) override;

private:
	Hazel::Ref<Hazel::VertexArray> m_VertexArray;
	Hazel::Ref<Hazel::OrthographicCameraController> m_CameraController;
	Hazel::Ref<Hazel::Shader> m_FlatColorShader;
	glm::vec4 m_FlatColor = { 0.8f, 0.3f, 0.2f, 1.0f };
	glm::vec2 m_Position = { 0.0f, 0.0f };
	glm::vec2 m_Size = { 200.0f,200.0f };

};
