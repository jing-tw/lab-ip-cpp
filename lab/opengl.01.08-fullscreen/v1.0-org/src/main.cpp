#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <mylib/mylib.h>
#include <mylib/MyFPS.h>
#include <mylib/MyPicture.h>

// Settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int MovePicture_1(); // demo move 1 picture
void processInput(GLFWwindow *window);


int main(){
    return MovePicture_1();
}


int MovePicture_1()
{
    glfwInit(); // Initialize GLFW

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
#endif

    GLFWwindow *window = glfwCreateWindow(800, 600, "MVP Draw Axes", nullptr, nullptr);

    if (window == nullptr)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    float d = 0.5f;
    float z = -0.0f;
    MyPicture2 *myPicture = new MyPicture2((float) SCR_WIDTH, (float) SCR_HEIGHT);
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
    myPicture->initVAOBAO(vertices, sizeof(vertices), attr1_element_num, attr2_element_num);

    OriginXYZ *obj = new OriginXYZ();
    MyFPS objFPS;

    // set the moving    
    float offsetMIN = -5.0f;
    float offsetMAX = 5.0f;
    float offset = 0.0f; 
    bool bUP = false;

    // setup view & perspective
    glm::vec3 cameraPosition = glm::vec3(3.0f, 3.0f, 3.0f); // glm::vec3(5.0f, 5.0f, 5.0f); // Set the camera position at (1, 1, 3)
    glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 upVector = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::mat4 view = glm::lookAt(cameraPosition, cameraTarget, upVector); //  glm::mat4 view = glm::mat4(1.0f);

    float near = 0.01f;
    float far = 100.0f;

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, near, far);

    while (!glfwWindowShouldClose(window))
    {
        // postion
       if (offset <= offsetMIN && bUP == false){
            bUP = true;
       }

        if(offset > offsetMAX && bUP == true){
            bUP = false;
        }

        if(bUP){
            offset += 0.1f;
        }else{
            offset -= 0.1f;
        }

        processInput(window); // Input processing
        

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
        
        
        myPicture->display(0.0f, 0.0f, offset, view, projection);
        obj->display(view, projection); // Render the scene

        glfwSwapBuffers(window); // Swap buffers
        glfwPollEvents();        // Check for events

        double fps = objFPS.display(false); // display fps
        // printf("fps = %f, offset = %f, bUP = %d\n", fps, offset, bUP); 
    }

    delete obj;
    delete myPicture;
    glfwTerminate(); // Clean up and exit the program
    return 0;
}

// Process input function to 
//  1. Close the window when ESC is pressed
//  2. Full screen when F is pressed
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window , GLFW_KEY_ESCAPE) == GLFW_PRESS)
       glfwSetWindowShouldClose(window , true);

     // Check for F key press
    static bool fKeyPressed = false; // tracking F key status
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
        if (!fKeyPressed) { // run on when F key just be pressed.
            printf("click F\n");
            toggleFullscreen(window);
            fKeyPressed = true; // set the flag to mark the F key was be pressed
        }
    } else {
        fKeyPressed = false; // reset the flag when F key was be released
    }
}

