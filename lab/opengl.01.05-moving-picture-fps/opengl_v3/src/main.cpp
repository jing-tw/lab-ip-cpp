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
    //  因為圖檔資料是從上往下放資料, 所以需要做轉換, 以配合 OpenGL Texture 的座標系統
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

    stbi_image_free(data); // 释放内存
    return texture;
}

int main() {
    // 初始化GLFW
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
    
    // 初始化GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    
   
    // https://learnopengl.com/Getting-started/Textures
    
    float vertices[] = {
    // positions                     // texture coords
     0.5f,  0.5f,      1.0f, 1.0f,   // top right
     0.5f, -0.5f,      1.0f, 0.0f,   // bottom right
    -0.5f, -0.5f,      0.0f, 0.0f,   // bottom left

     0.5f,  0.5f,      1.0f, 1.0f,   // top right
     -0.5f, -0.5f,      0.0f, 0.0f,   // bottom left
    -0.5f,  0.5f,      0.0f, 1.0f    // top left 
     };

    //  Define the Vertices
    //  (若載入圖檔時, 沒有做  vertical flip, 顯示的圖檔就會是上下顛倒)
    //  這時, 就需要在這裡手動把紋理座標做上下鏡射
    // 下面的程式就是手動調整的例子
    // float vertices[] = {
    //     // 位置             // 纹理坐标
    //     -0.5f, -0.5f, 0.0f, 1.0f,     // vertice: left, down; texxt:
    //      0.5f, -0.5f, 1.0f, 1.0f,
    //      0.5f,  0.5f, 1.0f, 0.0f,

    //     -0.5f, -0.5f, 0.0f, 1.0f,
    //      0.5f,  0.5f, 1.0f, 0.0f,
    //     -0.5f,  0.5f, 0.0f, 0.0f,
    // };
 

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    const char* vertexShaderSource = R"(
        #version 330 core
        layout(location = 0) in vec2 aPos;
        layout(location = 1) in vec2 aTexCoord;
        uniform mat4 uMVPMatrix; // MVP matrix
        out vec2 TexCoord;
        void main() {
            gl_Position = uMVPMatrix * vec4(aPos.x, aPos.y, 0.0, 1.0);
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

   // 编译顶点着色器
   unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
   glShaderSource(vertexShader , 1 , &vertexShaderSource , NULL);
   glCompileShader(vertexShader);

   // Compile the shader
   unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
   glShaderSource(fragmentShader , 1 , &fragmentShaderSource , NULL);
   glCompileShader(fragmentShader);

   // 创建着色器程序并链接
   unsigned int shaderProgram = glCreateProgram();
   glAttachShader(shaderProgram , vertexShader);
   glAttachShader(shaderProgram , fragmentShader);
   glLinkProgram(shaderProgram);

   // 删除着色器，因为它们已经链接到程序中
   glDeleteShader(vertexShader);
   glDeleteShader(fragmentShader);

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

       // 使用着色器程序并绑定纹理
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
        // printf("offsetX = %f\n", offsetX);
 
       // glm::mat4 mvpMatrix = glm::mat4(1.0f); // Identity matrix for static triangle MVP
       glm::mat4 mvpMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(offsetX , 0.0f , 0.0f)); // Translate MVP for moving triangle
       glUniformMatrix4fv(glGetUniformLocation(shaderProgram , "uMVPMatrix") , 1 , GL_FALSE , glm::value_ptr(mvpMatrix));

       // draw object
       glBindTexture(GL_TEXTURE_2D , texture);  // draw texture
       glBindVertexArray(VAO); // draw vertex
       glDrawArrays(GL_TRIANGLES , 0 ,6); // draw

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

   // 清理资源
   glDeleteVertexArrays(1 , &VAO);
   glDeleteBuffers(1 , &VBO);
   glfwTerminate();
   
   return 0;
}

// Process input function to close the window when ESC is pressed
void processInput(GLFWwindow *window)
{
   if (glfwGetKey(window , GLFW_KEY_ESCAPE) == GLFW_PRESS)
       glfwSetWindowShouldClose(window , true);
}