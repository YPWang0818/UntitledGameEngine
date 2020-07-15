#shader vertex
#version 330 core

layout(location = 0) in vec3 a_position;

uniform mat4 u_ProjectionView;
uniform mat4 u_Model;

void main(){

	gl_Position = u_ProjectionView * u_Model * vec4(a_position, 1.0);
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;
void main(){
	color = vec4(0.1, 0.2, 0.8, 1.0);
};