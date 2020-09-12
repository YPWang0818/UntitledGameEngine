#pragma once

#include "glad/glad.h"
#include "glfw/glfw3.h" 
#include "imgui.h"
#include "core/BaseWindow.h"
#include "core/Application.h"

#define GLFW_EXPOSE_NATIVE_WIN32
#include "glfw/glfw3native.h"

namespace UGE {

	
	static void _init_opengl();
	static void _init_glfw();
	static void _compile_shader(const GLchar* vertex_src, const GLchar* frag_src);
	static void _load_font_texture();
	static void _setup_render_states(ImDrawData* drawdata, int fb_width, int fb_hight);
	static void _draw_render_data(ImDrawData* drawdata);
	static void _shutdown();

	static void _init_platform_interface();
	static void _imgui_create_window(ImGuiViewport* viewport);
	static void _imgui_distory_window(ImGuiViewport* viewport);
	static void _imgui_show_window(ImGuiViewport* viewport);
	static void _imgui_set_window_pos(ImGuiViewport* viewport, ImVec2 pos);
	static ImVec2 _imgui_get_window_pos(ImGuiViewport* viewport);
	static void  _imgui_set_window_size(ImGuiViewport* viewport, ImVec2 size);
	static ImVec2 _imgui_get_window_size(ImGuiViewport* viewport);
	static void _imgui_set_window_focus(ImGuiViewport* viewport);
	static bool _imgui_get_window_focus(ImGuiViewport* viewport);
	static bool _imgui_get_window_minimized(ImGuiViewport* viewport);
	static void _imgui_set_window_title(ImGuiViewport* viewport, const char* title);
	static void _imgui_render_window(ImGuiViewport* viewport, void* render_arg);
	static void _imgui_swap_buffer(ImGuiViewport* viewport, void* render_arg);




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




	static void _init_glfw() {

		GLFWwindow* window = static_cast<GLFWwindow*>(Application::getInstance().getWindowHandle().getNativeWindow());

		ImGuiViewport* main_viewport = ImGui::GetMainViewport();

		main_viewport->PlatformHandle = (void*)window;
		#ifdef _WIN32
		main_viewport->PlatformHandleRaw = glfwGetWin32Window(window);
		#endif

		ImGuiIO& io = ImGui::GetIO();

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {	
			_init_platform_interface();
		}


		
	};

	static void _init_opengl() {

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
		glGenVertexArrays(1, &imgui_vertex_array);
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
		imgui_uniforms.projection_mtx = glGetUniformLocation(imgui_shader_program, "ProjMtx");
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

		
	};

	static void _compile_shader(const GLchar* vertex_src, const GLchar* frag_src) {



		imgui_vertex_shader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(imgui_vertex_shader, 1, &vertex_src, nullptr);
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

		}


