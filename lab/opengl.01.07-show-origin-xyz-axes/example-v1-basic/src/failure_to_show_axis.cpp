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

void createAxisLines(float* vertices, int& index);
bool CreateVerticesAxis(float *vertices, unsigned int size, unsigned int *VAO, unsigned int *VBO);
bool InitShaderAxis(unsigned int shaderProgram);

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
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Two Triangles. Press [Left] & [Right] keys.", NULL, NULL);
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

    // define near and far for perspective view
    float near = 1.0f;
    float far = 100.0f;

    // Set up vertex data and buffers for two triangles
    float staticTriangleVertices[] = {
        -0.8f, -0.8f, 0.0f,
         -0.3f, -0.8f, 0.0f,
         -0.3f,  0.8f, 0.0f  
    };
    
    float dx = 0.3;
    float z = -2.0f;   // the value between near and far (-1.0 ~ -10.0)
    float movingTriangleVertices[] = {
        -0.3f + dx, -0.3f, z,
         0.3f + dx, -0.3f, z,
         0.0f + dx,  0.3f, z 
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


    // Axis
    // Link shaders into a program
    unsigned int shaderProgramAxis = glCreateProgram();
    InitShaderAxis(shaderProgramAxis);

    // init Vertics
    unsigned int VBOsAxis[1], VAOsAxis[1];
   {

        const int axisVerticesCount = (6 + (18 * (9))) * 3; // Axes + ticks for each axis
        float axisVertices[axisVerticesCount];
            
        int index = 0;
            
        createAxisLines(axisVertices, index);

       

        // Generate and bind VAO and VBO for axis lines and ticks
        glGenVertexArrays(1 , &VAOsAxis[0]);
        glGenBuffers(1 , &VBOsAxis[0]);

        glBindVertexArray(VAOsAxis[0]);

        glBindBuffer(GL_ARRAY_BUFFER , VBOsAxis[0]);
        glBufferData(GL_ARRAY_BUFFER , sizeof(axisVertices) , axisVertices , GL_STATIC_DRAW);

        glVertexAttribPointer(0 , 3 , GL_FLOAT , GL_FALSE , 3 * sizeof(float) , (void*)0);
        glEnableVertexAttribArray(0);

        // Unbind the VAO (optional)
        glBindBuffer(GL_ARRAY_BUFFER , 0); 
        glBindVertexArray(0);
   }

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

       // glm::mat4 model = glm::mat4(1.0f);

       // Translate: by change the model matrix
       // glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(offsetX, 0.0f, 0.0f)); // moving in x
       // glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, offsetX, 0.0f));  // Moving in y
       glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, offsetX));  // Moving in z
       
       // Rotation
       // glm::mat4 model = glm::rotate(glm::mat4(1.0f), offsetX, glm::vec3(1.0f, 0.0f, 0.0f)); // Rotate around x-axis
       // glm::mat4 model = glm::rotate(glm::mat4(1.0f), offsetX, glm::vec3(0.0f, 1.0f, 0.0f)); // Rotate around y-axis
       // glm::mat4 model = glm::rotate(glm::mat4(1.0f), offsetX, glm::vec3(0.0f, 0.0f, 1.0f)); // Rotate around z-axis

       // glm::mat4 view = glm::mat4(1.0f);
       glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);  // set the camera at the (0, 0, 3) 
       glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
       glm::vec3 upVector = glm::vec3(0.0f, 1.0f, 0.0f);
       glm::mat4 view = glm::lookAt(cameraPosition, cameraTarget, upVector);

       glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, near, far);  // near = 1, far = 100
       glm::mat4 mvpMatrix = projection * view * model;

       printf("offset = %f\n", offsetX);
       glUniformMatrix4fv(glGetUniformLocation(shaderProgram , "uMVPMatrix") , 1 , GL_FALSE , glm::value_ptr(mvpMatrix));

       // Draw moving triangle
       glBindVertexArray(VAOs[1]);
       glDrawArrays(GL_TRIANGLES , 0 , 3);


       // Axis
       glUseProgram(shaderProgramAxis);

       // Draw axis lines and ticks
       int index = 0;
       glBindVertexArray(VAOsAxis[0]);
       glDrawArrays(GL_LINES , index/6*6, index/6*6+6);

       // Swap buffers and poll events
       glfwSwapBuffers(window);
       glfwPollEvents();
   }

   // Cleanup resources
   glDeleteVertexArrays(2 , VAOs);
   glDeleteBuffers(2 , VBOs);
   glDeleteProgram(shaderProgram);

   // Axis Part
    glDeleteVertexArrays(1 , VAOsAxis);
   glDeleteBuffers(1 , VBOsAxis);
   glDeleteProgram(shaderProgramAxis);

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


