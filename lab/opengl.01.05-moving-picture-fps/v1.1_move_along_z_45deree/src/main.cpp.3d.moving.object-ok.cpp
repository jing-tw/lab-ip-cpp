#include <iostream>
#include <sstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h" // for load image utility


void processInput(GLFWwindow *window);

GLuint loadTexture(const char* path, int& width, int& height) {
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

bool CreateVertices(float *vertices, unsigned int size, unsigned int *VAO, unsigned int *VBO) {
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

bool Draw(unsigned int VAO, float x, float y, float z, GLuint texture, unsigned int shaderProgram){
    // adjuest shader for moving
    glm::mat4 mvpMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(x , y , z)); // Translate MVP for moving triangle
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram , "uMVPMatrix") , 1 , GL_FALSE , glm::value_ptr(mvpMatrix));

    // draw object with texture
    glBindTexture(GL_TEXTURE_2D , texture);  // draw texture
    glBindVertexArray(VAO); // draw vertex
    glDrawArrays(GL_TRIANGLES , 0 ,6); // draw

    return true;
}

// unsigned int shaderProgram = glCreateProgram();
bool InitShader(unsigned int shaderProgram){
    const char* vertexShaderSource = R"(
        #version 330 core
        layout(location = 0) in vec3 aPos;
        layout(location = 1) in vec2 aTexCoord;
        uniform mat4 uMVPMatrix; // MVP matrix
        out vec2 TexCoord;
        void main() {
            gl_Position = uMVPMatrix * vec4(aPos.x, aPos.y, aPos.z, 1.0);
            TexCoord = aTexCoord;
        }
    )";

   const char* fragmentShaderSource = R"(
       #version 330 core
       out vec4 FragColor;
       in vec2 TexCoord;
       uniform sampler2D texture1;
       void main() {
           FragColor = texture(texture1 , TexCoord);
       }
   )";

   // compile the vertex shader
   unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
   glShaderSource(vertexShader , 1 , &vertexShaderSource , NULL);
   glCompileShader(vertexShader);

   // compile the fragment shader
   unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
   glShaderSource(fragmentShader , 1 , &fragmentShaderSource , NULL);
   glCompileShader(fragmentShader);

   // Create a shader program
   // unsigned int shaderProgram = glCreateProgram();
   glAttachShader(shaderProgram , vertexShader);
   glAttachShader(shaderProgram , fragmentShader);
   glLinkProgram(shaderProgram);

   // delete the shaders because they are already binded to the procedure
   glDeleteShader(vertexShader);
   glDeleteShader(fragmentShader);
} 

int main() {
    // init GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Display PNG", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // init GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    
    unsigned int num = 9;
    unsigned int *VBOs = new unsigned int[num];
    unsigned int *VAOs = new unsigned int[num];
    unsigned int i = 0;

    unsigned int shaderProgram = glCreateProgram();
    InitShader(shaderProgram);

    // create VAO, VBO from vertices
    float d = 0.5f;
    float z = 0.5f;
    for (int i = 0; i < num; i++){
        // d = d + 0.1f;
        float vertices[] = { // Format: positions, texture coords
            d,  d, z,     1.0f, 1.0f,   // top right
            d, -d, z,     1.0f, 0.0f,   // bottom right
            -d, -d, z,     0.0f, 0.0f,  // bottom left

            d,  d, z,     1.0f, 1.0f,   // top right
            -d, -d, z,     0.0f, 0.0f,  // bottom left
            -d,  d, z,     0.0f, 1.0f   // top left 
            };
        CreateVertices(vertices, sizeof(vertices), &VAOs[i], &VBOs[i]);
    }

    // Variables for FPS calculation
    double lastTime = glfwGetTime();
    int nbFrames = 0;

   // load texture
   int width = 0 , height = 0; 
   GLuint texture = loadTexture("cs-black-000.png", width,height); // chage to your PNG path

   float offsetX = 0.0f; // Moving triangle horizontal offset
   bool bUP = false;
   while (!glfwWindowShouldClose(window)) {
       // Input processing
       processInput(window);

       glClear(GL_COLOR_BUFFER_BIT);

       // use the shader program
       glUseProgram(shaderProgram);

       // postion
       if (offsetX <= 0.0f && bUP == false){
            bUP = true;
       }

        if(offsetX > 1.0f && bUP == true){
            bUP = false;
        }

        if(bUP){
            offsetX += 0.01f;
        }else{
            offsetX -= 0.01f;
        }
 
       // glm::mat4 mvpMatrix = glm::mat4(1.0f); // Identity matrix for static triangle MVP
       for(int i = 0; i < num; i++){
            switch(i){
            case 0:
                Draw(VAOs[i], offsetX , 0.0f , 0.0f, texture, shaderProgram);
                break;
            case 1:
                Draw(VAOs[i], -offsetX , 0.0f , 0.0f, texture, shaderProgram);
                break;
            case 2:
                Draw(VAOs[i], 0.0f, offsetX, 0.0f, texture, shaderProgram);
                break;
            case 3:
                Draw(VAOs[i], 0.0f, -offsetX, 0.0f, texture, shaderProgram);
                break;
            case 4:
                Draw(VAOs[i], offsetX , offsetX , 0.0f, texture, shaderProgram);
                break;
            case 5:
                Draw(VAOs[i], -offsetX , -offsetX , 0.0f, texture, shaderProgram);
                break;
            case 6:
                Draw(VAOs[i], -offsetX , offsetX , 0.0f, texture, shaderProgram);
                break;
            case 7:
                Draw(VAOs[i], offsetX , -offsetX , 0.0f, texture, shaderProgram);
                break;
            case 8:
                Draw(VAOs[i], 0.0f, 0.0f, offsetX, texture, shaderProgram);
                break;
            default:
                Draw(VAOs[i], 0.0f , 0.0f , 0.0f, texture, shaderProgram);
                break;
            }
       }

       Draw(VAOs[0], 0.0f, 0.0f, 0.0f, texture, shaderProgram);

       glfwSwapBuffers(window);
       glfwPollEvents();

       // FPS calculation
        double currentTime = glfwGetTime();
        nbFrames++;
        if (currentTime - lastTime >= 1.0) { // If lastTime is more than 1 sec ago
            double fps = double(nbFrames) / (currentTime - lastTime);
            std::stringstream ss;
            ss << "FPS: " << fps;
            // glfwSetWindowTitle(window, ss.str().c_str());
            printf("%s\n", ss.str().c_str());
            nbFrames = 0;
            lastTime += 1.0;
        }
   }

   // free resource
   glDeleteVertexArrays(num , VAOs);
   glDeleteBuffers(num , VBOs);

   glfwTerminate();

   delete [] VBOs;
   delete [] VAOs;

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