#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <mylib/mylib.h>
#include <mylib/MyPicture.h>

// Settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int MovePicture_1(); // demo move 1 picture
int MovePicture_9(); // demo move 9 pictures

int main(){
    return MovePicture_1();
    // return MovePicture_9();
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
    FPS objFPS;

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
    
        printf("offset = %f, bUP = %d\n", offset, bUP);
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

        // offset = 0;
        processInput(window); // Input processing

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
        
        
        myPicture->display(0.0f, 0.0f, offset, view, projection);
        obj->display(view, projection); // Render the scene

        glfwSwapBuffers(window); // Swap buffers
        glfwPollEvents();        // Check for events

        objFPS.display(); // display fps
    }

    delete obj;
    delete myPicture;
    glfwTerminate(); // Clean up and exit the program
    return 0;
}


int MovePicture_9() {
    // init GLFW
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
    
    // init GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    unsigned int num = 9;
    MyPicture2 **myPictures = new MyPicture2* [num];

    // create VAO, VBO from vertices
    float d = 0.5f;
    float z = -5.0f;
    for (int i = 0; i < num; i++){
        myPictures[i] = new MyPicture2(SCR_WIDTH, SCR_HEIGHT);
        // d = d + 0.1f;
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
         myPictures[i]->initVAOBAO(vertices, sizeof(vertices), attr1_element_num, attr2_element_num);
    }
     // setup view & perspective
    glm::vec3 cameraPosition = glm::vec3(1.0f, 1.0f, 3.0f); // Set the camera position at (1, 1, 3)
    glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 upVector = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::mat4 view = glm::lookAt(cameraPosition, cameraTarget, upVector); //  glm::mat4 view = glm::mat4(1.0f);

    float near = 0.01f;
    float far = 10.0f;
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, near, far);


    OriginXYZ *obj = new OriginXYZ();
    FPS objFPS;

   float offset = 0.0f; // Moving triangle horizontal offset
   bool bUP = false;
   while (!glfwWindowShouldClose(window)) {
       // Input processing
       processInput(window);

       glClear(GL_COLOR_BUFFER_BIT);

       // postion
       if (offset <= 0.0f && bUP == false){
            bUP = true;
       }

        if(offset > 1.0f && bUP == true){
            bUP = false;
        }

        if(bUP){
            offset += 0.01f;
        }else{
            offset -= 0.01f;
        }
 
       for(int i = 0; i < num; i++){
            switch(i){
            case 0:
                myPictures[i]->display(offset , 0.0f , 0.0f, view, projection);
                break;
            case 1:
                myPictures[i]->display(-offset , 0.0f , 0.0f, view, projection);
                break;
            case 2:
                 myPictures[i]->display(0.0f, offset, 0.0f, view, projection);
                break;
            case 3:
                myPictures[i]->display(0.0f, -offset, 0.0f, view, projection);
                break;
            case 4:
                 myPictures[i]->display(offset , offset , 0.0f, view, projection);
                break;
            case 5:
                myPictures[i]->display(-offset , -offset , 0.0f, view, projection);
                break;
            case 6:
                myPictures[i]->display(-offset , offset , 0.0f, view, projection);
                break;
            case 7:
                myPictures[i]->display(offset , -offset , 0.0f, view, projection);
                break;
            case 8:
                myPictures[i]->display(0.9f, 0.9f, offset * 4.0, view, projection);
                break;
            default:
                myPictures[i]->display(0.0f , 0.0f , 0.0f, view, projection);
                break;
            }
       }

       obj->display(view, projection);

       glfwSwapBuffers(window);
       glfwPollEvents();
       objFPS.display(); // display fps
   }

   // free resource
    for(int i=0; i<num; i++){
        delete myPictures[i];
    }
    delete[] myPictures; 

    delete obj;

   glfwTerminate();


   return 0;
}
