#pragma once
#include "stdafx.h"

class Input final
{
public:
    Input(GLFWwindow* window, int width, int height);
    ~Input();

private:

    GLFWwindow* window = nullptr;

    int window_width = 0;
    int window_height = 0;

    mat4 ViewMatrix;
    mat4 ProjectionMatrix;

    vec3 position;
    float horizontalAngle;
    float verticalAngle;
    float initialFoV;
    float speed;
    float mouseSpeed;

    double lastTime;

public:
    mat4 getViewMatrix() const;
    mat4 getProjectionMatrix() const;
    void computeMatricesFromInputs();

};
