



#shader vertex
#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec4 a_color;

uniform mat4 u_ProjectionView;

out vec4 v_color;


void main(){

	gl_Position = u_ProjectionView * vec4(a_position , 1.0);
	v_color = a_color;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;
in vec4 v_color;

void main(){
	color = v_color;
};