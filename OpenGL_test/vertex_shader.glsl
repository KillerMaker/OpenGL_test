#version 330 core

layout (location = 0) in vec3 aPos;
//layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTexCoord;

out vec4 vertexColor;
out vec2 TexCoord;

uniform mat4 transform_matrix;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;

void main()
{
	TexCoord = aTexCoord;
	//vertexColor = vec4(aColor, 1.0f);

	vec4 vert = projection_matrix * view_matrix * transform_matrix * model_matrix * vec4(aPos, 1.0f);

	gl_Position = vert;
}

