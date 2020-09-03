#pragma once
#include "glfw/glfw3.h" 
#include "glad/glad.h"
#include "imgui.h"
#include "Platform/openGL/gl_debug.h"


namespace UGE {

	static int _init_renderer(GLFWwindow* window);
	static int _init_opengl();
	static int _compile_shader(const GLchar* vertex_src, const GLchar* frag_src);
	static int _load_font_texture();
	static int _init_glfw(GLFWwindow* window);
	static int _new_frame();
	static int _setup_render_states(ImDrawData* drawdata, int fb_width, int fb_hight);
	static int _draw_render_data(ImDrawData* drawdata);
	static int _shutdown();
	


	static GLuint imgui_vertex_shader = 0;
	static GLuint imgui_fragment_shader = 0;
	static GLuint imgui_shader_program = 0;
	static GLuint imgui_vertex_buffer = 0;
	static GLuint imgui_index_buffer = 0;
	static GLuint imgui_font_texture = 0;
	static GLuint imgui_vertex_array = 0;

	static struct uniform_location {
		GLint texture;
		GLint projection_mtx;
	} imgui_uniforms;

	static struct attrib_location {
		GLint Position;
		GLint UV;
		GLint Color;
	} imgui_attributes;


	static int _init_renderer(GLFWwindow* window) {

		_init_opengl();
		_init_glfw(window);

		return 0;
	};

	static int _init_opengl() { 

		// Initial Setup
		glEnable(GL_BLEND);
		glBlendEquation(GL_FUNC_ADD);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_SCISSOR_TEST);
		#ifdef GL_POLYGON_MODE
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		#endif

		glGenBuffers(1, &imgui_vertex_buffer);
		glGenBuffers(1, &imgui_index_buffer);
		glGenVertexArrays(1, imgui_vertex_array);
		glGenTextures(1, &imgui_font_texture);

		// Set Up can Compile Shaders.
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

		
		// Set Up textures
		glBindTexture(GL_TEXTURE_2D, imgui_font_texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);


		// Get Unifrom Locations.
		imgui_uniforms.texture = glGetUniformLocation(imgui_shader_program, "Texture");
		imgui_uniforms.projection_mtx = glGetUniformLocation(g_ShaderHandle, "ProjMtx");
		glUniform1i(imgui_uniforms.texture, 0);
		


		// SetUp vertex buffer layout
		imgui_attributes.Position = glGetAttribLocation(imgui_shader_program, "Position");
		imgui_attributes.UV = glGetAttribLocation(imgui_shader_program, "UV");
		imgui_attributes.Color = glGetAttribLocation(imgui_shader_program, "Color");

		glBindVertexArray(imgui_vertex_array);
		glBindBuffer(GL_ARRAY_BUFFER, imgui_vertex_buffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, imgui_index_buffer);
		
		glEnableVertexAttribArray(imgui_attributes.Position);
		glEnableVertexAttribArray(imgui_attributes.UV);
		glEnableVertexAttribArray(imgui_attributes.Color);

		glVertexAttribPointer(imgui_attributes.Position, 2, GL_FLOAT, GL_FALSE, sizeof(ImDrawVert), (GLvoid*)IM_OFFSETOF(ImDrawVert, pos));
		glVertexAttribPointer(imgui_attributes.UV, 2, GL_FLOAT, GL_FALSE, sizeof(ImDrawVert), (GLvoid*)IM_OFFSETOF(ImDrawVert, uv));
		glVertexAttribPointer(imgui_attributes.Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(ImDrawVert), (GLvoid*)IM_OFFSETOF(ImDrawVert, col));


