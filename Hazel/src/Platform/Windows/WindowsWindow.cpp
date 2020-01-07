#pragma once
#include "hzpch.h"
#include "WindowsWindow.h"

namespace Hazel {

	static bool isGLFWInitilized = false;
	static void GLFWErrorCallBack(int error, const char* errMsg)
	{
		HZ_CORE_ERROR("GLFW Error: {0}", error);
		HZ_CORE_ERROR(errMsg);
	}
	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		shutDown();
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::setVSync(bool enabled)
	{
		m_Data.vSync = enabled;
		if (enabled)
		{
			glfwSwapInterval(1);
		}
		else
		{
			glfwSwapInterval(0);
		}
	}

	bool WindowsWindow::isVSysn() const
	{
		return m_Data.vSync;
	}

	void* WindowsWindow::getNativeWindow() const
	{
		return m_Window;
	}

	void WindowsWindow::Init(const WindowProps props)
	{
		m_Data.Height = props.Height;
		m_Data.Width = props.Width;
		m_Data.Title = props.Title;
		
		if (!isGLFWInitilized)
		{
			//TODO: glfwTerminated on system shutdown
			int success = glfwInit();
			HZ_CORE_ASSERT(success, "Could not initialize glfw window");
			glfwSetErrorCallback(GLFWErrorCallBack);
			isGLFWInitilized = true;
		}
		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);


		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HZ_CORE_ASSERT(status, "Failed to initialize glad.");
		glfwSetWindowUserPointer(m_Window, &m_Data);
		setVSync(true);

		HZ_CORE_INFO("Creating Hazel Engine Window: {0} by {1}", m_Data.Width, m_Data.Height);

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) 
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.Width = width;
				data.Height = height;
				WindowResizeEvent event(width, height);
				data.EventCallback(event);
			});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event = WindowCloseEvent();
				data.EventCallback(event);
				//glfwDestroyWindow(window);
			});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				switch (action)
				{
					case GLFW_PRESS:
					{
						KeyPressedEvent event(key, 0);
						WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
						data.EventCallback(event);
						break;
					}

					case GLFW_REPEAT:
					{
						KeyPressedEvent event(key, 1);
						WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
						data.EventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						KeyReleasedEvent event = KeyReleasedEvent(key);
						WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
						data.EventCallback(event);
						break;
					}

					default:
						break;
				}
			});


		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				KeyTypedEvent event(keycode);
				data.EventCallback(event);
			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				//remember to write BREAK; at the end of every option!!!!!!!!!!!!!!

				switch (action)
				{
					case GLFW_PRESS:
					{
						MouseButtonPressedEvent event(button);
						data.EventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						MouseButtonReleasedEvent event(button);
						data.EventCallback(event);
						break;
					}
					default:
						break;
				}

			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				data.EventCallback(event);

			});
		
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				MouseMovedEvent event((float)xpos, (float)ypos);
				data.EventCallback(event);
			});


		
	
	}

	void WindowsWindow::shutDown()
	{
		glfwDestroyWindow(m_Window);
	}

}
