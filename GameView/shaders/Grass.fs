R"(#version 130

in vec3 vs_out_col;
in vec2 vs_out_tex;

out vec4 fs_out_col;

uniform sampler2D GrassTexture;

void main()
{
	fs_out_col = texture( GrassTexture, vs_out_tex );
})"