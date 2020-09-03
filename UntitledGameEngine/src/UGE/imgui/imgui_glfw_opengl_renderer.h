#pragma once
#include "glfw/glfw3.h" 
#include "glad/glad.h"
#include "imgui.h"

namespace UGE {

	static int _init_renderer(GLFWwindow* window);
	static int _init_opengl();
	static int _compile_shader(const GLchar* vertex_src, const GLchar* frag_src);
	static int _init_glfw(GLFWwindow* window);
	static int _new_frame();
	static int _draw_render_data(ImDrawData* drawdata);
	static int _shutdown();
	


	static GLuint imgui_vertex_shader = 0;
	static GLuint imgui_fragment_shader = 0;
	static GLuint imgui_shader_program = 0;
	

	static int _init_renderer(GLFWwindow* window) {

		_init_opengl();
		_init_glfw(window);

		return 0;
	};

	static int _init_opengl() { 
		
		GLuint imgui_texture;
		GLuint imgui_array_buffer;
		GLuint imgui_vertex_array;

		glGetIntegerv(GL_TEXTURE_BINDING_2D, &imgui_texture);
		glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &imgui_array_buffer);
		glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &imgui_vertex_array);

		const GLchar* imgui_vertex_shader_src = 
			"#version 410 core \n"
			"layout (location = 0) in vec2 Position;\n"
			"layout (location = 1) in vec2 UV;\n"
			"layout (location = 2) in vec4 Color;\n"
			"uniform mat4 ProjMtx;\n"
			"out vec2 Frag_UV;\n"
			"out vec4 Frag_Color;\n"
			"void main()\n"
			"{\n"
			"    Frag_UV = UV;\n"
			"    Frag_Color = Color;\n"
			"    gl_Position = ProjMtx * vec4(Position.xy,0,1);\n"
			"}\n";

		const GLchar* imgui_fragment_shader_src = 
			"#version 410 core \n"
			"in vec2 Frag_UV;\n"
			"in vec4 Frag_Color;\n"
			"uniform sampler2D Texture;\n"
			"layout (location = 0) out vec4 Out_Color;\n"
			"void main()\n"
			"{\n"
			"    Out_Color = Frag_Color * texture(Texture, Frag_UV.st);\n"
			"}\n";

		_compile_shader(imgui_vertex_shader_src, imgui_fragment_shader_src);
		

		return 0;
	};

	static int _compile_shader(const GLchar* vertex_src, const GLchar* frag_src) {
	
		
		
		imgui_vertex_shader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(imgui_vertex_shader, 1, vertex_src, nullptr);
		glCompileShader(imgui_vertex_shader);


	
		imgui_fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(imgui_fragment_shader, 1, frag_src, nullptr);
		glCompileShader(imgui_fragment_shader);
	

		imgui_shader_program = glCreateProgram();
		glAttachShader(imgui_vertex_shader, imgui_shader_program);
		glAttachShader(imgui_fragment_shader, gimgui_shader_program);
		glLinkProgram(imgui_shader_program);
	
		return 0;
	}


	static int _init_glfw(GLFWwindow* window)
	{
		return 0;
	};

	static int _new_frame() 
	{
		return 0;
	};

	static int _draw_render_data(ImDrawData* drawdata)
	{
		
		return 0;
	}
	
	static int _shutdown() {
	
	
	}
