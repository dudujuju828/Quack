
#include <iostream>
#include <vector>
#include <cmath>
#include <filesystem>

#include "../include/utilities/shader.h"
#include "../include/utilities/stb_image.h"
#include "../include/utilities/PerlinNoise.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
glm::vec3 cameraPos   = glm::vec3(0.0f, 5.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);

bool firstMouse = true;
float yaw   = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch =  0.0f;
float lastX =  800.0f / 2.0;
float lastY =  600.0 / 2.0;
float fov   =  45.0f;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

std::string texture_name_1 = "src/textures/Ground037_2K-JPG_Color.jpg";
std::string texture_name_2 = "src/textures/Rocks008_1K-JPG_Color.jpg";
std::string texture_name_3 = "src/textures/Ice002_2K-JPG_Color.jpg";


int main() {        

   	const siv::PerlinNoise::seed_type seed = 123456u;
	const siv::PerlinNoise perlin{ seed }; 
    float ruggedness = 0.02f;
    int frequency = 4;
    int grid_width = 256*4;

    
    std::vector<float> v;
    for (int i = 0; i < grid_width; i++) {
        float x = (float)i/10.0f;
        for (int j = 0; j < grid_width; j++) {
            float z = (float)j/10.0f;
            v.push_back(x);
            // use perlin noise for the y-coordinate
			double noise = perlin.octave2D_01((i * ruggedness), (j * ruggedness), frequency);
            std::cout << noise << std::endl;



            v.push_back(2.0f*(float)noise);




            v.push_back(z);
        }
    }


    std::vector<unsigned int> indices;
    for (int i = 0; i < grid_width-1; i++) {

        for (int j = 0; j < grid_width-1; j++) {
        indices.push_back(j+(i*grid_width));    
        indices.push_back(j+(i*grid_width)+1);    
        indices.push_back(j +(i*grid_width)+ grid_width);    


        indices.push_back(j+(i*grid_width)+1);    
        indices.push_back(j+(i*grid_width)+grid_width);    
        indices.push_back(j+(i*grid_width)+grid_width+1);    
        }

    }

    

    glfwInit();
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH,SCR_HEIGHT,"Title",nullptr,nullptr);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);


    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    unsigned int VBO;
    glGenBuffers(1,&VBO);

    unsigned int VAO;
    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,v.size()*sizeof(float),v.data(),GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,2*sizeof(float),(void*)(v.size()*sizeof(float)));
    glEnableVertexAttribArray(1);


    //EDITS
    unsigned int container_texture;
    glGenTextures(1,&container_texture);

    stbi_set_flip_vertically_on_load(true);


    int width,height,nrChannels;
    unsigned char* data = stbi_load(texture_name_1.c_str(),&width,&height,&nrChannels,0);
    if (!data) {
        std::cout << "Error stbi_load" << std::endl;
    }

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,container_texture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
    glGenerateMipmap(GL_TEXTURE_2D);


    unsigned int container_texture_2;
    glGenTextures(1,&container_texture_2);

    stbi_set_flip_vertically_on_load(true);


    unsigned char* data_2 = stbi_load(texture_name_2.c_str(),&width,&height,&nrChannels,0);
    if (!data_2) {
        std::cout << "Error stbi_load" << std::endl;
    }

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D,container_texture_2);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data_2);
    glGenerateMipmap(GL_TEXTURE_2D);


    unsigned int container_texture_3;
    glGenTextures(1,&container_texture_3);

    stbi_set_flip_vertically_on_load(true);


    unsigned char* data_3 = stbi_load(texture_name_3.c_str(),&width,&height,&nrChannels,0);
    if (!data_3) {
        std::cout << "Error stbi_load" << std::endl;
    }

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D,container_texture_3);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data_3);
    glGenerateMipmap(GL_TEXTURE_2D);



    //END EDITS

    unsigned int EBO;
    glGenBuffers(1,&EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,indices.size()*sizeof(unsigned int),indices.data(),GL_STATIC_DRAW);

    
 
    Shader program("src/shaders/vertex_shader.glsl","src/shaders/fragment_shader.glsl");
    program.use();
    // set texture unit locations
    program.setInt("texture1",0);
    program.setInt("texture2",1);
    program.setInt("texture3",2);


    glBindVertexArray(0);

    unsigned int transformLoc = glGetUniformLocation(program.ID,"transform");

       
    glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);
    //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glEnable(GL_DEPTH_TEST);


    while(!glfwWindowShouldClose(window)) {

        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glClearColor(0.0f,0.7f,1.0f,1.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    
        program.use();
        glBindVertexArray(VAO);


        glm::mat4 model = glm::mat4(1.0f);

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        program.setMat4("projection", projection);

        // camera/view transformation
        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        program.setMat4("view", view);

        int modelLoc = glGetUniformLocation(program.ID, "model");
        glUniformMatrix4fv(modelLoc,1,GL_FALSE,glm::value_ptr(model));

        int viewLoc = glGetUniformLocation(program.ID, "view");
        glUniformMatrix4fv(viewLoc,1,GL_FALSE,glm::value_ptr(view));

        int projectionLoc = glGetUniformLocation(program.ID, "projection");
        glUniformMatrix4fv(projectionLoc,1,GL_FALSE,glm::value_ptr(projection));

        program.setFloat("time",(float)glfwGetTime());

        glDrawElements(GL_TRIANGLES,indices.size(),GL_UNSIGNED_INT,(void*)0);




        glBindVertexArray(0);

        processInput(window);
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();

}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float cameraSpeed = static_cast<float>(2.5 * deltaTime);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f; // change this value to your liking
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    fov -= (float)yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f;
}