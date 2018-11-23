#include <stdio.h>
#include <stdlib.h>

#include "window.h"
#include "loader.h"
#include "mat4x4.h"


Window::Window(const std::string& title, int width, int height)
    : window_title(title)
    , window_width(width)
    , window_height(height)
{
    if(!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW.\n");
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 

    window = glfwCreateWindow(window_width, window_height, window_title.c_str(), NULL, NULL);
    
    if(window == NULL){
        fprintf(stderr, "Failed to create a window.\n");

        glfwTerminate();
    } else {
        glfwMakeContextCurrent(window);

        glewExperimental = true;
        if (glewInit() != GLEW_OK) {
            fprintf(stderr, "Failed to initialize GLEW.\n");
        }

        glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    }
}

Window::~Window()
{
    glfwTerminate();
}

void Window::OnStart() {}

void Window::OnUpdate() {}

void Window::OnDestroy() {}

void Window::Run()
{
    OnStart();

    do {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        OnUpdate();

        glfwSwapBuffers(window);
        glfwPollEvents();
    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

    OnDestroy();

    glfwTerminate();
}

int Window::WindowWidth() const
{
    return window_width;
}

int Window::WindowHeight() const
{
    return window_height;
}

const std::string& Window::WindowTitle() const
{
    return window_title;
}