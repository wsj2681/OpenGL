#include "TextRender.h"

TextRender::TextRender(const char* fontPath, int fontSize)
{
	if (!LoadFont(fontPath, fontSize))
	{
		cerr << "ERROR::TextRenderer: Failed to load font" << endl;
	}

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

TextRender::~TextRender()
{
	for (auto& pair : characters) {
		glDeleteTextures(1, &pair.second.TextureID);
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void TextRender::RenderText(ShaderTool& shader, const string& text, float x, float y, float scale, vec3 color)
{
    glUseProgram(shader.programID);
    glUniform3f(glGetUniformLocation(shader.programID, "textColor"), color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    for (auto& c : text) {
        Character ch = characters[c];

        float xpos = x + ch.Bearing.x * scale;
        float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;
        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;

        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }
        };

        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        x += (ch.Advance >> 6) * scale;
    }

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

bool TextRender::LoadFont(const char* fontPath, int fontSize)
{
    // FreeType 초기화
    FT_Library ft;

    if (FT_Init_FreeType(&ft)) {
        cerr << "ERROR::FREETYPE: Could not init FreeType Library" << endl;
        return false;
    }

    // 폰트 로드
    FT_Face face;
    if (FT_New_Face(ft, fontPath, 0, &face)) {
        cerr << "ERROR::FREETYPE: Failed to load font" << endl;
        FT_Done_FreeType(ft);
        return false;
    }
    FT_Set_Pixel_Sizes(face, 0, fontSize);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // 텍스처 바이트 정렬

    // ASCII 문자 텍스처화
    for (GLubyte c = 0; c < 128; c++) {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            cerr << "ERROR::FREETYTPE: Failed to load Glyph" << endl;
            continue;
        }

        // 텍스처 생성 및 설정
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        Character character = {
            texture,
            ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            static_cast<GLuint>(face->glyph->advance.x)
        };
        characters.insert(pair<GLchar, Character>(c, character));
    }

    FT_Done_Face(face);
    FT_Done_FreeType(ft);
    return true;
}
