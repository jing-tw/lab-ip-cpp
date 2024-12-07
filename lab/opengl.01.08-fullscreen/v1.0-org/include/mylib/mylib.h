void processInput(GLFWwindow *window);
void framebuffer_size_callback(GLFWwindow* window,int width,int height);
void toggleFullscreen(GLFWwindow* window);

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
    void display(glm::mat4 view, glm::mat4 projection);
    ~OriginXYZ();

private:
    void init();
};

// // FPS: Calucate and print the fps on console
// //Usage:
// /*
//     FPS *objFPS = new FPS();
//     while (!glfwWindowShouldClose(window)) {
        
//         ...
//         objFPS->display(); // display fps value
//     }
// */
// class FPS
// {
// private:
//     // Variables for FPS calculation
//     double lastTime = glfwGetTime();
//     int nbFrames = 0;
//     double lastFPS = -1.0f;
//     double fps = -1.0f;

// public:
//     FPS();
//     // void display();
//     double display(bool bShow);
// };

