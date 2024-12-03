#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h" // for load image utility
#include <iostream>

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
    float z = 0.1f;
    float vertices[] = {
    // positions                     // texture coords
     0.5f,  0.5f, z,     1.0f, 1.0f,   // top right
     0.5f, -0.5f, z,  1.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, z,     0.0f, 0.0f,   // bottom left

     0.5f,  0.5f, z,     1.0f, 1.0f,   // top right
     -0.5f, -0.5f, z,     0.0f, 0.0f,   // bottom left
    -0.5f,  0.5f, z,     0.0f, 1.0f    // top left 
     };

    unsigned int VBO, VAO;
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

    

    const char* vertexShaderSource = R"(
        #version 330 core
        layout(location = 0) in vec3 aPos;
        layout(location = 1) in vec2 aTexCoord;
        out vec2 TexCoord;
        void main() {
            // gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
            gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
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

   // 编译片段着色器
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

   // 加载纹理
   int width = 0 , height = 0; 
   GLuint texture = loadTexture("cs-black-000.png", width,height); // chage to your PNG path

   while (!glfwWindowShouldClose(window)) {
       // 清屏
       glClear(GL_COLOR_BUFFER_BIT);

       // 使用着色器程序并绑定纹理
       glUseProgram(shaderProgram);
       glBindTexture(GL_TEXTURE_2D , texture);
       glBindVertexArray(VAO);
       glDrawArrays(GL_TRIANGLES , 0 ,6); // 绘制矩形

       glfwSwapBuffers(window);
       glfwPollEvents();
   }

   // 清理资源
   glDeleteVertexArrays(1 , &VAO);
   glDeleteBuffers(1 , &VBO);
   glfwTerminate();
   
   return 0;
}