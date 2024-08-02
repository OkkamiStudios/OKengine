#include <OKengine/OKengineInclude.h>
#include <iostream>
#include <thread>
#include <stdexcept>


// Constructor
Window::Window(int width, int height, const std::string& title, const std::string& backend, bool vsync, int fpsLimit)
    : width(width), height(height), title(title), window(nullptr), vsync(vsync), fpsLimit(fpsLimit), backend(backend) {}

// Destructor
Window::~Window() {
    if (window != nullptr) {
        glfwDestroyWindow(window);
    }
    glfwTerminate();
}

// Función para iniciar la ventana
bool Window::init() {
    if (!glfwInit()) {
        std::cerr << "Error al inicializar GLFW" << std::endl;
        return false;
    }

    if (backend == "OpenGL") {
        // Configuración de GLFW para usar OpenGL 3.3 y el perfil core
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    }
    else if (backend == "Vulkan") {
        // Configuración de GLFW para usar Vulkan
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    }
    else {
        std::cerr << "Backend no soportado" << std::endl;
        return false;
    }

    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!window) {
        std::cerr << "Error al crear la ventana GLFW" << std::endl;
        glfwTerminate();
        return false;
    }

    if (backend == "OpenGL") {
        glfwMakeContextCurrent(window);

        // Inicialización de Glad
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cerr << "Error al inicializar GLAD" << std::endl;
            return false;
        }

        glViewport(0, 0, width, height);
        glEnable(GL_DEPTH_TEST);
    }
    else if (backend == "Vulkan") {
        // Inicialización de Vulkan aquí (si es necesario)
    }

    setVSync(vsync);
    lastFrameTime = std::chrono::high_resolution_clock::now();
    Input::Initialize(window);

    return true;
}

// Función para actualizar la ventana
void Window::endDraw() {
    if (backend == "OpenGL") {
        glfwSwapBuffers(window);
        glfwPollEvents();

        if (fpsLimit > 0) {
            auto now = std::chrono::high_resolution_clock::now();
            auto frameDuration = std::chrono::duration<float, std::chrono::seconds::period>(now - lastFrameTime).count();
            auto targetFrameDuration = 1.0f / fpsLimit;

            if (frameDuration < targetFrameDuration) {
                std::this_thread::sleep_for(std::chrono::duration<float>(targetFrameDuration - frameDuration));
            }

            lastFrameTime = now;
        }
    }
    else if (backend == "Vulkan") {
        // Manejo de Vulkan aquí
    }
}

// Función para limpiar la ventana
void Window::initDraw() {
    if (backend == "OpenGL") {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        Input::Update();
    }
    else if (backend == "Vulkan") {
        // Manejo de Vulkan aquí
    }

    Input::Update();
}

// Función para verificar si la ventana debe cerrarse
bool Window::shouldClose() {
    return glfwWindowShouldClose(window);
}

// Función para obtener el tamaño de la ventana
void Window::getSize(int& width, int& height) const {
    glfwGetWindowSize(window, &width, &height);
}

// Función para obtener el puntero a la ventana GLFW
GLFWwindow* Window::getContext() const {
    return window;
}

// Función para activar o desactivar VSync
void Window::setVSync(bool enabled) {
    vsync = enabled;
    glfwSwapInterval(vsync ? 1 : 0);
}

// Función para establecer el límite de FPS
void Window::setFPSLimit(int fps) {
    fpsLimit = fps;
}

// Función para obtener el backend gráfico actual
std::string Window::getBackend() const {
    return backend;
}
