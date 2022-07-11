#include <iostream>
#include <memory>   

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"

#include "include/floor.hpp"
#include "include/snake.hpp"
#include "include/food.hpp"

#include "camera.hpp"



// setting section
const unsigned SCR_WIDTH = 800;
const unsigned SCR_HEIGHT = 600;

// variables section
float deltaTime = 0.0f;
float lastFrame = 0.0f;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window, std::unique_ptr<Snake> &snake);
GLFWwindow* init_window();

int main()
{
    GLFWwindow* window = init_window();
    if (!window) return EXIT_FAILURE;
    
    Camera camera;
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 model = camera.GetModelMatrix();
    glm::mat4 floor_view = projection * view * model;
    Floor floor(floor_view);

    std::unique_ptr<Food> food(new Food);
    std::unique_ptr<Snake> snake(new Snake);
    
    

    // game loop
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glClearColor(0.7f, 0.68f, 0.7f, 0.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // floor 
        floor.draw();
        // snake
        snake->draw();
        snake->move(deltaTime);
        std::cout << snake->is_alive() << "\n";
        // food
        food->draw();
        // if snake ate food
        if (snake->check_for_head_collision(food->get_position()))
        {
            snake->grow();
            food->spawn();
        }

        processInput(window, snake);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    return 0;
}

void processInput(GLFWwindow* window, std::unique_ptr<Snake>& snake)
{
    // the escape key
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    const float speed = 0.04f;
    
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        snake->change_direction(Direction::LEFT);
    }
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        snake->change_direction(Direction::RIGHT);
    }
    else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        snake->change_direction(Direction::UP);
    }
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        snake->change_direction(Direction::DOWN);
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{

}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    
}

GLFWwindow* init_window()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Snake3D", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return nullptr;
    }

    glEnable(GL_DEPTH_TEST);


    return window;
}