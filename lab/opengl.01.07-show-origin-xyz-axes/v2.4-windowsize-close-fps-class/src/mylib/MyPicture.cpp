
#include <mylib/MyPicture.h>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h" // for load image utility 

MyPicture::MyPicture(){
    this->initVertics();
}

void MyPicture::print(){
    #ifdef __MYDEBUG__
    printf("[__MYDEBUG__] class name = %s\n", "MyPicture");
    #endif
}

// init opengl vertics
bool MyPicture::initVertics(){
    float d = 0.5f;
    float z = -0.0f;
    float vertices[] = { // Format: positions, texture coords
            d,  d, z,     1.0f, 1.0f,   // top right
            d, -d, z,     1.0f, 0.0f,   // bottom right
            -d, -d, z,     0.0f, 0.0f,  // bottom left

            d,  d, z,     1.0f, 1.0f,   // top right
            -d, -d, z,     0.0f, 0.0f,  // bottom left
            -d,  d, z,     0.0f, 1.0f   // top left 
            };
    unsigned int attr1_element_num = 3;  // x, y, z
    unsigned int attr2_element_num = 2;  // texture
    this->initVAOBAO(vertices, sizeof(vertices), attr1_element_num, attr2_element_num);

    return true;
}

bool MyPicture::load(const char *path)
{
    this->path = path;
    this->texture = loadTexture(path, width, height); // chage to your PNG path
    if (this->texture == 0)
        return false;

    initShader();
    return true;
}

GLuint MyPicture::loadTexture(const char *path, int &width, int &height)
{
    // By default, PNG images are written as the first row of pixel data corresponds to the topmost part of the image.
    // However, OpenGL coordinate system for texture is bottom-to-top. This is reason why we do vertically flop operator to the image
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(path, &width, &height, 0, 4); // require RGBA: 4
    if (!data)
    {
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

bool MyPicture::initVAOBAO(float *vertices, unsigned int size, unsigned int attr1_element_num, unsigned int attr2_element_num)
{
    glGenVertexArrays(1, &(this->VAO));
    glGenBuffers(1, &(this->VBO));
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // printf("size = %d\n", size);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

    unsigned int total_element = attr1_element_num + attr2_element_num;
    // 1st attribute: vertices
    glVertexAttribPointer(0, attr1_element_num, GL_FLOAT, GL_FALSE, total_element * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // 2st attribute: texture
    unsigned attr_index = attr1_element_num; // end of the attr_1
    glVertexAttribPointer(1, attr2_element_num, GL_FLOAT, GL_FALSE, total_element * sizeof(float), (void *)(attr_index * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Unbind the VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return true;
}

bool MyPicture::display(float x, float y, float z, glm::mat4 view, glm::mat4 projection)
{
    glUseProgram(this->shaderProgram);

    // create mvp matrix
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z)); // Move to x, y, z
    glm::mat4 mvpMatrix = projection * view * model;
    glUniformMatrix4fv(glGetUniformLocation(this->shaderProgram, "uMVPMatrix"), 1, GL_FALSE, glm::value_ptr(mvpMatrix));

    // draw object with texture
    glBindTexture(GL_TEXTURE_2D, texture); // draw texture
    glBindVertexArray(this->VAO);          // draw vertex
    glDrawArrays(GL_TRIANGLES, 0, 6);      // draw

    return true;
}

bool MyPicture::initShader()
{
    const char *vertexShaderSource = R"(
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

    const char *fragmentShaderSource = R"(
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
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // compile the fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Create a shader program
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // delete the shaders because they are already binded to the procedure
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return true;
}

MyPicture::~MyPicture()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(this->shaderProgram);
}