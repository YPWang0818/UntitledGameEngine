#shader vertex

#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in float a_TexIdx;


uniform mat4 u_ViewProjection;


struct VertexOutput
{
	vec4 Color;
	vec2 TexCoord;
	float TexIndex;
};

layout (location = 0) out VertexOutput Output;

void main()
{
	Output.Color = a_Color;
	Output.TexCoord = a_TexCoord;
	Output.TexIndex = a_TexIdx;
	gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

struct VertexOutput
{
	vec4 Color;
	vec2 TexCoord;
	float TexIndex;
};

layout (location = 0) in VertexOutput Input;
uniform sampler2D u_Textures[32];

void main()
{
	color = texture(u_Textures[int(Input.TexIndex)], Input.TexCoord) * Input.Color;
}