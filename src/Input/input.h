#pragma once
#include <GLFW/glfw3.h>
#include <map>
#include "Codes.h"

class Input {
public:
    static void Initialize(GLFWwindow* window);
    static void Update();
    // Keyboard functions
    static bool KeycodePress(int keycode);
    static bool KeycodeFrame(int keycode);
    // Mouse functions
    static bool MouseButtonPress(int button);
    static bool MouseButtonFrame(int button);
    static void GetMousePosition(double& xpos, double& ypos);
    static double GetMousePosition(int axis);
private:
    static GLFWwindow* window;
    static std::map<int, bool> keys;
    static std::map<int, bool> prevKeys;
    static std::map<int, bool> buttons;
    static std::map<int, bool> prevButtons;
    static double mouseX;
    static double mouseY;
};