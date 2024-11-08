#include "Model.h"

Model::Model()
{
}

Model::Model(ShaderTool* shader, TextureTool* texture)
    :shader(shader), texture(texture)
{
}

Model::Model(vector<vec3> vertices, vector<vec2> uvs, vector<vec3> normals)
	:vertices(vertices), uvs(uvs), normals(normals)
{

}

Model::~Model()
{

}

void Model::Create()
{
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec3), vertices.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void*)0);

    glGenBuffers(1, &uvVBO);
    glBindBuffer(GL_ARRAY_BUFFER, uvVBO);
    glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(vec2), uvs.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GL_FLOAT), (void*)0);

    glGenBuffers(1, &normalVBO);
    glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(vec3), normals.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void*)0);

    // 메모리 최소화.
    vertices_count = vertices.size();
    vertices.clear();
    uvs.clear();
    normals.clear();


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Model::Render(const mat4& MVP)
{
    if (shader && texture)
    {
        glUseProgram(shader->programID);
        glUniformMatrix4fv(glGetUniformLocation(shader->programID, "MVP"), 1, GL_FALSE, &MVP[0][0]);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture->textureID);
        glUniform1i(glGetUniformLocation(shader->programID, "textureSampler"), 0);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, vertices_count);
        glBindVertexArray(0);
    }
}
