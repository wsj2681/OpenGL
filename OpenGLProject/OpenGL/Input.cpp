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
    // 현재 시간 계산
    double currentTime = glfwGetTime();
    float deltaTime = float(currentTime - lastTime);

    // 마우스 위치 가져오기
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    // 마우스 위치 초기화
    glfwSetCursorPos(window, window_width / 2, window_height / 2);

    // 방향 갱신
    horizontalAngle += mouseSpeed * float(window_width / 2 - xpos);
    verticalAngle += mouseSpeed * float(window_height / 2 - ypos);

    // 방향 벡터 계산
    vec3 direction(
        cos(verticalAngle) * sin(horizontalAngle),
        sin(verticalAngle),
        cos(verticalAngle) * cos(horizontalAngle)
    );

    // 오른쪽 벡터 계산
    vec3 right = vec3(
        sin(horizontalAngle - 3.14f / 2.0f),
        0,
        cos(horizontalAngle - 3.14f / 2.0f)
    );

    // 위쪽 벡터 계산
    vec3 up = cross(right, direction);

    // 키보드 입력에 따른 위치 업데이트
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

    // Field of View 설정
    float FoV = initialFoV;

    // 투영행렬과 카메라 행렬 계산
    ProjectionMatrix = perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);
    ViewMatrix = glm::lookAt(
        position,
        position + direction,
        up
    );

    lastTime = currentTime;
}
