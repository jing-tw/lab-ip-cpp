#include <mylib/mylibopengl.h>
#include <iostream> // debug

// openGL
bool toggleFullscreen(GLFWwindow* window) {
    static int width = -1, height = -1;
    static int xpos = -1, ypos = -1;

    if (glfwGetWindowMonitor(window)) {
        // Switch to windowed mode
        if(width != -1 && height != -1){
            glfwSetWindowMonitor(window, NULL, xpos, ypos, width, height, 0);
            // printf("Windowed mode: xpos = %d, ypos = %d, height = %d, width = %d \n", xpos, ypos, height, width);
        }else{
            return false;
        }
    } else {
        // Save original window position and size
        glfwGetWindowPos(window, &xpos, &ypos);
        glfwGetWindowSize(window, &width, &height);
        // printf("Save old data: xpos = %d, ypos = %d, height = %d, width = %d \n", xpos, ypos, height, width);

        // Switch to fullscreen mode
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
        // printf("Full screen mode: monitor = %p, mode->height = %d, mode->width = %d, mode->refreshRate = %d \n", monitor, mode->height, mode->width, mode->refreshRate);
    }

    return true;
}

void framebuffer_size_callback(GLFWwindow* window,int width,int height)
{
   glViewport(0 , 0 , width , height); 
}



