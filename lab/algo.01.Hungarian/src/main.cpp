

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

const int INF = std::numeric_limits<int>::max();

class HungarianAlgorithm {
public:
    HungarianAlgorithm(const std::vector<std::vector<int>>& costMatrix)
        : costMatrix(costMatrix), n(costMatrix.size()), m(costMatrix[0].size()),
          u(n + 1), v(m + 1), p(m + 1), way(m + 1) {}

    int solve(std::vector<int>& assignment) {
        for (int i = 1; i <= n; ++i) {
            p[0] = i;
            int j0 = 0;
            std::vector<int> minv(m + 1, INF);
            std::vector<bool> used(m + 1, false);
            do {
                used[j0] = true;
                int i0 = p[j0], delta = INF, j1;
                for (int j = 1; j <= m; ++j) {
                    if (!used[j]) {
                        int cur = costMatrix[i0 - 1][j - 1] - u[i0] - v[j];
                        if (cur < minv[j]) {
                            minv[j] = cur;
                            way[j] = j0;
                        }
                        if (minv[j] < delta) {
                            delta = minv[j];
                            j1 = j;
                        }
                    }
                }
                for (int j = 0; j <= m; ++j) {
                    if (used[j]) {
                        u[p[j]] += delta;
                        v[j] -= delta;
                    } else {
                        minv[j] -= delta;
                    }
                }
                j0 = j1;
            } while (p[j0] != 0);
            do {
                int j1 = way[j0];
                p[j0] = p[j1];
                j0 = j1;
            } while (j0 != 0);
        }
        assignment.resize(n);
        for (int j = 1; j <= m; ++j) {
            if (p[j] != 0) {
                assignment[p[j] - 1] = j - 1;
            }
        }
        return -v[0];
    }

private:
    const std::vector<std::vector<int>>& costMatrix;
    int n, m;
    std::vector<int> u, v, p, way;
};

int main() {
    std::vector<std::vector<int>> costMatrix = {
        {8, 4, 7},
        {5, 2, 3},
        {9, 4, 8}
    };

    HungarianAlgorithm hungarian(costMatrix);
    std::vector<int> assignment;
    int result = hungarian.solve(assignment);

    std::cout << "Minimum cost: " << result << std::endl;
    std::cout << "Task assignments:" << std::endl;
    for (int i = 0; i < assignment.size(); ++i) {
        std::cout << "Worker " << i + 1 << " assigned to task " << assignment[i] + 1 << std::endl;
    }

    return 0;
}




// #include <iostream>
// #include <mylib/mylibopengl.h>
// #include <mylib/MyCordXYZ.h>
// #include <mylib/MyFPS.h>
// #include <mylib/MyPictureCV.h>

// // Settings
// const unsigned int SCR_WIDTH = 800;
// const unsigned int SCR_HEIGHT = 600;

// int MovePicture_1(); // demo move 1 picture
// void processInput(GLFWwindow *window);

// int main(){
//     int ret = MovePicture_1();
//     return ret;
// }

// int MovePicture_1()
// {
//     glfwInit(); // Initialize GLFW

//     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

// #ifdef __APPLE__
//     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
// #endif

//     GLFWwindow *window = glfwCreateWindow(800, 600, "MyWindow", nullptr, nullptr);

//     if (window == nullptr)
//     {
//         std::cerr << "Failed to create GLFW window" << std::endl;
//         glfwTerminate();
//         return -1;
//     }

//     glfwMakeContextCurrent(window);
//     glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

//     if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//     {
//         std::cerr << "Failed to initialize GLAD" << std::endl;
//         return -1;
//     }

//     MyPicture *myPicture = new MyPictureCV();
//     // MyPicture *myPicture = new MyPicture();
//     if (!myPicture->load("cs-black-000.png"))
//         return 0;
    
    
//     MyCordXYZ *obj = new MyCordXYZ();
//     MyFPS objFPS;

//     // set the moving    
//     float offsetMIN = -5.0f;
//     float offsetMAX = 5.0f;
//     float offset = 0.0f; 
//     bool bUP = false;

//     // setup view & perspective
//     glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f); // glm::vec3(3.0f, 3.0f, 3.0f); // glm::vec3(5.0f, 5.0f, 5.0f); // Set the camera position at (1, 1, 3)
//     glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
//     glm::vec3 upVector = glm::vec3(0.0f, 1.0f, 0.0f);
//     glm::mat4 view = glm::lookAt(cameraPosition, cameraTarget, upVector); //  glm::mat4 view = glm::mat4(1.0f);

//     float near = 0.01f;
//     float far = 100.0f;

//     glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, near, far);

//     while (!glfwWindowShouldClose(window))
//     {
//         // postion
//        if (offset <= offsetMIN && bUP == false){
//             bUP = true;
//        }

//         if(offset > offsetMAX && bUP == true){
//             bUP = false;
//         }

//         if(bUP){
//             offset += 0.1f;
//         }else{
//             offset -= 0.1f;
//         }
//         // offset = 0.0f; 
//         processInput(window); // Input processing
        

//         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
        
        
        

//         double fps = objFPS.display(false); // display fps
//         std::stringstream ss;
//         ss << "FPS: " << fps;

//         // draw text (SLOW)
//         Point org(myPicture->width/2, myPicture->height/2);
//         Scalar color(255, 255, 0); // Set color (BGR format)
//         ((MyPictureCV*) myPicture)->drawText_SLOW(ss.str().c_str(), org, color);

//         myPicture->display(0.0f, 0.0f, offset, view, projection);
//         obj->display(view, projection); // Render the scene

//         glfwSwapBuffers(window); // Swap buffers
//         glfwPollEvents();        // Check for events

//        // double fps = objFPS.display(false); // display fps
//         printf("fps = %f, offset = %f, bUP = %d\n", fps, offset, bUP); 
//         myPicture->print();
//     }

//     delete obj;
//     delete myPicture;
//     glfwTerminate(); // Clean up and exit the program
//     return 0;
// }

// // Process input function to 
// //  1. Close the window when ESC is pressed
// //  2. Full screen when F is pressed
// void processInput(GLFWwindow *window)
// {
//     if (glfwGetKey(window , GLFW_KEY_ESCAPE) == GLFW_PRESS)
//        glfwSetWindowShouldClose(window , true);

//      // Check for F key press
//     static bool fKeyPressed = false; // tracking F key status
//     if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
//         if (!fKeyPressed) { // run on when F key just be pressed.
//             printf("click F\n");
//             toggleFullscreen(window);
//             fKeyPressed = true; // set the flag to mark the F key was be pressed
//         }
//     } else {
//         fKeyPressed = false; // reset the flag when F key was be released
//     }
// }

