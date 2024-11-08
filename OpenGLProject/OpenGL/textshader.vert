#version 460 core

layout (location = 0) in vec4 vertex; // (x, y, z, w) 위치와 텍스처 좌표

out vec2 TexCoords;

uniform mat4 projection;

void main() 
{
    gl_Position = projection * vec4(vertex.xy, 0.0, 1.0); // 화면에 문자 위치 변환
    TexCoords = vertex.zw; // 텍스처 좌표 전달
}