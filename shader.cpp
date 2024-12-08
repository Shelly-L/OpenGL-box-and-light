#include"shader.h"
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;



	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		//打开文件
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);

		if (!vShaderFile || !fShaderFile) {
			std::cerr << "Failed to open shader file." << std::endl;

		}
		else {
			std::cout << " shader file opened successfully." << std::endl;
		}


		//把缓冲区的内容流入字符串流
		std::stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		if (vShaderStream.fail()) {
			std::cerr << "Failed to read vertex shader file into stringstream." << std::endl;

		}
		if (fShaderStream.fail()) {
			std::cerr << "Failed to read fragment shader file into stringstream." << std::endl;

		}
		//关闭文件
		vShaderFile.close();
		fShaderFile.close();

		//字符串流转换为字符串
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();



	}
	catch (std::ifstream::failure& e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
	}


	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();


	//VS
	unsigned int vertex, fragment;
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	checkCompileErrors(vertex, "VERTEX");

	//FS
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glad_glCompileShader(fragment);
	checkCompileErrors(fragment, "FRAGMENT");


	//PROGRAM
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	checkCompileErrors(ID, "PROGRAM");

	//删除VS和FS
	glDeleteShader(vertex);
	glDeleteShader(fragment);

}

void Shader::use()
{
	glUseProgram(ID);
}

void Shader::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setMatrix4x4(const std::string& name, glm::mat4 value)const
{
	GLint location=glGetUniformLocation(ID, name.c_str());
	glUniformMatrix4fv(location, 1,GL_FALSE, glm::value_ptr(value));
}

void Shader::setVec3(const std::string& name, glm::vec3 value)const {
	glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::checkCompileErrors(unsigned int shader, std::string type)
{
	int success;
	char infolog[1024];
	if (type == "PROGRAM")
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infolog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infolog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
	else
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infolog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infolog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
}

void Shader::end() {
	glUseProgram(0);
}