		// Unbind Eveything
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);

		return 0;
	};

	static int _compile_shader(const GLchar* vertex_src, const GLchar* frag_src) {
	
		
		
		imgui_vertex_shader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(imgui_vertex_shader, 1, vertex_src, nullptr);
		glCompileShader(imgui_vertex_shader);

		GLint is_compiled = 0;
		glGetShaderiv(imgui_vertex_shader, GL_COMPILE_STATUS, &is_compiled);

		if (is_compiled == GL_FALSE)
		{
			GLint max_length = 0;
			glGetShaderiv(imgui_vertex_shader, GL_INFO_LOG_LENGTH, &max_length);

			std::vector<GLchar> log(max_length);
			glGetShaderInfoLog(imgui_vertex_shader, max_length, &max_length, &log[0]);

			glDeleteShader(imgui_vertex_shader);

			UGE_CORE_ERROR("{0}", log.data());
			UGE_CORE_ASSERT(false, "Vertex Shader Compile Failure.");

			return 1;
		}

	
		imgui_fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(imgui_fragment_shader, 1, frag_src, nullptr);
		glCompileShader(imgui_fragment_shader);


		glGetShaderiv(imgui_fragment_shader, GL_COMPILE_STATUS, &is_compiled);

		if (is_compiled == GL_FALSE)
		{
			GLint max_length = 0;
			glGetShaderiv(imgui_fragment_shader, GL_INFO_LOG_LENGTH, &max_length);

			std::vector<GLchar> log(max_length);
			glGetShaderInfoLog(imgui_fragment_shader, max_length, &max_length, &log[0]);

			glDeleteShader(imgui_fragment_shader);

			UGE_CORE_ERROR("{0}", log.data());
			UGE_CORE_ASSERT(false, "Fragment Shader Compile Failure.");

			return 1;
		}
	

		imgui_shader_program = glCreateProgram();
		glAttachShader(imgui_vertex_shader, imgui_shader_program);
		glAttachShader(imgui_fragment_shader, gimgui_shader_program);
		glLinkProgram(imgui_shader_program);
		
		GLint is_linked= 0;
		glGetProgramiv(imgui_shader_program , GL_LINK_STATUS, (int*)&is_linked);
		if (is_linked == GL_FALSE)
		{
			GLint max_length = 0;
			glGetProgramiv(imgui_shader_program, GL_INFO_LOG_LENGTH, &max_length);

			std::vector<GLchar> log(max_length);
			glGetProgramInfoLog(imgui_shader_program, max_length, &max_length, &[0]);


			glDeleteProgram(imgui_shader_program);

			glDeleteShader(imgui_vertex_shader);
			glDeleteShader(imgui_fragment_shader);

			UGE_CORE_ERROR("{0}", log.data());
			UGE_CORE_ASSERT(false, "Program Linking Error.");

			return 1;
		}


		return 0;
	}


	static int _load_font_texture() 
	{
		unsigned char* data;
		int width, hight;
		ImGuiIO& io = ImGui::GetIO();

		io.Fonts->GetTexDataAsRGBA32((&data, &width, &hight);
		glBindTexture(GL_TEXTURE_2D, imgui_font_texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
		io.Fonts->TexID = (ImTextureID)(intptr_t)imgui_font_texture;

		return 0;
	}

	static int _setup_render_states(ImDrawData* drawdata, int fb_width, int fb_hight) {
	
		// Bind everything
		glBindBuffer(GL_ARRAY_BUFFER, imgui_vertex_buffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, imgui_index_buffer);
		glBindVertexArray(imgui_vertex_array);
		glBindTexture(GL_TEXTURE_2D, imgui_font_texture);
		glUseProgram(imgui_shader_program;


		glViewport(0, 0, (GLsizei)fb_width, (GLsizei)fb_height);

		// SetUp Projection matrix
		float L = draw_data->DisplayPos.x;
		float R = draw_data->DisplayPos.x + draw_data->DisplaySize.x;
		float T = draw_data->DisplayPos.y;
		float B = draw_data->DisplayPos.y + draw_data->DisplaySize.y;
		const float ortho_projection[4][4] =
		{
			{ 2.0f / (R - L),   0.0f,         0.0f,   0.0f },
			{ 0.0f,         2.0f / (T - B),   0.0f,   0.0f },
			{ 0.0f,         0.0f,        -1.0f,   0.0f },
			{ (R + L) / (L - R),  (T + B) / (B - T),  0.0f,   1.0f },
		};



		return 0
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
