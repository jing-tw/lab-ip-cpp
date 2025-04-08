// #include <iostream> // for debug msg
#include <mylib/MyCordXYZ.h>


MyCordXYZ::MyCordXYZ(GLfloat *vertices, int length)
{
    if (vertices != NULL){
        init(vertices, length);
    }else{
        init(this->vertices, this->Vertex_Array_Length);
    }
}

MyCordXYZ::~MyCordXYZ()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
}

// Initialize OpenGL settings
void MyCordXYZ::init(GLfloat *vertices, int length)
{
    // Create VAO and VBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, length * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, Vertex_Attribute1_COMPONENT_NUM, GL_FLOAT, GL_FALSE, Vertex_Attribute1_COMPONENT_TOTAL_NUM * sizeof(GLfloat), (GLvoid *)0);
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

void MyCordXYZ::display(glm::mat4 view, glm::mat4 projection)
{
    // Use shader program
    glUseProgram(shaderProgram);

    // Set MVP matrix
    glm::mat4 model = glm::mat4(1.0f); // Model matrix
    // glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f)); // Move view to observe the 3D object
    // glm::vec3 cameraPosition = glm::vec3(1.0f, 1.0f, 3.0f); // Set the camera position at (1, 1, 3)
    // glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    // glm::vec3 upVector = glm::vec3(0.0f, 1.0f, 0.0f);
    // glm::mat4 view = glm::lookAt(cameraPosition, cameraTarget, upVector);

    // glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f); // Projection matrix
    glm::mat4 mvp = projection * view * model;                                                           // MVP matrix

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
    glDrawArrays(GL_LINES, 2, 2);                     // Draw Y axis

    // Draw Z axis (blue)
    glUniform3f(lineColorLocation, 0.0f, 0.0f, 1.0f); // Blue color
    glDrawArrays(GL_LINES, 4, 2);                     // Draw Z axis

    glBindVertexArray(0);
}
