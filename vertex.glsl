#version 460 core
layout (location = 0) in vec3 aPos;
layout(location=1)in vec3 aNormal;
layout (location = 2) in vec2 aUV;

out vec2 uv;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 transform;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

//aPos作为attribute（属性）传入shader
//不允许更改的
void main()
{
	vec4 position = vec4(aPos, 1.0);
	position = projectionMatrix*viewMatrix * transform*position;
	gl_Position = position;
	FragPos=vec3(transform*vec4(aPos,1.0));
	Normal=mat3(transpose(inverse(transform)))*aNormal;
	uv = aUV;
}