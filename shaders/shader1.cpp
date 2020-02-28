#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Need VAO in core profile

    // Create window
    GLFWwindow * window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
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

    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    float vertices[] = {
         0.0f,  0.5f, 0.0f, // triangle 1
        -0.5f,  0.0f, 0.0f,
         0.5f,  0.0f, 0.0f,
        -0.5f,  0.0f, 0.0f, // triangle 2
         0.5f,  0.0f, 0.0f,
         0.0f, -0.5f, 0.0f
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Vertex Shader
    const char *vs_glsl[] = {
        "#version 460 core\n"
        "layout (location = 0) in vec3 pos;\n"
        "out vec4 vertex_color;\n"
        "void main() {\n"
        "    gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);\n"
        "    vertex_color = pos.yzxx;\n"
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
        "out vec4 frag_color;\n"
        "in vec4 vertex_color;\n"
        "void main() {\n"
        "    frag_color = vertex_color;\n"
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
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

