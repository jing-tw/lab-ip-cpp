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
    // return MovePicture_1();
    return MovePicture_9();
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
    float z = -5.0f;
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

    float offsetX = 0.0f; // Moving triangle horizontal offset
    bool bUP = false;
    while (!glfwWindowShouldClose(window))
    {
         // postion
       if (offsetX <= 0.0f && bUP == false){
            bUP = true;
       }

        if(offsetX > 1.0f && bUP == true){
            bUP = false;
        }

        if(bUP){
            offsetX += 0.01f;
        }else{
            offsetX -= 0.01f;
        }

        processInput(window); // Input processing

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
        
        
        myPicture->display(0.0f, 0.0f, offsetX*4);
        obj->display(); // Render the scene

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
        //myPictures[i]->initVAOBAO(vertices, sizeof(vertices));
    }

    OriginXYZ *obj = new OriginXYZ();
    FPS objFPS;

   float offsetX = 0.0f; // Moving triangle horizontal offset
   bool bUP = false;
   while (!glfwWindowShouldClose(window)) {
       // Input processing
       processInput(window);

       glClear(GL_COLOR_BUFFER_BIT);

       // postion
       if (offsetX <= 0.0f && bUP == false){
            bUP = true;
       }

        if(offsetX > 1.0f && bUP == true){
            bUP = false;
        }

        if(bUP){
            offsetX += 0.01f;
        }else{
            offsetX -= 0.01f;
        }
 
       for(int i = 0; i < num; i++){
            switch(i){
            case 0:
                myPictures[i]->display(offsetX , 0.0f , 0.0f);
                break;
            case 1:
                myPictures[i]->display(-offsetX , 0.0f , 0.0f);
                break;
            case 2:
                 myPictures[i]->display(0.0f, offsetX, 0.0f);
                break;
            case 3:
                myPictures[i]->display(0.0f, -offsetX, 0.0f);
                break;
            case 4:
                 myPictures[i]->display(offsetX , offsetX , 0.0f);
                break;
            case 5:
                myPictures[i]->display(-offsetX , -offsetX , 0.0f);
                break;
            case 6:
                myPictures[i]->display(-offsetX , offsetX , 0.0f);
                break;
            case 7:
                myPictures[i]->display(offsetX , -offsetX , 0.0f);
                break;
            case 8:
                myPictures[i]->display(0.9f, 0.9f, offsetX * 4.0);
                break;
            default:
                myPictures[i]->display(0.0f , 0.0f , 0.0f);
                break;
            }
       }

       obj->display();

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
