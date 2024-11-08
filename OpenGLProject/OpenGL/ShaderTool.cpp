#include "ShaderTool.h"

GLuint ShaderTool::LoadShaders(const char* vsPath, const char* fsPath)
{
    // vertex shader File Load
    GLuint vsID = glCreateShader(GL_VERTEX_SHADER);
    ifstream vsShaderStream(vsPath, ios::in);
    if (!vsShaderStream.is_open()) 
    {
        cout << "Vertex Shader File : " << vsPath << " cannot find file" << endl;
        return 0;
    }

    stringstream vsBuffer;
    vsBuffer << vsShaderStream.rdbuf();
    vsShaderStream.close();
    string vscode = vsBuffer.str();

    // fragment shader File Load
    GLuint fsID = glCreateShader(GL_FRAGMENT_SHADER);
    ifstream fsShaderStream(fsPath, ios::in);
    if (!fsShaderStream.is_open()) 
    {
        cout << "Fragment Shader File : " << vsPath << " cannot find file" << endl;
        return 0;
    }

    stringstream fsBuffer;
    fsBuffer << fsShaderStream.rdbuf();
    fsShaderStream.close();
    string fscode = fsBuffer.str();


    GLint result = GL_FALSE;

    int infoLogLength = 0;

    // vertex shader compile
    cout << "Compiling shader... : " << vsPath << endl;
    const char* vsSourcePointer = vscode.c_str();
    glShaderSource(vsID, 1, &vsSourcePointer, NULL);
    glCompileShader(vsID);

    cout << "Checking shader... : " << vsPath << endl;
    glGetShaderiv(vsID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(vsID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0)
    {
        vector<char> vsErrorMessage(infoLogLength + 1);
        glGetShaderInfoLog(vsID, infoLogLength, NULL, &vsErrorMessage[0]);
        cout << vsErrorMessage[0];
    }

    // fragment shader compile
    cout << "Compiling shader... : " << fsPath << endl;
    const char* fsSourcePointer = fscode.c_str();
    glShaderSource(fsID, 1, &fsSourcePointer, NULL);
    glCompileShader(fsID);

    cout << "Checking shader... : " << fsPath << endl;
    glGetShaderiv(fsID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(fsID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0)
    {
        vector<char> fsErrorMessage(infoLogLength + 1);
        glGetShaderInfoLog(fsID, infoLogLength, NULL, &fsErrorMessage[0]);
        cout << fsErrorMessage[0];
    }

    // shader linking
    cout << "Linking Program..." << endl;
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, vsID);
    glAttachShader(ProgramID, fsID);
    glLinkProgram(ProgramID);

    glGetProgramiv(ProgramID, GL_LINK_STATUS, &result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0)
    {
        vector<char> programErrorMessage(infoLogLength + 1);
        glGetProgramInfoLog(ProgramID, infoLogLength, NULL, &programErrorMessage[0]);
        cout << programErrorMessage[0];
    }

    glDetachShader(ProgramID, vsID);
    glDetachShader(ProgramID, fsID);

    glDeleteShader(vsID);
    glDeleteShader(fsID);

    this->programID = ProgramID;

    return ProgramID;
}
