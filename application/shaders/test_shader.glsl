#Shader:Vertex
#version 330 core
layout(location = 0) in vec2 local_position;
layout(location = 1) in vec2 world_position;

out vec2 FragUV;
void main()
{
	gl_Position = vec4(local_position,1,1);
	FragUV = local_position;
}

#Shader:Fragment
#version 330 core

uniform vec2 u_ScreenSize;

in vec2 FragUV;
out vec4 FragColor;

void main()
{
	float screen_aspect_ratio = u_ScreenSize.x / u_ScreenSize.y;
	vec2 coords = FragUV;

	float radius = 1.f/10.f;
	coords.x *= screen_aspect_ratio > 1.0f ? screen_aspect_ratio : 1.0f;
	coords.y /= screen_aspect_ratio < 1.0f ? screen_aspect_ratio : 1.0f;

	float multiplier = float(length(coords) <= radius);

	FragColor = vec4(multiplier);
}