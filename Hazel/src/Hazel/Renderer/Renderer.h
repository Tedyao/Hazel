#pragma once
#include "RendererAPI.h"
#include "RendererCommand.h"
#include "Shader.h"
#include "OrthoGraphicCamera.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

namespace Hazel {
	struct SceneData
	{
		glm::mat4 viewProjectionMatrix;
	};

	class Renderer
	{
	public:
		static void Init();
		static void setViewPort(unsigned int width, unsigned int height);
		static void beginScene(OrthoGraphicCamera& camera);
		static void endScene();
		static void submit(Ref<Shader>& shader, Ref<VertexArray>& vertexArray, glm::mat4 transform);
	private:
		static Scope<SceneData> data;
	};



}