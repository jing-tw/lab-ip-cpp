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

