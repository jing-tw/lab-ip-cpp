#include <mylib/mylib.h>
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

// OpenCV + OpenGL
GLuint mat2Texture(Mat image) {
    // Convert image to RGB format for OpenGL
    cvtColor(image, image, COLOR_BGR2RGB);

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.cols, image.rows, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image.data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return texture;
}

