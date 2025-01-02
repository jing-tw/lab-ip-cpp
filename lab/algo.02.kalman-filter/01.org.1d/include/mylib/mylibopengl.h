// OpenGL
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// OpenCV
#include <opencv2/opencv.hpp>
using namespace cv;

// OpenGL
void framebuffer_size_callback(GLFWwindow* window,int width,int height);
bool toggleFullscreen(GLFWwindow* window);

// OpenCV + OpenGL
GLuint mat2Texture(Mat &image, bool bflip);