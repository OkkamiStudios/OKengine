
#include <iostream>
#include <OKengine/OKengineInclude.h>

int main() {
    // Configura los parámetros para la ventana
    int width = 800;
    int height = 600;
    std::string title = "Vulkan or OpenGL Window";
    std::string backend = OpenGL; // Puedes cambiar a "Vulkan" para usar Vulkan
    bool vsync = true;
    int fpsLimit = 60;

    // Crea una instancia de la ventana
    Window window(width, height, title, backend, vsync, fpsLimit);

    // Inicializa la ventana
    if (!window.init()) {
        std::cerr << "No se pudo inicializar la ventana." << std::endl;
        return -1;
    }
    

    // Bucle principal de renderizado
    while (!window.shouldClose()) {
        // Limpia el buffer de color y profundidad
        window.initDraw();

        // Aquí puedes realizar el renderizado, manejo de entrada, etc.

        // Finaliza el renderizado y actualiza la ventana
        window.endDraw();
    }

    // El destructor de Window se encargará de limpiar los recursos
    return 0;
}
