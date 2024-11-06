#include "Input.h"

Input::Input(GLFWwindow* window, int width, int height)
    : window(window), position(vec3(0, 0, 5)),
    horizontalAngle(3.14f), verticalAngle(0.0f),
    initialFoV(45.0f),
    speed(3.0f), mouseSpeed(0.005f), 
    window_width(width), window_height(height)
{
    ViewMatrix = mat4(1.f);
    ProjectionMatrix = mat4(1.f);



    lastTime = glfwGetTime();
}

Input::~Input()
{

}

mat4 Input::getViewMatrix() const
{
    return ViewMatrix;
}

mat4 Input::getProjectionMatrix() const
{
    return ProjectionMatrix;
}

void Input::computeMatricesFromInputs()
{
    // ���� �ð� ���
    double currentTime = glfwGetTime();
    float deltaTime = float(currentTime - lastTime);

    // ���콺 ��ġ ��������
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    // ���콺 ��ġ �ʱ�ȭ
    glfwSetCursorPos(window, window_width / 2, window_height / 2);

    // ���� ����
    horizontalAngle += mouseSpeed * float(window_width / 2 - xpos);
    verticalAngle += mouseSpeed * float(window_height / 2 - ypos);

    // ���� ���� ���
    vec3 direction(
        cos(verticalAngle) * sin(horizontalAngle),
        sin(verticalAngle),
        cos(verticalAngle) * cos(horizontalAngle)
    );

    // ������ ���� ���
    vec3 right = vec3(
        sin(horizontalAngle - 3.14f / 2.0f),
        0,
        cos(horizontalAngle - 3.14f / 2.0f)
    );

    // ���� ���� ���
    vec3 up = cross(right, direction);

    // Ű���� �Է¿� ���� ��ġ ������Ʈ
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        position += direction * deltaTime * speed;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        position -= direction * deltaTime * speed;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        position += right * deltaTime * speed;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        position -= right * deltaTime * speed;
    }

    // Field of View ����
    float FoV = initialFoV;

    // ������İ� ī�޶� ��� ���
    ProjectionMatrix = perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);
    ViewMatrix = glm::lookAt(
        position,
        position + direction,
        up
    );

    lastTime = currentTime;
}
