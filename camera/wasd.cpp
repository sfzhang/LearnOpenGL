#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <cmath>

using namespace std;

const static int width = 800;
const static int height = 600;

glm::vec3 cam_pos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cam_front = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cam_up = glm::vec3(0.0f, 1.0f, 0.0f);
float delta_time = 0.25f;

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    float cam_speed = 0.08f * delta_time;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        cam_pos += cam_speed * cam_front;
    }
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        cam_pos -= cam_speed * cam_front;
    }
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        cam_pos -= glm::normalize(glm::cross(cam_front, cam_up)) * cam_speed;
    }
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        cam_pos += glm::normalize(glm::cross(cam_front, cam_up)) * cam_speed;
    }
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Need VAO in core profile

    // Create window
    GLFWwindow * window = glfwCreateWindow(width, height, "LearnOpenGL", nullptr, nullptr);
    if (!window) {
        cout << "glfwCreateWindow() failed!" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cout << "gladLoadGLLoader() failed" << endl;
        glfwTerminate();
        return -1;
    }

    glViewport(0, 0, width, height);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glEnable(GL_DEPTH_TEST);

    float vertices[] = {
        // pos                texture coordinate
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
    
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3
    };

    glm::vec3 cube_pos[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f), 
        glm::vec3( 2.0f,  5.0f, -15.0f), 
        glm::vec3(-1.5f, -2.2f, -2.5f),  
        glm::vec3(-3.8f, -2.0f, -12.3f),  
        glm::vec3( 2.4f, -0.4f, -3.5f),  
        glm::vec3(-1.7f,  3.0f, -7.5f),  
        glm::vec3( 1.3f, -2.0f, -2.5f),  
        glm::vec3( 1.5f,  2.0f, -2.5f), 
        glm::vec3( 1.5f,  0.2f, -1.5f), 
        glm::vec3(-1.3f,  1.0f, -1.5f)  
    };
    
    // VAO
    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // VBO
    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Texture
    unsigned int tex[2];
    for (int i = 0; i < 2; i++) {
        glGenTextures(1, &tex[i]);
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, tex[i]);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    // texture 0
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex[0]);

    int width, height, channels;
    unsigned char *data = stbi_load("../res/container.jpg", &width, &height, &channels, 0);
    if (!data) {
        cout << "stbi_load() failed" << endl;
        glfwTerminate();
        return -1;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    // texture 1
    glActiveTexture(GL_TEXTURE0 + 1);
    glBindTexture(GL_TEXTURE_2D, tex[1]);

    //stbi_set_flip_vertically_on_load(true);
    data = stbi_load("../res/awesomeface.png", &width, &height, &channels, 0);
    if (!data) {
        cout << "stbi_load() failed" << endl;
        glfwTerminate();
        return -1;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    // Vertex Shader
    const char *vs_glsl[] = {
        "#version 460 core\n"
        "layout (location = 0) in vec3 pos;\n"
        "layout (location = 1) in vec2 tex_coord;\n"
        "out vec2 vertex_tex_coord;\n"
		"uniform mat4 model;\n"
        "uniform mat4 view;\n"
        "uniform mat4 projection;\n"
        "void main() {\n"
        "    gl_Position = projection * view * model * vec4(pos, 1.0);\n"
        "    vertex_tex_coord = tex_coord;\n"
        "}\n"
    };

    unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, vs_glsl, nullptr);
    glCompileShader(vertex_shader);
    int success;
    char err_msg[1024] = {0};
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex_shader, sizeof(err_msg), nullptr, err_msg);
        cout << "Compile vertex shader failed: " << err_msg << endl;
        glfwTerminate();
        return -1;
    }

    // Fragment Shader
    const char *fs_glsl[] = {
        "#version 460 core\n"
        "in vec2 vertex_tex_coord;\n"
        "out vec4 frag_color;\n"
        "uniform sampler2D tex1;\n"
        "uniform sampler2D tex2;\n"
        "void main() {\n"
        "    frag_color = mix(texture(tex1, vertex_tex_coord), texture(tex2, vertex_tex_coord), 0.2);\n"
        "}\n"
    };

    unsigned int frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag_shader, 1, fs_glsl, nullptr);
    glCompileShader(frag_shader);
    glGetShaderiv(frag_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(frag_shader, sizeof(err_msg), nullptr, err_msg);
        cout << "Compile fragment shader failed: " << err_msg << endl;
        glfwTerminate();
        return -1;
    }

    // Use shader
    unsigned int shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, frag_shader);
    glLinkProgram(shader_program);
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader_program, sizeof(err_msg), nullptr, err_msg);
        cout << "Link program failed: " << err_msg << endl;
        glfwTerminate();
        return -1;
    }

    glUseProgram(shader_program);

    glUniform1i(glGetUniformLocation(shader_program, "tex1"), 0);
    glUniform1i(glGetUniformLocation(shader_program, "tex2"), 1);

    glm::mat4 model = glm::mat4(1.0f);
    glUniformMatrix4fv(glGetUniformLocation(shader_program, "model"), 1, GL_FALSE, glm::value_ptr(model));

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)(width / height), 0.1f, 100.0f);
    glUniformMatrix4fv(glGetUniformLocation(shader_program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    float last_time = 0;
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, tex[0]);

        glActiveTexture(GL_TEXTURE0 + 1);
        glBindTexture(GL_TEXTURE_2D, tex[1]);

        float current_time = glfwGetTime();
        if (last_time != 0) {
            delta_time = current_time - last_time;
        }
        last_time = delta_time;

        float radius = 2.0f;
        glm::mat4 view = glm::mat4(1.0f);
        view = glm::lookAt(cam_pos, cam_pos + cam_front, cam_up);
        glUniformMatrix4fv(glGetUniformLocation(shader_program, "view"), 1, GL_FALSE, glm::value_ptr(view));
        
        glBindVertexArray(vao);
        for (int i = 0; i < 10; i++) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cube_pos[i]);
            if (i % 3) {
                model = glm::rotate(model, glm::radians(20.0f * i), glm::vec3(1.0f, 0.3f, 0.5f));
            }
            else {
                model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(1.0f, 0.3f, 0.5f));
            }
            glUniformMatrix4fv(glGetUniformLocation(shader_program, "model"), 1, GL_FALSE, glm::value_ptr(model));
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

