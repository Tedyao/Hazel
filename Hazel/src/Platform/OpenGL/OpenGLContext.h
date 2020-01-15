#pragma once
#include <GLFW/glfw3.h>
#include <Glad/glad.h>
#include "Hazel/Core.h"
#include "Hazel/Log.h"
#include "Hazel/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Hazel {
	class OpenGLContext
		:public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);
		~OpenGLContext();
		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;


	};
}
