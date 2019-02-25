#version 330 core

in vec3 textureCoords;
out vec4 color;
uniform sampler2D tex;

void main() {
	color = texture(tex, textureCoords.xy);
}