// Function to create axis lines
void createAxisLines(float* vertices, int& index)
{
    float z = 2.0f;
    // X-axis (Red)
    vertices[index++] = -10.0f; vertices[index++] = 0.0f; vertices[index++] = z; // Start
    vertices[index++] = 10.0f;  vertices[index++] = 0.0f; vertices[index++] = z; // End

    // Y-axis (Green)
    vertices[index++] = 0.0f;   vertices[index++] = -10.0f; vertices[index++] = z; // Start
    vertices[index++] = 0.0f;   vertices[index++] = 10.0f;  vertices[index++] = z; // End

    // Z-axis (Blue)
    vertices[index++] = 0.0f;   vertices[index++] = 0.0f;   vertices[index++] = -10.0f; // Start
    vertices[index++] = 0.0f;   vertices[index++] = 0.0f;   vertices[index++] = 10.0f; // End

    // Create ticks for each axis
    for (float i = -9.0f; i <= 9.0f; i += 1.0f) {
        // X-axis ticks
        if (i != 0) {
            vertices[index++] = i;     vertices[index++] = -0.2f; vertices[index++] = 0.0f;
            vertices[index++] = i;     vertices[index++] =  0.2f; vertices[index++] = 0.0f;
        }
        // Y-axis ticks
        if (i != 0) {
            vertices[index++] = -0.2f; vertices[index++] = i;     vertices[index++] = 0.0f;
            vertices[index++] =  0.2f; vertices[index++] = i;     vertices[index++] = 0.0f;
        }
        // Z-axis ticks
        if (i != 0) {
            vertices[index++] = 0.0f;   vertices[index++] = -0.2f; vertices[index++] = i;
            vertices[index++] = 0.0f;   vertices[index++] =  0.2f; vertices[index++] = i;
        }
    }

}

// CreateVerticesAxis: Create VBO VAO for axis
// Usage:
/*
CreateVerticesAxis(vertices, sizeof(vertices), &VAOs[i], &VBOs[i]);
*/
bool CreateVerticesAxis(float *vertices, unsigned int size, unsigned int *VAO, unsigned int *VBO) {
    glGenVertexArrays(1, VAO);
    glGenBuffers(1, VBO);
    glBindVertexArray(*VAO);

    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

    // 1st attribute: vertices
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // 2st attribute: texture
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Unbind the VAO 
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    
    return true;
}

// InitShaderAxis: initial the shader for Axis
// Usage:
/*
    unsigned int shaderProgram = glCreateProgram();
    InitShader(shaderProgram);

    while(1){
         glUseProgram(shaderProgram);
    }
*/
bool InitShaderAxis(unsigned int shaderProgram){
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
            FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); // Default color
        })";

   // compile the vertex shader
   unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
   glShaderSource(vertexShader , 1 , &vertexShaderSource , NULL);
   glCompileShader(vertexShader);

   // compile the fragment shader
   unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
   glShaderSource(fragmentShader , 1 , &fragmentShaderSource , NULL);
   glCompileShader(fragmentShader);

   // Create a shader program
   glAttachShader(shaderProgram , vertexShader);
   glAttachShader(shaderProgram , fragmentShader);
   glLinkProgram(shaderProgram);

   // delete the shaders because they are already binded to the procedure
   glDeleteShader(vertexShader);
   glDeleteShader(fragmentShader);
} 