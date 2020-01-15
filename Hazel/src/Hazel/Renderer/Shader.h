#pragma once
#include "string"
#include "glm.hpp"
#include "Hazel/Core.h"
namespace Hazel {
	class Shader
	{
	public:
		virtual void bind() const = 0;
		virtual void unbind() const = 0;
		virtual int getUniform(const std::string& name) = 0;
		virtual void setUniform1i(const std::string& name, int value) = 0;
		virtual void setUniform1f(const std::string& name, float value) = 0;
		virtual void setUniform2f(const std::string& name, float v0, float v1) = 0;
		virtual void setUniformMat4f(const std::string& name, const float* matrix) = 0;
		virtual void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3) = 0;
		virtual void setUniformMat4f(const std::string& name, const glm::mat4& matrix) = 0;
		virtual std::string getName() const = 0;

		static Ref<Shader> CreateShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		static Ref<Shader> CreateShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		static Ref<Shader> CreateShader(const std::string& filePath);

	};

	class ShaderLibrary
	{
	public:
		static void add(const std::string& name, Ref<Shader>& shader);
		static void add(Ref<Shader> shader);
		static Ref<Shader> load(std::string& shaderPath);
		static Ref<Shader> load(const std::string& name, std::string& shaderPath);
		static Ref<Shader> getShader(const std::string& name);

		static bool contains(const std::string& name);

	private:
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;
		static ShaderLibrary* s_Instance;

	};
}
