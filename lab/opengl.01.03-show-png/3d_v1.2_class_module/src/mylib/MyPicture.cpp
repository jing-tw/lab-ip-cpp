#include <iostream>
#include <sstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <mylib/MyPicture.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h" // for load image utility 



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
