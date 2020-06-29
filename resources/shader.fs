#version 330 core

out vec4 FragColor;

in vec2 tex_coord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float blend_amount;

void main() {
    FragColor = mix(texture(texture1, tex_coord), texture(texture2, tex_coord), blend_amount);
}