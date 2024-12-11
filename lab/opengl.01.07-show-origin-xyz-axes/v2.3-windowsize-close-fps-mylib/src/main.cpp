#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
// #include <sstream>

#include <mylib.h>


int main()
{
    glfwInit(); // Initialize GLFW

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
#endif

    GLFWwindow *window = glfwCreateWindow(800, 600, "MVP Draw Axes", nullptr, nullptr);

    if (window == nullptr)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    OriginXYZ *obj = new OriginXYZ();
    FPS objFPS;
    while (!glfwWindowShouldClose(window))
    {
        processInput(window); // Input processing

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
        obj->display(); // Render the scene
        glfwSwapBuffers(window); // Swap buffers
        glfwPollEvents();        // Check for events

        objFPS.display(); // display fps
    }

    delete obj;

    glfwTerminate(); // Clean up and exit the program
    return 0;
}

