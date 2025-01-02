#include <iostream> // debug

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include <mylib/mylib.h>

void toggleFullscreen(GLFWwindow* window) {
    static int width = -1, height = -1;
    static int xpos = -1, ypos = -1;

    if (glfwGetWindowMonitor(window)) {
        // Switch to windowed mode
        if(width != -1 && height != -1){
            glfwSetWindowMonitor(window, NULL, xpos, ypos, width, height, 0);
            // printf("Windowed mode: xpos = %d, ypos = %d, height = %d, width = %d \n", xpos, ypos, height, width);
        }
    } else {
        // save original location
        glfwGetWindowPos(window, &xpos, &ypos);
        glfwGetWindowSize(window, &width, &height);
        // printf("Save old data: xpos = %d, ypos = %d, height = %d, width = %d \n", xpos, ypos, height, width);

        // Switch to fullscreen mode
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
        // printf("Full screen mode: monitor = %p, mode->height = %d, mode->width = %d, mode->refreshRate = %d \n", monitor, mode->height, mode->width, mode->refreshRate);
    }
}

// Framebuffer size callback function to adjust viewport when window is resized
void framebuffer_size_callback(GLFWwindow* window,int width,int height)
{
   glViewport(0 , 0 , width , height); 
}

OriginXYZ::OriginXYZ()
{
    init();
}

OriginXYZ::~OriginXYZ()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
}

// Initialize OpenGL settings
void OriginXYZ::init()
{
    // Create VAO and VBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // init attribute 1: (x, y, z)
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glVertexAttribPointer(0, Vertex_Attribute1_COMPONENT_NUM, GL_FLOAT, GL_FALSE, Vertex_Attribute1_COMPONENT_TOTAL_NUM * sizeof(GLfloat), (GLvoid *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Compile shaders
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Create shader program
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // free shader resource
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void OriginXYZ::display(glm::mat4 view, glm::mat4 projection)
{
    // Use shader program
    glUseProgram(shaderProgram);

    // Set MVP matrix
    glm::mat4 model = glm::mat4(1.0f); // Model matrix
    // glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f)); // Move view to observe the 3D object
    // glm::vec3 cameraPosition = glm::vec3(1.0f, 1.0f, 3.0f); // Set the camera position at (1, 1, 3)
    // glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    // glm::vec3 upVector = glm::vec3(0.0f, 1.0f, 0.0f);
    // glm::mat4 view = glm::lookAt(cameraPosition, cameraTarget, upVector);

    // glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f); // Projection matrix
    glm::mat4 mvp = projection * view * model;                                                           // MVP matrix

    // Get uniform location and pass MVP matrix
    GLuint mvpLocation = glGetUniformLocation(shaderProgram, "mvp");
    glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, glm::value_ptr(mvp));

    // Draw X axis (red)
    GLuint lineColorLocation = glGetUniformLocation(shaderProgram, "lineColor");
    glUniform3f(lineColorLocation, 1.0f, 0.0f, 0.0f); // Red color
    glBindVertexArray(VAO);
    glDrawArrays(GL_LINES, 0, 2); // Draw X axis

    // Draw Y axis (green)
    glUniform3f(lineColorLocation, 0.0f, 1.0f, 0.0f); // Green color
    glDrawArrays(GL_LINES, 2, 2);                     // Draw Y axis

    // Draw Z axis (blue)
    glUniform3f(lineColorLocation, 0.0f, 0.0f, 1.0f); // Blue color
    glDrawArrays(GL_LINES, 4, 2);                     // Draw Z axis

    glBindVertexArray(0);
}