#include "input.h"
#include <stdexcept>

std::map<int, bool> Input::keys;
std::map<int, bool> Input::prevKeys;
std::map<int, bool> Input::buttons;
std::map<int, bool> Input::prevButtons;
GLFWwindow* Input::window = nullptr;
double Input::mouseX = 0.0;
double Input::mouseY = 0.0;

void Input::Initialize(GLFWwindow* win) {
    window = win;
}

void Input::Update() {
    prevKeys = keys;
    prevButtons = buttons;

    // Update keyboard
    for (int i = GLFW_KEY_SPACE; i <= GLFW_KEY_LAST; i++) {
        keys[i] = glfwGetKey(window, i) == GLFW_PRESS;
    }

    // Update mouse buttons
    for (int i = GLFW_MOUSE_BUTTON_1; i <= GLFW_MOUSE_BUTTON_LAST; i++) {
        buttons[i] = glfwGetMouseButton(window, i) == GLFW_PRESS;
    }

    glfwGetCursorPos(window, &mouseX, &mouseY);
}

bool Input::KeycodePress(int keycode) {
    return keys[keycode];
}

bool Input::KeycodeFrame(int keycode) {
    return keys[keycode] && !prevKeys[keycode];
}

bool Input::MouseButtonPress(int button) {
    return buttons[button];
}

bool Input::MouseButtonFrame(int button) {
    return buttons[button] && !prevButtons[button];
}

void Input::GetMousePosition(double& xpos, double& ypos) {
    xpos = mouseX;
    ypos = mouseY;
}

double Input::GetMousePosition(int axis) {
    switch (axis) {
    case MouseX:
        return mouseX;
    case MouseY:
        return mouseY;
    default:
        throw std::invalid_argument("Invalid axis. Use MouseX or MouseY.");
    }
}