#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <sstream>

#include <mylib.h>
void processInput(GLFWwindow *window);

// FPS: Calucate and print the fps on console
//Usage:
/*
    FPS *objFPS = new FPS();
    while (!glfwWindowShouldClose(window)) {
        
        ...
        objFPS->display(); // display fps value
    }
*/
class FPS
{
private:
    // Variables for FPS calculation
    double lastTime = glfwGetTime();
    int nbFrames = 0;

public:
    FPS();
    void display();
};

FPS::FPS()
{
}

void FPS::display()
{
    // FPS calculation
    double currentTime = glfwGetTime();
    nbFrames++;
    if (currentTime - lastTime >= 1.0)
    { // If lastTime is more than 1 sec ago
        double fps = double(nbFrames) / (currentTime - lastTime);
        std::stringstream ss;
        ss << "FPS: " << fps;
        // glfwSetWindowTitle(window, ss.str().c_str());
        printf("%s\n", ss.str().c_str());
        nbFrames = 0;
        lastTime += 1.0;
    }
}


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

// Process input function to close the window when ESC is pressed
void processInput(GLFWwindow *window)
{
   if (glfwGetKey(window , GLFW_KEY_ESCAPE) == GLFW_PRESS)
       glfwSetWindowShouldClose(window , true);
}