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

in vec2 FragUV;
out vec4 FragColor;

float plot(vec2 st, float tickness, float smoothness){
  return  1.0f - ( smoothstep(tickness - smoothness, tickness, st.x - st.y) + smoothstep(smoothness - tickness, -tickness, st.x - st.y));
}

void main()
{
    float line_thickness = .1f;
    float color = plot(FragUV,line_thickness,.05f);
	FragColor = vec4(color);
}