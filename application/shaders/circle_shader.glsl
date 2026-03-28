#Shader:Vertex
#version 330 core
layout(location = 0) in vec2 local_position;
layout(location = 1) in vec2 world_position;

uniform mat4 u_projection;

out vec2 FragUV;
void main()
{
	gl_Position = u_projection * vec4(world_position,0.0f,1);
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

	float radius = 1.f;
	coords.x *= screen_aspect_ratio > 1.0f ? screen_aspect_ratio : 1.0f;
	coords.y /= screen_aspect_ratio < 1.0f ? screen_aspect_ratio : 1.0f;

	float circle_smooth_value = 0.09f;
	float color_value = 1.f - smoothstep(radius - circle_smooth_value, radius,length(coords));

	FragColor = vec4(color_value);
}