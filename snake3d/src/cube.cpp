#include "../include/cube.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include <math.h>

glm::vec3 Cube::color = glm::vec3(0.8f, 0.1f, 0.14f);
glm::vec3 Cube::bcolor = glm::vec3(0.1f, 0.1f, 0.14f);

glm::mat4 Cube::projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
glm::mat4 Cube::view = glm::lookAt(
    glm::vec3(0.0f, 0.0f, 1.0f),
    glm::vec3(
        cos(glm::radians(-90.0f)) * cos(glm::radians(0.0f)),
        sin(glm::radians(0.0f)),
        sin(glm::radians(-90.0f)) * cos(glm::radians(0.0f)) + 1.0f
    ),
    glm::vec3(0.0f, 1.0f, 0.0f)
);

float Cube::side_length = 0.02f;

float Cube::get_side_length()
{
    return Cube::side_length;
}

Cube::Cube()
{
    init_buffers();

    position = glm::vec3();
}

void Cube::init_buffers()
{
    
    program = Shader("shaders/cube.vs", "shaders/cube.fs");
    program.use();
    program.setMat4("projection", projection);
    program.setMat4("view", view);
    //program.setVec3("color", color);

    // cube made of triangle faces
    float vertices[] = {
        // back
        -side_length, -side_length, -side_length, bcolor.x, bcolor.y, bcolor.z,
         side_length, -side_length, -side_length, bcolor.x, bcolor.y, bcolor.z,
         side_length,  side_length, -side_length, color.x, color.y, color.z,
         side_length,  side_length, -side_length, color.x, color.y, color.z,
        -side_length,  side_length, -side_length, color.x, color.y, color.z,
        -side_length, -side_length, -side_length, bcolor.x, bcolor.y, bcolor.z,
        // front
        -side_length, -side_length,  side_length, bcolor.x, bcolor.y, bcolor.z,
         side_length, -side_length,  side_length, bcolor.x, bcolor.y, bcolor.z,
         side_length,  side_length,  side_length, color.x, color.y, color.z,
         side_length,  side_length,  side_length, color.x, color.y, color.z,
        -side_length,  side_length,  side_length, color.x, color.y, color.z,
        -side_length, -side_length,  side_length, bcolor.x, bcolor.y, bcolor.z,

        -side_length,  side_length,  side_length, color.x, color.y, color.z,
        -side_length,  side_length, -side_length, color.x, color.y, color.z,
        -side_length, -side_length, -side_length, bcolor.x, bcolor.y, bcolor.z,
        -side_length, -side_length, -side_length, bcolor.x, bcolor.y, bcolor.z,
        -side_length, -side_length,  side_length, bcolor.x, bcolor.y, bcolor.z,
        -side_length,  side_length,  side_length, color.x, color.y, color.z,
        //
         side_length,  side_length,  side_length, color.x, color.y, color.z,
         side_length,  side_length, -side_length, color.x, color.y, color.z,
         side_length, -side_length, -side_length, bcolor.x, bcolor.y, bcolor.z,
         side_length, -side_length, -side_length, bcolor.x, bcolor.y, bcolor.z,
         side_length, -side_length,  side_length, bcolor.x, bcolor.y, bcolor.z,
         side_length,  side_length,  side_length, color.x, color.y, color.z,
         //
         // bottom
         //-a, -a, -a, color.x, color.y, color.z,
         // a, -a, -a, color.x, color.y, color.z,
         // a, -a,  a, color.x, color.y, color.z,
         // a, -a,  a, color.x, color.y, color.z,
         //-a, -a,  a, color.x, color.y, color.z,
         //-a, -a, -a, color.x, color.y, color.z,
         //
         -side_length,  side_length, -side_length, color.x, color.y, color.z,
          side_length,  side_length, -side_length, color.x, color.y, color.z,
          side_length,  side_length,  side_length, color.x, color.y, color.z,
          side_length,  side_length,  side_length, color.x, color.y, color.z,
         -side_length,  side_length,  side_length, color.x, color.y, color.z,
         -side_length,  side_length, -side_length, color.x, color.y, color.z
    };

    // gen
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    // bind
    glBindVertexArray(VAO);
    // vbo
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void Cube::draw(const glm::mat4 &model) const
{
    // apply transfromations
    program.use();
    program.setMat4("model", model);
    // draw
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 30);
}


