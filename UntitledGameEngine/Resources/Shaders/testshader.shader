#shader vertex
#version 330 core

layout(location = 0) in vec3 a_position;
out vec3 v_position;

void main(){

	gl_Position = vec4(a_position , 1.0);
	v_position = a_position + 0.5;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;
in vec3 v_position;

void main(){
	color = vec4(v_position, 1.0);
};