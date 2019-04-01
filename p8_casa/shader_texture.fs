#version 330 core

in vec2 TexCoord;
out vec4 FragColor;

uniform vec3 aColor;
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    FragColor = texture(texture1, TexCoord);
	FragColor=texture(texture2,TexCoord);
}