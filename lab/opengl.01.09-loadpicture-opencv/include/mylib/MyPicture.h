
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// MyPicture: stb_image version 
// Usage:
/*
    MyPicture *myPicture = new MyPicture();
    myPicture->load("cs-black-000.png");
    while(1){
        myPicture->display(0.0f, 0.0f, offset, view, projection);
    }
*/
class MyPicture{
    public:
        int width = 0 , height = 0; // picture 's width, height
        const char* path; // picture path

    protected:
        GLuint texture;

    private:
        unsigned int shaderProgram;
        GLuint VAO, VBO;

    public:
        MyPicture();
        ~MyPicture();
        virtual bool load(const char* path);
        virtual bool display(float x, float y, float z,  glm::mat4 view, glm::mat4 projection);
        virtual void print();

    protected:
        bool initVertics();
        bool initShader();
    
    private:
        bool initVAOBAO(float *vertices, unsigned int size, unsigned int attr1_element_num, unsigned int attr2_element_num);
        GLuint loadTexture(const char* path, int& width, int& height);
};

