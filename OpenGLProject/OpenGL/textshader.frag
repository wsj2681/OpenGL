#version 460 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D text;
uniform vec3 textColor;

void main() {
    // 텍스처에서 알파 값을 가져와서 텍스트 색상에 적용
    float alpha = texture(text, TexCoords).r;
    color = vec4(textColor * alpha, alpha); // 텍스트 색상을 설정하고 배경은 투명
}