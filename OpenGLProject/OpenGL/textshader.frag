#version 460 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D text;
uniform vec3 textColor;

void main() {
    // �ؽ�ó���� ���� ���� �����ͼ� �ؽ�Ʈ ���� ����
    float alpha = texture(text, TexCoords).r;
    color = vec4(textColor * alpha, alpha); // �ؽ�Ʈ ������ �����ϰ� ����� ����
}