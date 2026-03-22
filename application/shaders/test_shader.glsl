#Shader:Vertex
#version 330 core
layout(location = 0) in vec2 local_position;
layout(location = 1) in vec2 world_position;

void main()
{
	gl_Position = vec4(local_position,1,1);
}

#Shader:Fragment
#version 330 core

out vec4 FragColor;

void main()
{
	FragColor = vec4(1);
}