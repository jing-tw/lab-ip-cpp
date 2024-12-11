

void processInput(GLFWwindow *window);
void framebuffer_size_callback(GLFWwindow* window,int width,int height);

// OriginXYZ: Show x, y,z axes
// Usage
/*
    OriginXYZ *obj = new OriginXYZ();

    while (!glfwWindowShouldClose(window)) {
        obj->display(); // Render the scene
        ...
    }

    delete obj;
*/
class OriginXYZ
{
private:
    GLuint shaderProgram;
    GLuint VAO;
    GLuint VBO;
    static const int VertexToalNUM = 6;                                                                                         // total vertex number
    static const int Vertex_Attribute1_COMPONENT_NUM = 3;                                                                       // x, y, z
    static const int Vertex_Attribute2_COMPONENT_NUM = 0;                                                                       // no texture location
    static const int Vertex_Attribute1_COMPONENT_TOTAL_NUM = Vertex_Attribute1_COMPONENT_NUM + Vertex_Attribute2_COMPONENT_NUM; // one  vector size = 3 + 0
    GLfloat vertices[VertexToalNUM * Vertex_Attribute1_COMPONENT_TOTAL_NUM] = {
        // X axis
        -1.0f, 0.0f, 0.0f,
         1.0f, 0.0f, 0.0f,
        // Y axis
         0.0f, -1.0f, 0.0f,
         0.0f,  1.0f, 0.0f,
        // Z axis
         0.0f, 0.0f, -1.0f,
         0.0f, 0.0f,  1.0f,
    };
    const char *vertexShaderSource = R"(
            #version 330 core
            layout(location = 0) in vec3 position;
            uniform mat4 mvp;
            void main() {
                gl_Position = mvp * vec4(position, 1.0);
            }
            )";

    const char *fragmentShaderSource = R"(
            #version 330 core
            out vec4 color;
            uniform vec3 lineColor;
            void main() {
                color = vec4(lineColor, 1.0); // Set the color
            }
            )";

public:
    OriginXYZ();
    void display();
    ~OriginXYZ();

private:
    void init();
};

// FPS: Calucate and print the fps on console
//Usage:
/*
    FPS *objFPS = new FPS();
    while (!glfwWindowShouldClose(window)) {
        
        ...
        objFPS->display(); // display fps value
    }
*/
class FPS
{
private:
    // Variables for FPS calculation
    double lastTime = glfwGetTime();
    int nbFrames = 0;

public:
    FPS();
    void display();
};


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
