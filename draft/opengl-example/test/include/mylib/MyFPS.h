
#include <glad/glad.h>

// FPS: Calucate and print the fps on console
//Usage:
/*
    FPS *objFPS = new FPS();
    while (!glfwWindowShouldClose(window)) {
        
        ...
        objFPS->display(); // display fps value
    }
*/
class MyFPS
{
private:
    // Variables for FPS calculation
    double lastTime = glfwGetTime();
    int nbFrames = 0;
    double lastFPS = -1.0f;
    double fps = -1.0f;

public:
    MyFPS();
    // void display();
    double display(bool bShow);
};
