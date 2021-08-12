#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include "app.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

// settings
const unsigned int SCR_WIDTH = 1600;
const unsigned int SCR_HEIGHT = 900;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Graphing Program", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);


    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //setup 
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    App app(SCR_WIDTH, SCR_HEIGHT);

    glfwSetWindowUserPointer(window, &app); //pointer to app object
    
    // render loop

    while (!glfwWindowShouldClose(window))
    {
        //update
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        app.Update(deltaTime);

        if(app.ShouldClose())
            glfwSetWindowShouldClose(window, true);
        
        // render
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        app.Render();

        //swap
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    if (width != 0 && height != 0)
    {
        App* app = reinterpret_cast<App*>(glfwGetWindowUserPointer(window));
        app->Resize(width, height);
    }
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    App* app = reinterpret_cast<App*>(glfwGetWindowUserPointer(window));
    app->ProcessMouse(xpos, ypos);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    //get app object in order to handle input
    App* app = reinterpret_cast<App*>(glfwGetWindowUserPointer(window));
    if (key == GLFW_KEY_F && action == GLFW_RELEASE)
    {
        if (glfwGetWindowMonitor(window) == nullptr)
        {
            const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
            glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, mode->width, mode->height, mode->refreshRate);
        }
        else
        {
            const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
            glfwSetWindowMonitor(window, NULL, 100, 100, SCR_WIDTH, SCR_HEIGHT, mode->refreshRate);
        }
    }
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
        {
            app->ProcessKeyboard(key, true);
        }
        else if (action == GLFW_RELEASE)
        {
            app->ProcessKeyboard(key, false);
        }
    }
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    App* app = reinterpret_cast<App*>(glfwGetWindowUserPointer(window));
    app->Scroll(yoffset);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    App* app = reinterpret_cast<App*>(glfwGetWindowUserPointer(window));

    if (button >= 0 && button < 8)
    {
        if (action == GLFW_PRESS)
        {
            app->ProcessMouseBtn(button, true);
        }
        else if (action == GLFW_RELEASE)
        {
            app->ProcessMouseBtn(button, false);
        }
    }
}

