#pragma once

#include "Hazel/Renderer/Shader.h"
#include "string"


namespace Hazel {

	class OpenGLShader
		:public Shader
	{
	public:
		OpenGLShader(const std::string& filePath);
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();
		virtual void bind() const override;
		virtual void unbind() const override;

		virtual int getUniform(const std::string& name) override;
		virtual void setUniform1i(const std::string& name, int value) override;
		virtual void setUniform1f(const std::string& name, float value) override;
		virtual void setUniform2f(const std::string& name, float v0, float v1) override;
		virtual void setUniformMat4f(const std::string& name, const float* matrix) override;
		virtual void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3) override;
		virtual void setUniformMat4f(const std::string& name, const glm::mat4& matrix) override;
		virtual std::string getName() const override;

		std::string parseName(const std::string& filePath);
	private:
		unsigned int m_RendererID;
		std::string readFile(const std::string& filepath);
		std::vector<unsigned int> compile(std::unordered_map<unsigned int, std::string> shaders);
		void link(std::vector<unsigned int> shadersIDs);
		unsigned int nameToShaderType(const std::string& type);
		std::unordered_map<unsigned int, std::string> parseShaderSource(const std::string& source);
		std::string m_Name;

	};
}
