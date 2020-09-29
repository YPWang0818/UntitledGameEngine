#pragma once
#include "core/Log.h"
#include "glad/glad.h"

#define GLCALL(x) _glClearError();\
	x;\
	UGE_CORE_ASSERT(_glCall(), "OpenGL Error")

static void _glClearError();
static bool _glCall();

void _glClearError()
{
	while (glGetError() != GL_NO_ERROR);
};

bool _glCall()
{
	while (GLenum error = glGetError()) {
		UGE_CORE_ERROR("Erorr ID {0}", error);
		return false;
	}

	return true;
};


