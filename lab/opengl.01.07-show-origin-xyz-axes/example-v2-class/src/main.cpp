#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

class OriginXYZ{
    public:
        GLuint shaderProgram;
        GLuint VAO;
        GLuint VBO;
        static const int VertexToalNUM = 6; // total vertex number
        static const int Vertex_Attribute1_COMPONENT_NUM = 3; // x, y, z
        static const int Vertex_Attribute2_COMPONENT_NUM = 0; // no texture location
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

        const char* vertexShaderSource = R"(
            #version 330 core
            layout(location = 0) in vec3 position;
            uniform mat4 mvp;
            void main() {
                gl_Position = mvp * vec4(position, 1.0);
            }
            )";

            const char* fragmentShaderSource = R"(
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


OriginXYZ::OriginXYZ(){
    init();
}

OriginXYZ::~OriginXYZ(){
    glDeleteVertexArrays(1,&VAO); 
    glDeleteBuffers(1,&VBO); 
    glDeleteProgram(shaderProgram);
}

// Initialize OpenGL settings
void OriginXYZ::init() {
    // Create VAO and VBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // init attribute 1: (x, y, z)
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glVertexAttribPointer(0, Vertex_Attribute1_COMPONENT_NUM, GL_FLOAT, GL_FALSE, Vertex_Attribute1_COMPONENT_TOTAL_NUM  * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 

        // Compile shaders
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Create shader program
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // free shader resource
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void OriginXYZ::display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers

    // Use shader program
    glUseProgram(shaderProgram);

    // Set MVP matrix
    glm::mat4 model = glm::mat4(1.0f); // Model matrix
    // glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f)); // Move view to observe the 3D object
    glm::vec3 cameraPosition = glm::vec3(1.0f, 1.0f, 3.0f); // Set the camera position at (1, 1, 3)
       glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
       glm::vec3 upVector = glm::vec3(0.0f, 1.0f, 0.0f);
       glm::mat4 view = glm::lookAt(cameraPosition, cameraTarget, upVector);

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f); // Projection matrix
    glm::mat4 mvp = projection * view * model; // MVP matrix

    // Get uniform location and pass MVP matrix
    GLuint mvpLocation = glGetUniformLocation(shaderProgram, "mvp");
    glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, glm::value_ptr(mvp));

    // Draw X axis (red)
    GLuint lineColorLocation = glGetUniformLocation(shaderProgram, "lineColor");
    glUniform3f(lineColorLocation, 1.0f, 0.0f, 0.0f); // Red color
    glBindVertexArray(VAO);
    glDrawArrays(GL_LINES, 0, 2); // Draw X axis

    // Draw Y axis (green)
    glUniform3f(lineColorLocation, 0.0f, 1.0f, 0.0f); // Green color
    glDrawArrays(GL_LINES, 2, 2); // Draw Y axis

    // Draw Z axis (blue)
    glUniform3f(lineColorLocation, 0.0f, 0.0f, 1.0f); // Blue color
    glDrawArrays(GL_LINES, 4, 2); // Draw Z axis
    
    glBindVertexArray(0);
}

int main() {
    glfwInit(); // Initialize GLFW

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); 
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
#endif

    GLFWwindow* window = glfwCreateWindow(800, 600, "MVP Draw Axes", nullptr, nullptr);
    
    if (window == nullptr) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    OriginXYZ *obj = new OriginXYZ();
    // obj->init(); // Initialize OpenGL settings

    while (!glfwWindowShouldClose(window)) {
        obj->display(); // Render the scene

        glfwSwapBuffers(window); // Swap buffers
        glfwPollEvents(); // Check for events
    }

    // glDeleteVertexArrays(1,&VAO); 
    // glDeleteBuffers(1,&VBO); 
    // glDeleteProgram(shaderProgram);
    delete obj;

    glfwTerminate(); // Clean up and exit the program
    return 0;
}