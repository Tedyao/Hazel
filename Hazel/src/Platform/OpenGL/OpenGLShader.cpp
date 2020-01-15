#include "hzpch.h"
#include "OpenGLShader.h"
#include "Glad/glad.h"
#include "Hazel/Core/Log.h"
#include <fstream>


namespace Hazel {

	OpenGLShader::OpenGLShader(const std::string& filePath)
		:m_Name(parseName(filePath))
	{
		
		std::string shadeSource = readFile(filePath);
		std::unordered_map<GLenum, std::string> shaders = parseShaderSource(shadeSource);
		std::vector<GLuint> shaderIDs = compile(shaders);
		link(shaderIDs);

	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
		:m_Name(name)
	{
		std::unordered_map<GLenum, std::string> shaders;
		shaders[GL_VERTEX_SHADER] = vertexSrc;
		shaders[GL_FRAGMENT_SHADER] = fragmentSrc;
		auto shaderIDs = compile(shaders);
		link(shaderIDs);

	}


	OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragSrc)
		:m_Name("Unknown")
	{
		
		std::unordered_map<GLenum, std::string> shaders;
		shaders[GL_VERTEX_SHADER] = vertexSrc;
		shaders[GL_FRAGMENT_SHADER] = fragSrc;
		std::vector<GLuint> shaderIDs = compile(shaders);
		link(shaderIDs);
	}


	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}


	std::string OpenGLShader::getName() const
	{
		return m_Name;
	}

	std::string OpenGLShader::parseName(const std::string& filePath)
	{
		//Assets/shaders/shader.glsl
		size_t nameStart = filePath.find_last_of("/\\");
		nameStart = nameStart == std::string::npos ? 0 : nameStart + 1;
		size_t nameEnd = filePath.rfind(".");
		size_t nameLength = nameEnd == std::string::npos ? filePath.size() - nameStart : nameEnd - nameStart;
		std::string result = filePath.substr(nameStart, nameLength);
		return result;
	}


	std::string OpenGLShader::readFile(const std::string& filepath)
	{
		std::ifstream ifile;
		ifile.open(filepath, std::ios::in | std::ios::binary);
		std::string result;
		ifile.seekg(0, std::ios::end);
		result.resize(ifile.tellg());
		ifile.seekg(0, std::ios::beg);
		ifile.read(&result[0], result.size());
		return result;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::parseShaderSource(const std::string& source)
	{
		std::unordered_map<GLenum, std::string> result;
		const char* token = "#type";
		size_t pos = source.find(token, 0);
		while (pos != std::string::npos)
		{
			size_t lineEnd = source.find_first_of("\r\n", pos + 1);
			size_t sourceStart = source.find_first_not_of("\r\n", lineEnd);
			std::string& type = source.substr(pos + strlen(token) + 1, lineEnd - pos - strlen(token) - 1);
			GLenum shaderType = nameToShaderType(type);
			size_t nextPos = source.find(token, lineEnd + 1);
			result[shaderType] = source.substr(sourceStart, (nextPos == std::string::npos) ? source.size() - sourceStart : nextPos - sourceStart);
			pos = nextPos;
		}
		return result;
	}

	std::vector<GLuint> OpenGLShader::compile(std::unordered_map<GLenum, std::string> shaders)

	{
		std::vector<GLuint> shaderIDs;
		for (auto& kv : shaders)
		{
			GLenum type = kv.first;
			std::string shaderSource = kv.second;

			// Create an empty vertex shader handle
			GLuint shader = glCreateShader(type);
			shaderIDs.emplace_back(shader);
			// Send the vertex shader source code to GL
			// Note that std::string's .c_str is NULL character terminated.
			const GLchar* source = shaderSource.c_str();
			glShaderSource(shader, 1, &source, 0);

			// Compile the vertex shader
			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				// The maxLength includes the NULL character
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				// We don't need the shader anymore.
				glDeleteShader(shader);

				// Use the infoLog as you see fit.

				// In this simple program, we'll just leave
				HZ_CORE_ERROR("Vertex shader compilation failed!");
				HZ_CORE_ERROR("Error message: {0}", infoLog.data());
				HZ_CORE_ASSERT(false, "Vertex shader compilation failed.");

			}

		}

		return shaderIDs;

		
	}

	void OpenGLShader::link(std::vector<unsigned int> shaderIDs)
	{
		m_RendererID = glCreateProgram();
		GLuint program = m_RendererID;

		// Attach our shaders to our program
		for (GLuint shadeID : shaderIDs)
		{
			glAttachShader(program, shadeID);
		}
		glLinkProgram(program);

		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)& isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);
			// Don't leak shaders either.
			for (auto shaderID : shaderIDs)
			{
				glDeleteShader(shaderID);
			}
			HZ_CORE_ERROR("Shader link failed!");
			HZ_CORE_ERROR("Error message: {0}", infoLog.data());
			HZ_CORE_ASSERT(false, "Shader link failed.");
			return;
		}

		for (auto shaderID : shaderIDs)
		{
			glDetachShader(program, shaderID);
		}
		// Always detach shaders after a successful link.

	}

	GLenum OpenGLShader::nameToShaderType(const std::string& type)
	{
		if (type == "vertex")
		{
			return GL_VERTEX_SHADER;
		}
		else if (type == "fragment" || type == "pixel")
		{
			return GL_FRAGMENT_SHADER;
		}
		else
			HZ_CORE_ERROR("Unknow shader type!");
		return 0;
	}

	void OpenGLShader::bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::unbind() const
	{
		glUseProgram(0);
	}


	void OpenGLShader::setUniform1f(const std::string& name, float value)
	{
		int location = getUniform(name);
		glUniform1f(location, value);
	}

	void OpenGLShader::setUniform1i(const std::string& name, int value)
	{
		int location = getUniform(name);
		glUniform1i(location, value);

	}


	void OpenGLShader::setUniformMat4f(const std::string& name, const float* matrix)
	{
		int location = getUniform(name);
		glUniformMatrix4fv(location, 1, GL_TRUE, matrix);


	}

	void OpenGLShader::setUniformMat4f(const std::string& name, const glm::mat4& matrix)
	{
		int location = getUniform(name);
		glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);


	}

	

	

	void OpenGLShader::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
	{
		int location = getUniform(name);
		glUniform4f(location, v0, v1, v2, v3);
	}

	void OpenGLShader::setUniform2f(const std::string& name, float v0, float v1)
	{
		int location = getUniform(name);
		glUniform2f(location, v0, v1);
	}

	int OpenGLShader::getUniform(const std::string& name)
	{
		int location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1)
		{
			std::cout << "Can't find uniform variable: " << name << "!" << std::endl;
			HZ_CORE_ASSERT(false, "Failed to upload uniforms!");
		}
		return location;
	}
}