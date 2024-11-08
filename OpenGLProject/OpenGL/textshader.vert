#version 460 core

layout (location = 0) in vec4 vertex; // (x, y, z, w) ��ġ�� �ؽ�ó ��ǥ

out vec2 TexCoords;

uniform mat4 projection;

void main() 
{
    gl_Position = projection * vec4(vertex.xy, 0.0, 1.0); // ȭ�鿡 ���� ��ġ ��ȯ
    TexCoords = vertex.zw; // �ؽ�ó ��ǥ ����
}