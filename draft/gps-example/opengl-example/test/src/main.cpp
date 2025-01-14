
#include <iostream>
#include <array>
#include <list>
#include <algorithm>

#include <mylib/mylibopengl.h>
#include <mylib/MyCordXYZ.h>
#include <mylib/MyFPS.h>
#include <mylib/MyPictureCV.h>

#include <wgs_conversions/wgs_conversions.h>

// Settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int MovePicture_1(); // demo move 1 picture
void processInput(GLFWwindow *window);
int test_lla2enu_v2();

int main(){
    test_lla2enu_v2();
    int ret = MovePicture_1();

    return ret;
}

int test_lla2enu_v2()
{
  double lla[3], ref_lla[3], enu[3];
  WgsConversions conv;

  // reference Lat,Long,Alt)
  ref_lla[0] = 35.061676;  // Latitude
  ref_lla[1] = 131.651995; // Longitude
  ref_lla[2] = 0;          // altitude

  std::list<std::array<double, 3>> gpsList;

  gpsList.push_back({35.061739, 131.652172, 0}); // 前進 (64), lat, long
  gpsList.push_back({35.061877, 131.652303, 0}); // 第一個左轉位置 (67)
  gpsList.push_back({35.062719, 131.651996, 0}); // 前進 (77)
  gpsList.push_back({35.063797, 131.651670, 0}); // 開始左轉 (88)
  gpsList.push_back({35.064134, 131.651519, 0}); // 第二個左轉位置 (97)
  gpsList.push_back({35.064021, 131.650956, 0}); // 繼續前進 (157)
  gpsList.push_back({35.062526, 131.645814, 0}); // POI 終點位置 (201)

  std::list<std::array<double, 3>> enuList;

  // Displaying the elements in the list
  for (const auto &arr : gpsList)
  {
    std::cout << "\t\tLat: " << arr[0] << "\tLong: " << arr[1] << "\tAlt: " << arr[2] << std::endl;
    std::copy(arr.begin(), arr.end(), lla); // update the lla point

    conv.lla2enu(enu, lla, ref_lla); // Lat: 32.6031    Long: -85.4983  Alt: 164.241

    std::cout << "\n\tSuccessfully converted from lla to enu" << std::endl;
    std::cout << "\t\tLat: " << lla[0] << "\tLong: " << lla[1] << "\tAlt: " << lla[2] << std::endl;
    std::cout << "\t\tref_Lat: " << ref_lla[0] << "\tref_Long: " << ref_lla[1] << "\tref_Alt: " << ref_lla[2] << std::endl;
    std::cout << "\t\tE: " << enu[0] << "\tN: " << enu[1] << "\tU: " << enu[2] << std::endl;

    enuList.push_back({enu[0], enu[1], enu[2]});
    std::cout << std::endl;
  }

  // print enu list
  for (const auto &enu : enuList)
  {
    std::cout << "\t\tE: " << enu[0] << "\tN: " << enu[1] << "\tU: " << enu[2] << std::endl;
  }

  return 0;
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

    GLFWwindow *window = glfwCreateWindow(800, 600, "MyWindow", nullptr, nullptr);

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

    MyPicture *myPicture = new MyPictureCV();
    // MyPicture *myPicture = new MyPicture();
    if (!myPicture->load("cs-black-000.png"))
        return 0;
    
    
    MyCordXYZ *obj = new MyCordXYZ();
    MyFPS objFPS;

    // set the moving    
    float offsetMIN = -5.0f;
    float offsetMAX = 5.0f;
    float offset = 0.0f; 
    bool bUP = false;

    // setup view & perspective
    glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f); // glm::vec3(3.0f, 3.0f, 3.0f); // glm::vec3(5.0f, 5.0f, 5.0f); // Set the camera position at (1, 1, 3)
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
        // offset = 0.0f; 
        processInput(window); // Input processing
        

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
        
        
        

        double fps = objFPS.display(false); // display fps
        std::stringstream ss;
        ss << "FPS: " << fps;

        // draw text (SLOW)
        Point org(myPicture->width/2, myPicture->height/2);
        Scalar color(255, 255, 0); // Set color (BGR format)
        ((MyPictureCV*) myPicture)->drawText_SLOW(ss.str().c_str(), org, color);

        myPicture->display(0.0f, 0.0f, offset, view, projection);
        obj->display(view, projection); // Render the scene

        glfwSwapBuffers(window); // Swap buffers
        glfwPollEvents();        // Check for events

       // double fps = objFPS.display(false); // display fps
        printf("fps = %f, offset = %f, bUP = %d\n", fps, offset, bUP); 
        myPicture->print();
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

