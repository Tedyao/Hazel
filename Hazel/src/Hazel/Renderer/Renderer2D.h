#pragma once
#include "Hazel/Renderer/VertexArray.h"
#include "Hazel/Renderer/Shader.h"
#include "Hazel/Renderer/RendererCommand.h"
#include "Hazel/Renderer/OrthographicCameraController.h"
#include "Hazel/Renderer/OrthographicCamera.h"
#include "glm.hpp"
#include "gtc/type_ptr.hpp"


namespace Hazel {
	class Renderer2D
	{
	public:
		static void Init();
		static void beginScene(const Ref<OrthographicCameraController>& camera);
		static void endScene();
		static void drawQuad(glm::vec2 position, glm::vec2 size, glm::vec4 color);
		static void drawQuad(glm::vec3 position, glm::vec2 size, glm::vec4 color);
	};
}