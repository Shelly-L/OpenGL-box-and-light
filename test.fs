#version 330 core
out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube skyMap;

void main()
{
     FragColor =texture(skyMap, TexCoords); // set all 4 vector values to 1.0
    //FragColor = vec4(1.0); // set all 4 vector values to 1.0

}