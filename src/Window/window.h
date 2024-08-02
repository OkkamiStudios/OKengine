#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>
#include <string>
#include <chrono>

class Window {
public:
    // Constructor
    Window(int width, int height, const std::string& title, const std::string& backend, bool vsync = true, int fpsLimit = 60);

    // Destructor
    ~Window();

    // Inicializa la ventana
    bool init();

    // Actualiza la ventana y maneja el límite de FPS
    void endDraw();

    // Limpia el buffer de color y profundidad
    void initDraw();

    // Verifica si la ventana debe cerrarse
    bool shouldClose();

    // Obtiene el tamaño de la ventana
    void getSize(int& width, int& height) const;

    // Obtiene el puntero a la ventana GLFW
    GLFWwindow* getContext() const;

    // Activa o desactiva VSync
    void setVSync(bool enabled);

    // Establece el límite de FPS
    void setFPSLimit(int fps);

    // Obtiene el backend gráfico actual
    std::string getBackend() const;

private:
    int width;
    int height;
    std::string title;
    std::string backend;
    GLFWwindow* window;
    bool vsync;
    int fpsLimit;
    std::chrono::high_resolution_clock::time_point lastFrameTime;

    // Configura el contexto gráfico
    void setupContext();
};

#endif // WINDOW_H


#define OpenGL "OpenGL"
#define Vulkan "Vulkan"