#include <iostream>
#include <sstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <mylib/MyFPS.h>

MyFPS::MyFPS()
{
}

double MyFPS::display(bool bShow)
{
    // FPS calculation
    double currentTime = glfwGetTime();
    nbFrames++;
    if (currentTime - lastTime >= 1.0)
    { // If lastTime is more than 1 sec ago
       
        // double fps = double(nbFrames) / (currentTime - lastTime);
        fps = double(nbFrames) / (currentTime - lastTime);
        lastFPS = fps;

        if(bShow){
            std::stringstream ss;
            ss << "FPS: " << fps;
            // glfwSetWindowTitle(window, ss.str().c_str());
            printf("%s\n", ss.str().c_str());
        }
        nbFrames = 0;
        lastTime += 1.0;

        return fps;
    }

    return lastFPS;
}
