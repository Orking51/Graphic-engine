#include "window.h" 
#include <glad/glad.h>                                  
#include <GLFW/glfw3.h>     
#include <stdio.h>

static GLFWwindow* window = NULL;  

bool window_init(int width, int height, const char* title) 
{
    if (!glfwInit())    
        return false;

    //On creer un contexte pour OpenGl 3.3 core profile. 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_DEPTH_BITS, 24);

    window = glfwCreateWindow(width, height, title, NULL, NULL);
    
    if (!window){ 
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window); 

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))  
        return false;

    glViewport(0, 0, width, height); 

    return true;   
}

bool window_should_close(void) 
{
    return glfwWindowShouldClose(window);
}

void window_swap_buffers(void) 
{
    glfwSwapBuffers(window);
}

void window_poll_events(void) 
{
    glfwPollEvents();
}

void window_shutdown(void)
{
    glfwDestroyWindow(window);
    glfwTerminate();
}
