
#include <glad/glad.h>

// MyPicture: Show a png picture on screen
// Usage:
/*
    MyPicture *picture = new MyPicture((float) SCR_WIDTH, (float) SCR_HEIGHT);
    while (!glfwWindowShouldClose(window)) {
        processInput(window); // Input processing

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers    
        picture->display(0.0f, 0.0f, 0.1f); // render the screen

        glfwSwapBuffers(window); // Swap buffers
        glfwPollEvents();        // Check for events

        objFPS.display(); // display fps
    }

    delete picture;
*/
class MyPicture
{
private:
    float SCR_WIDTH, SCR_HEIGHT;
    GLuint shaderProgram;
    GLuint VAO;
    GLuint VBO;
    static const int VertexToalNUM = 6;                                                                                         // total vertex number
    static const int Vertex_Attribute1_COMPONENT_NUM = 3;                                                                       // x, y, z
    static const int Vertex_Attribute2_COMPONENT_NUM = 2;                                                                       // no texture location
    static const int Vertex_Attribute1_COMPONENT_TOTAL_NUM = Vertex_Attribute1_COMPONENT_NUM + Vertex_Attribute2_COMPONENT_NUM; // one  vector size = 3 + 0
    
    float z = 0.1f;
    float vertices[VertexToalNUM * Vertex_Attribute1_COMPONENT_TOTAL_NUM] = {
    // positions                     // texture coords
     0.5f,  0.5f, z,  1.0f, 1.0f,   // top right
     0.5f, -0.5f, z,  1.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, z,  0.0f, 0.0f,   // bottom left

     0.5f,  0.5f, z,  1.0f, 1.0f,   // top right
     -0.5f, -0.5f, z, 0.0f, 0.0f,   // bottom left
    -0.5f,  0.5f, z,  0.0f, 1.0f    // top left 
     };

     GLuint texture; 

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
public:
    MyPicture(float scr_width, float scr_height);
    void display(float x, float y, float z);
    ~MyPicture();

private:
    void init();
    void initShader();
    void initVAOBAO();
    GLuint loadTexture(const char* path, int& width, int& height);
};
