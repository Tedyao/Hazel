#include "hzpch.h"
#include "Shader.h"
#include "Hazel/Log.h"
#include "Glad/glad.h"
#include "Hazel/Renderer/RendererAPI.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Hazel/Log.h"
namespace Hazel {
	ShaderLibrary* ShaderLibrary::s_Instance = new ShaderLibrary();

	Ref<Shader> Shader::CreateShader(const std::string& filePath)
	{
		RenderAPI api = RendererAPI::API();
		switch (api)
		{
		case Hazel::RenderAPI::None:
			HZ_CORE_ASSERT(false, "None api has not been supported yet!");
			return nullptr;
			break;
		case Hazel::RenderAPI::OpenGL:
			return std::make_shared<OpenGLShader>(filePath);
			break;
		default:
			HZ_CORE_ASSERT(false, "Invalid api!");
			return nullptr;
			break;
		}
	}


	Ref<Shader> Shader::CreateShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		RenderAPI api = RendererAPI::API();
		switch (api)
		{
		case Hazel::RenderAPI::None:
			HZ_CORE_ASSERT(false, "None api has not been supported yet!");
			return nullptr;
			break;
		case Hazel::RenderAPI::OpenGL:
			return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
			break;
		default:
			HZ_CORE_ASSERT(false, "Invalid api!");
			return nullptr;
			break;
		}
	}

	Ref<Shader> Shader::CreateShader(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		RenderAPI api = RendererAPI::API();
		switch (api)
		{
		case Hazel::RenderAPI::None:
			HZ_CORE_ASSERT(false, "None api has not been supported yet!");
			return nullptr;
			break;
		case Hazel::RenderAPI::OpenGL:
			return std::make_shared<OpenGLShader>(vertexSrc, fragmentSrc);
			break;
		default:
			HZ_CORE_ASSERT(false, "Invalid api!");
			return nullptr;
			break;
		}
	}


	void ShaderLibrary::add(const std::string& name, Ref<Shader>& shader)
	{
		if (contains(name))
		{
			HZ_CORE_INFO("Shader: {0} already exists!", name);
			return;
		}
		
		s_Instance->m_Shaders[name] = shader;
	}

	void ShaderLibrary::add(Ref<Shader> shader)
	{
		if (contains(shader->getName()))
		{
			HZ_CORE_INFO("Shader: {0} already exists!", shader->getName());
			return;
		}
		s_Instance->m_Shaders[shader->getName()] = shader;
	}

	Hazel::Ref<Hazel::Shader> ShaderLibrary::load(std::string& shaderPath)
	{
		Ref<Shader> shader = Shader::CreateShader(shaderPath);
		s_Instance->add(shader);
		return shader;
	}

	Hazel::Ref<Hazel::Shader> ShaderLibrary::load(const std::string& name, std::string& shaderPath)
	{
		Ref<Shader> shader = Shader::CreateShader(shaderPath);
		s_Instance->add(name, shader);
		return shader;
	}

	Hazel::Ref<Hazel::Shader> ShaderLibrary::getShader(const std::string& name)
	{
		if (!contains(name))
		{
			HZ_CORE_ASSERT(false, "Can not get access of shader: {0}", name)
		}
		return s_Instance->m_Shaders[name];
	}

	bool ShaderLibrary::contains(const std::string& name)
	{
		return s_Instance->m_Shaders.find(name) != s_Instance->m_Shaders.end();
	}

}
