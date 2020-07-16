#shader vertex
#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec2 a_texcoord;

out vec2 v_texcoord;

uniform mat4 u_ProjectionView;
uniform mat4 u_Model;

void main(){

	gl_Position =  u_ProjectionView * u_Model * vec4(a_position, 1.0);
	v_texcoord = a_texcoord;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;
in vec2 v_texcoord;

uniform sampler2D u_texture;

void main(){
	color =	texture(u_texture, v_texcoord);
	
	//vec4(v_texcoord, 0.0, 1.0);

	}