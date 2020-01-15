#type vertex
#version 330 core
layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec2 a_TextureCoord;
out vec2 v_TextureCoord;
uniform mat4 u_TransformMatrix;
uniform mat4 u_ViewProjectionMatrix;
void main()
{	
	gl_Position = u_ViewProjectionMatrix * u_TransformMatrix * a_Position;
	v_TextureCoord = a_TextureCoord;
}

#type fragment
#version 330 core
layout(location = 0) out vec4 color;
in vec2 v_TextureCoord;
uniform sampler2D u_Texture;
void main()
{	
	color = texture(u_Texture, v_TextureCoord);
}