#Shader:Vertex
#version 330 core
layout(location = 0) in vec2 local_position;
layout(location = 1) in vec2 world_position;
layout(location = 2) in vec2 texture_coords;

out vec2 FragUV;
void main()
{
	gl_Position = vec4(world_position,0.0f,1);
	FragUV = texture_coords;
}

#Shader:Fragment
#version 330 core

uniform sampler2D uTexture;

in vec2 FragUV;
out vec4 FragColor;

void main()
{
	float texture_pixe = texture(uTexture,FragUV).x;

	texture_pixe = abs(texture_pixe - 1.f);
	vec4 color = vec4(vec3(texture_pixe - 1.f), texture_pixe);
	FragColor = vec4(color);
}