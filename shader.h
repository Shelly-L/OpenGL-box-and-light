#ifndef SHADER_H
#define SHADER_H

#include"core.h"
#include<string>


class Shader
{
public:
	//����ID
	unsigned int ID;


	//��������ȡ��������ɫ��
	Shader(const char* vertexPath, const char* fragmentPath);

	//ʹ��/�������
	void use();

	//uniform���ߺ���
	void setBool(const std::string& name, bool value)const;
	void setInt(const std::string& name, int value)const;
	void setFloat(const std::string& name, float value)const;
	void setMatrix4x4(const std::string& name, glm::mat4 value)const;
	void setVec3(const std::string& name, glm::vec3 value)const;

	//����Ƿ��б������
	void checkCompileErrors(unsigned int shader, std::string type);
	void end();

};

#endif