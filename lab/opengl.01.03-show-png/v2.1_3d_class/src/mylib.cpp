#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <sstream>

#include <mylib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h" // for load image utility 

// Process input function to close the window when ESC is pressed
void processInput(GLFWwindow *window)
{
   if (glfwGetKey(window , GLFW_KEY_ESCAPE) == GLFW_PRESS)
       glfwSetWindowShouldClose(window , true);
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

void OriginXYZ::display()
{
    // Use shader program
    glUseProgram(shaderProgram);

    // Set MVP matrix
    glm::mat4 model = glm::mat4(1.0f); // Model matrix
    // glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f)); // Move view to observe the 3D object
    glm::vec3 cameraPosition = glm::vec3(1.0f, 1.0f, 3.0f); // Set the camera position at (1, 1, 3)
    glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 upVector = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::mat4 view = glm::lookAt(cameraPosition, cameraTarget, upVector);

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f); // Projection matrix
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



// ==  Class My Picture ==
MyPicture::MyPicture(float scr_width, float scr_height)
{
    this->SCR_WIDTH = scr_width;
    this->SCR_HEIGHT = scr_height;
    init();
}

MyPicture::~MyPicture()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(this->shaderProgram);
}

// Initialize OpenGL settings
void MyPicture::init()
{
    
    initVAOBAO();
    initShader();

    // load texture
    int width = 0 , height = 0; 
    this->texture = loadTexture("cs-black-000.png", width, height);
}

void MyPicture::initVAOBAO(){
    // Create VAO and VBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // the first attribute: vertices
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // second attribute: texture
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void MyPicture::initShader(){
    // compiling the vertex shader
   unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
   glShaderSource(vertexShader , 1 , &vertexShaderSource , NULL);
   glCompileShader(vertexShader);

   // compiling the fragment shader
   unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
   glShaderSource(fragmentShader , 1 , &fragmentShaderSource , NULL);
   glCompileShader(fragmentShader);

   // create shader program and attached the shader
   shaderProgram = glCreateProgram();
   glAttachShader(shaderProgram , vertexShader);
   glAttachShader(shaderProgram , fragmentShader);
   glLinkProgram(shaderProgram);

   // free the shader resouces because they have been linkied
   glDeleteShader(vertexShader);
   glDeleteShader(fragmentShader);
}

// disay the picture
// Usage
/*
    display(0.0f, 0.0f, 0.0f, texture, shaderProgram);
*/
void MyPicture::display(float x, float y, float z){
    glUseProgram(this->shaderProgram);

    float near = 0.01f;
    float far = 10.0f;

    // create mvp matrix
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(x , y , z));  // Moving in z
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, near, far);
    glm::mat4 mvpMatrix = projection * view * model;
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram , "uMVPMatrix") , 1 , GL_FALSE , glm::value_ptr(mvpMatrix));

    // draw object with texture
    glBindTexture(GL_TEXTURE_2D , texture);  // draw texture
    glBindVertexArray(VAO); // draw vertex
    glDrawArrays(GL_TRIANGLES , 0 ,6); // draw
}

GLuint MyPicture::loadTexture(const char* path, int& width, int& height) {
    // By default, PNG images are written as the first row of pixel data corresponds to the topmost part of the image.
    // However, OpenGL coordinate system for texture is bottom-to-top. This is reason why we do vertically flop operator to the image
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path, &width, &height, 0, 4); // require RGBA: 4
    if (!data) {
        std::cerr << "Failed to load texture: " << path << std::endl;
        return 0;
    }

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data); // free data
    return texture;
}
