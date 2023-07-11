#version 330 core

out vec4 FragColor;

in vec2 TexCoord;
//in vec4 vertexColor;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    FragColor = //vertexColor;
        mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 1.0f);
    //FragColor = texture(texture2, TexCoord);
}