		imgui_fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(imgui_fragment_shader, 1, &frag_src, nullptr);
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
		}


		imgui_shader_program = glCreateProgram();
		glAttachShader(imgui_vertex_shader, imgui_shader_program);
		glAttachShader(imgui_fragment_shader, imgui_shader_program);
		glLinkProgram(imgui_shader_program);

		GLint is_linked = 0;
		glGetProgramiv(imgui_shader_program, GL_LINK_STATUS, (int*)&is_linked);
		if (is_linked == GL_FALSE)
		{
			GLint max_length = 0;
			glGetProgramiv(imgui_shader_program, GL_INFO_LOG_LENGTH, &max_length);

			std::vector<GLchar> log(max_length);
			glGetProgramInfoLog(imgui_shader_program, max_length, &max_length, &log[0]);


			glDeleteProgram(imgui_shader_program);

			glDeleteShader(imgui_vertex_shader);
			glDeleteShader(imgui_fragment_shader);

			UGE_CORE_ERROR("{0}", log.data());
			UGE_CORE_ASSERT(false, "Program Linking Error.");
		}

	}


	static void _load_font_texture()
	{
		unsigned char* data;
		int width, hight;
		ImGuiIO& io = ImGui::GetIO();

		io.Fonts->GetTexDataAsRGBA32(&data, &width, &hight);
		glBindTexture(GL_TEXTURE_2D, imgui_font_texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, hight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		io.Fonts->TexID = (ImTextureID)(intptr_t)imgui_font_texture;

	}

	static void _setup_render_states(ImDrawData* drawdata, int fb_width, int fb_hight) {

		// Bind everything
		glBindBuffer(GL_ARRAY_BUFFER, imgui_vertex_buffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, imgui_index_buffer);
		glBindVertexArray(imgui_vertex_array);
		glUseProgram(imgui_shader_program);


		glViewport(0, 0, (GLsizei)fb_width, (GLsizei)fb_hight);

		// SetUp Projection matrix
		float L = drawdata->DisplayPos.x;
		float R = drawdata->DisplayPos.x + drawdata->DisplaySize.x;
		float T = drawdata->DisplayPos.y;
		float B = drawdata->DisplayPos.y + drawdata->DisplaySize.y;
		const float ortho_projection[4][4] =
		{
			{ 2.0f / (R - L),	0.0f,			0.0f,		0.0f},
			{ 0.0f,			2.0f / (T - B),		0.0f,		0.0f },
			{ 0.0f,         0.0f,			-1.0f,		0.0f },
			{ (R + L) / (L - R),  (T + B) / (B - T),	0.0f,		1.0f },
		};

		glUniformMatrix4fv(imgui_uniforms.projection_mtx, 1, GL_FALSE, &ortho_projection[0][0]);
		glBindSampler(0, 0);
	}

	static void _draw_render_data(ImDrawData* drawdata)
	{

		int fb_width = (int)(drawdata->DisplaySize.x * drawdata->FramebufferScale.x);
		int fb_hight = (int)(drawdata->DisplaySize.y * drawdata->FramebufferScale.y);
		if (fb_width <= 0 || fb_hight <= 0) return;

		_setup_render_states(drawdata, fb_width, fb_hight);

		ImVec2 clip_offset = drawdata->DisplayPos;
		ImVec2 clip_scale = drawdata->FramebufferScale;


		for (int i = 0; i < drawdata->CmdListsCount; i++) {

			const ImDrawList* cmd_list = drawdata->CmdLists[i];

			// Fill in the buffers;
			glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)cmd_list->VtxBuffer.Size * sizeof(ImDrawVert), (const GLvoid*)cmd_list->VtxBuffer.Data, GL_STREAM_DRAW);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)cmd_list->IdxBuffer.Size * sizeof(ImDrawIdx), (const GLvoid*)cmd_list->IdxBuffer.Data, GL_STREAM_DRAW);


			for (int i_cmd = 0; i_cmd < cmd_list->CmdBuffer.Size; i_cmd++) {

				const ImDrawCmd* cmd = &cmd_list->CmdBuffer[i_cmd];


				if (cmd->UserCallback != nullptr) {

					if (cmd->UserCallback == ImDrawCallback_ResetRenderState)
						_setup_render_states(drawdata, fb_width, fb_hight);
					else
						cmd->UserCallback(cmd_list, cmd);
					continue;
				}

				ImVec4 clip_rect;
				clip_rect.x = (cmd->ClipRect.x - clip_offset.x) * clip_scale.x;
				clip_rect.y = (cmd->ClipRect.y - clip_offset.y) * clip_scale.y;
				clip_rect.z = (cmd->ClipRect.z - clip_offset.x) * clip_scale.x;
				clip_rect.w = (cmd->ClipRect.w - clip_offset.y) * clip_scale.y;

				if (clip_rect.x < fb_width && clip_rect.y < fb_hight && clip_rect.z >= 0.0f && clip_rect.w >= 0.0f)
				{
					glScissor((int)clip_rect.x, (int)(fb_hight - clip_rect.w), (int)(clip_rect.z - clip_rect.x), (int)(clip_rect.w - clip_rect.y));

					glBindTexture(GL_TEXTURE_2D, (GLuint)(intptr_t)cmd->TextureId);
					glDrawElementsBaseVertex(GL_TRIANGLES, (GLsizei)cmd->ElemCount, sizeof(ImDrawIdx) == 2 ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT, (void*)(intptr_t)(cmd->IdxOffset * sizeof(ImDrawIdx)), (GLint)cmd->VtxOffset);



				}
			}
		}

	}

	static void _shutdown() {

	}



	static void _init_platform_interface() {

		ImGuiPlatformIO& platform_io = ImGui::GetPlatformIO();

		platform_io.Platform_CreateWindow = _imgui_create_window;
		platform_io.Platform_DestroyWindow = _imgui_distory_window;
		platform_io.Platform_ShowWindow = _imgui_show_window;
		platform_io.Platform_SetWindowPos = _imgui_set_window_pos;
		platform_io.Platform_GetWindowPos = _imgui_get_window_pos;
		platform_io.Platform_SetWindowSize = _imgui_set_window_size;
		platform_io.Platform_GetWindowSize = _imgui_get_window_size;
		platform_io.Platform_SetWindowFocus = _imgui_set_window_focus;
		platform_io.Platform_GetWindowFocus = _imgui_get_window_focus;
		platform_io.Platform_GetWindowMinimized = _imgui_get_window_minimized;
		platform_io.Platform_SetWindowTitle = _imgui_set_window_title;
		platform_io.Platform_RenderWindow = _imgui_render_window;
		platform_io.Platform_SwapBuffers = _imgui_swap_buffer;

		#if GLFW_HAS_WINDOW_ALPHA
		platform_io.Platform_SetWindowAlpha = ImGui_ImplGlfw_SetWindowAlpha;
		#endif




	};


	static BaseWindow* _get_app_main_window() { return &(Application::getInstance().getWindowHandle()); };

	static struct ImguiViewPortData {
		Ref<BaseWindow> window ;
		bool        window_owned = false;
		int			ignore_window_pos_event_frame = -1;
		int         ignore_window_size_event_frame = -1;
		
	};

	static void _imgui_create_window(ImGuiViewport* viewport)
	{

		ImguiViewPortData* data = new ImguiViewPortData;
		WindowProps props;


		props.Title = "New Viewport.";
		props.Width = viewport->Size.x;
		props.Hight = viewport->Size.y;
		props.isVisble = false;
		props.isFocusedOnCreate = false;
		props.isFocusedOnShow = false;
		props.isDecorated = (viewport->Flags & ImGuiViewportFlags_NoDecoration) ? false : true ;
		props.isFloating = (viewport->Flags & ImGuiViewportFlags_TopMost) ? true : false;
		props.isVync = false;

		data->window = BaseWindow::Create(props, _get_app_main_window()->getGraphicsContex());
		data->window_owned = true;

		GLFWwindow* native_window = static_cast<GLFWwindow*>(data->window->getNativeWindow());
		viewport->PlatformUserData = static_cast<void*>(data);
		viewport->PlatformHandle = native_window;

		#ifdef _WIN32
			viewport->PlatformHandleRaw = glfwGetWin32Window(native_window);
		#endif
	
	};


	static void _imgui_distory_window(ImGuiViewport* viewport) 
	{
	
		if (ImguiViewPortData* data = (ImguiViewPortData*)viewport->PlatformUserData) {

			if (data->window_owned) {
				data->window.reset();
			};
			delete data;
		};
		
		viewport->PlatformHandle = nullptr;
		viewport->PlatformUserData = nullptr;
		viewport->PlatformHandleRaw = nullptr;
	};




	static void _imgui_show_window(ImGuiViewport* viewport) {

		ImguiViewPortData* data = (ImguiViewPortData*)viewport->PlatformUserData;
	#if defined(_WIN32)
		// GLFW hack: Hide icon from task bar
		HWND hwnd = (HWND)viewport->PlatformHandleRaw;
		if (viewport->Flags & ImGuiViewportFlags_NoTaskBarIcon)
		{
			LONG ex_style = ::GetWindowLong(hwnd, GWL_EXSTYLE);
			ex_style &= ~WS_EX_APPWINDOW;
			ex_style |= WS_EX_TOOLWINDOW;
			::SetWindowLong(hwnd, GWL_EXSTYLE, ex_style);
		}
	#endif
		data->window->setVisbility(true);
		
	};


	static void _imgui_set_window_pos(ImGuiViewport* viewport, ImVec2 pos) {
		ImguiViewPortData* data = (ImguiViewPortData*)viewport->PlatformUserData;
		data->window->setPos(glm::ivec2(pos.x, pos.y));
	};


	static ImVec2 _imgui_get_window_pos(ImGuiViewport* viewport) {
		ImguiViewPortData* data = (ImguiViewPortData*)viewport->PlatformUserData;

		int x_pos = data->window->getPos().x;
		int y_pos = data->window->getPos().y;

		data->ignore_window_pos_event_frame = ImGui::GetFrameCount();
		return ImVec2(x_pos, y_pos);
	
	};


	static void  _imgui_set_window_size(ImGuiViewport* viewport, ImVec2 size) 
	{
		ImguiViewPortData* data = (ImguiViewPortData*)viewport->PlatformUserData;
		data->window->setSize(size.x, size.y);
		data->ignore_window_size_event_frame = ImGui::GetFrameCount();

	};

	static ImVec2 _imgui_get_window_size(ImGuiViewport* viewport) {
	
		ImguiViewPortData* data = (ImguiViewPortData*)viewport->PlatformUserData;

		unsigned int x = data->window->getWidth();
		unsigned int y = data->window->getHight();

		return ImVec2((float)x, (float)y);
	};

	static void _imgui_set_window_focus(ImGuiViewport* viewport) {
		ImguiViewPortData* data = (ImguiViewPortData*)viewport->PlatformUserData;
		data->window->FocusWindow();
	};
	static bool _imgui_get_window_focus(ImGuiViewport* viewport) 
	{
		ImguiViewPortData* data = (ImguiViewPortData*)viewport->PlatformUserData;
		data->window->isFocused();
	};

	static bool _imgui_get_window_minimized(ImGuiViewport* viewport)
	{
		ImguiViewPortData* data = (ImguiViewPortData*)viewport->PlatformUserData;
		data->window->isMinimized();
	};

	static void _imgui_set_window_title(ImGuiViewport* viewport, const char* title) {
		ImguiViewPortData* data = (ImguiViewPortData*)viewport->PlatformUserData;
		data->window->setTitle(title);
	};

	static void _imgui_render_window(ImGuiViewport* viewport, void* render_arg) 
	{
		ImguiViewPortData* data = (ImguiViewPortData*)viewport->PlatformUserData;
		data->window->getGraphicsContex()->makeContexCurrent();
	
	};
	static void _imgui_swap_buffer(ImGuiViewport* viewport, void* rander_arg) {
		ImguiViewPortData* data = (ImguiViewPortData*)viewport->PlatformUserData;
		data->window->getGraphicsContex()->makeContexCurrent();
		data->window->getGraphicsContex()->SwapBuffers();
	};


}