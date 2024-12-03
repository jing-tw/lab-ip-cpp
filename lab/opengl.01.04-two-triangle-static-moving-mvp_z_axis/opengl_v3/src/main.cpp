#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <sstream>

// Function declarations
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// Settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// Shader sources
const char *vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
uniform mat4 uMVPMatrix; // MVP matrix
void main()
{
    gl_Position = uMVPMatrix * vec4(aPos, 1.0);
})";

const char *fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;
void main()
{
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); // Orange color
})";

int main()
{
    // Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a window
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Two Triangles", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Load OpenGL function pointers using GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Build and compile shader program
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Check for vertex shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Check for fragment shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Link shaders into a program
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Set up vertex data and buffers for two triangles
    float staticTriangleVertices[] = {
        -0.8f, -0.8f, 0.0f,
         -0.3f, -0.8f, 0.0f,
         -0.3f,  0.8f, 0.0f  
    };
    
    float dx = 0.3;
    float movingTriangleVertices[] = {
        -0.3f + dx, -0.3f, 0.0f,
         0.3f + dx, -0.3f, 0.0f,
         0.0f + dx,  0.3f, 0.0f 
    };

    unsigned int VBOs[2], VAOs[2];
    
    // Generate and bind VAO and VBO for static triangle
    glGenVertexArrays(1, &VAOs[0]);
    glGenBuffers(1, &VBOs[0]);
    
    glBindVertexArray(VAOs[0]);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(staticTriangleVertices), staticTriangleVertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

   // Generate and bind VAO and VBO for moving triangle
   glGenVertexArrays(1 , &VAOs[1]);
   glGenBuffers(1 , &VBOs[1]);

   glBindVertexArray(VAOs[1]);

   glBindBuffer(GL_ARRAY_BUFFER , VBOs[1]);
   glBufferData(GL_ARRAY_BUFFER , sizeof(movingTriangleVertices) , movingTriangleVertices , GL_STATIC_DRAW);

   glVertexAttribPointer(0 , 3 , GL_FLOAT , GL_FALSE , 3 * sizeof(float) , (void*)0);
   glEnableVertexAttribArray(0);

   // Unbind the VAO (optional)
   glBindBuffer(GL_ARRAY_BUFFER , 0); 
   glBindVertexArray(0); 

   // Variables for moving triangle position
   float offsetX = 0.0f; // Moving triangle horizontal offset

   // Render loop
   while (!glfwWindowShouldClose(window))
   {
       // Input processing
       processInput(window);

       // Update moving triangle position based on input (arrow keys)
       if (glfwGetKey(window , GLFW_KEY_LEFT) == GLFW_PRESS)
           offsetX -= 0.01f;
       if (glfwGetKey(window , GLFW_KEY_RIGHT) == GLFW_PRESS)
           offsetX += 0.01f;

       // Render
       glClearColor(0.2f , 0.3f , 0.3f , 1.0f);
       glClear(GL_COLOR_BUFFER_BIT);

       glUseProgram(shaderProgram);
       
       // Use shader program for static triangle
       glm::mat4 mvpStatic = glm::mat4(1.0f); // Identity matrix for static triangle MVP
       glUniformMatrix4fv(glGetUniformLocation(shaderProgram , "uMVPMatrix") , 1 , GL_FALSE , glm::value_ptr(mvpStatic));

       // Draw static triangle
       glBindVertexArray(VAOs[0]);
       glDrawArrays(GL_TRIANGLES , 0 , 3);


       glm::mat4 model = glm::mat4(1.0f);
       // glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(offsetX, 0.0f, 0.0f)); // moving in x
       // glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, offsetX, 0.0f));  // Moving in y
       glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, offsetX));  // Moving in z
       glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10.0f);
       glm::mat4 mvpMatrix = projection * view * model;

       glm::mat4 mvpMoving = mvpMatrix;
       printf("%f\n", offsetX);
       // Use shader program for moving triangle
       // Translate MVP for moving triangle
       // Translate
       // glm::mat4 mvpMoving = glm::mat4(1.0f); // Identity matrix for static triangle MVP
       // glm::mat4 mvpMoving = glm::translate(glm::mat4(1.0f), glm::vec3(offsetX , 0.0f ,  0.0f));  // Moving in x
       // glm::mat4 mvpMoving = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, offsetX,  0.0f));  // Moving in y
       // glm::mat4 mvpMoving = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, offsetX));  // Moving in z
       

       // Rotation
       // glm::mat4 mvpMoving = glm::rotate(glm::mat4(1.0f), offsetX, glm::vec3(1.0f, 0.0f, 0.0f)); // Rotate around x-axis
       // glm::mat4 mvpMoving = glm::rotate(glm::mat4(1.0f), offsetX, glm::vec3(0.0f, 1.0f, 0.0f)); // Rotate around y-axis
       // glm::mat4 mvpMoving = glm::rotate(glm::mat4(1.0f), offsetX, glm::vec3(0.0f, 0.0f, 1.0f)); // Rotate around z-axis
       
       glUniformMatrix4fv(glGetUniformLocation(shaderProgram , "uMVPMatrix") , 1 , GL_FALSE , glm::value_ptr(mvpMoving));

       // Draw moving triangle
       glBindVertexArray(VAOs[1]);
       glDrawArrays(GL_TRIANGLES , 0 , 3);

       // Swap buffers and poll events
       glfwSwapBuffers(window);
       glfwPollEvents();
   }

   // Cleanup resources
   glDeleteVertexArrays(2 , VAOs);
   glDeleteBuffers(2 , VBOs);
   glDeleteProgram(shaderProgram);

   glfwTerminate();
   return 0;
}

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