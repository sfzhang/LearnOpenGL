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
glm::vec3 g_light_pos(1.2f, 1.0f, 2.0f);
glm::vec3 cam_pos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cam_front = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cam_up = glm::vec3(0.0f, 1.0f, 0.0f);
float delta_time = 0.25f;
bool first_in = true;
float last_x = 0;
float last_y = 0;
float pitch = 0;
float yaw = 0;
float fov = 45.0f;

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

void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
    if (first_in) {
        cout << "first in: " << xpos << " " << ypos << endl;
        first_in = false;
        last_x = xpos;
        last_y = ypos;
    }

    float xoffset = xpos - last_x;
    float yoffset = last_y - ypos;
    last_x = xpos;
    last_y = ypos;

    float sensitivity = 0.05;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    cout << "xoffset: " << xoffset << endl;
    cout << "yoffset: " << yoffset << endl;

    if (pitch > 89.0f) {
        pitch = 89.0f;
    }
    else if (pitch < -89.0f) {
        pitch = -89.0f;
    }

    cout << "yaw: " << yaw << endl;
    cout << "pitch: " << pitch << endl;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    cam_front = glm::normalize(front);
}

void scroll_callback(GLFWwindow *window, double xoffet, double yoffset)
{
    if (fov >= 1.0f && fov <= 45.0f) {
        fov -= yoffset;
    }

    if (fov < 1.0f) {
        fov = 1.0f;
    }

    if (fov > 45.0f) {
        fov = 45.0f;
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
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glEnable(GL_DEPTH_TEST);

    float vertices[] = {
		// positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
    
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
    
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
    
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    // light VAO
    unsigned int light_vao;
    glGenVertexArrays(1, &light_vao);
    glBindVertexArray(light_vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Texture
    unsigned int tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load("../res/container2.png", &width, &height, &channels, 0);
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
        "layout (location = 1) in vec3 pos_vec;\n"
        "layout (location = 2) in vec2 tex_coords_data;\n"
		"uniform mat4 model;\n"
        "uniform mat4 view;\n"
        "uniform mat4 projection;\n"
        "out vec3 pos_nor_vec;\n"
        "out vec3 frag_pos;\n"
        "out vec2 tex_coords;\n"
        "void main() {\n"
        "    gl_Position = projection * view * model * vec4(pos, 1.0);\n"
        "    pos_nor_vec = pos_vec;\n"
        "    frag_pos = vec3(model * vec4(pos, 1.0));\n"
        "    tex_coords = tex_coords_data;\n"
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
        "struct Material {\n"
        "    sampler2D diffuse;\n"
        "    vec3 specular;\n"
        "    float shininess;\n"
        "};"
        "struct Light {\n"
        "    vec3 pos;\n"
        "    vec3 ambient;\n"
        "    vec3 diffuse;\n"
        "    vec3 specular;\n"
        "};"
        "in vec3 pos_nor_vec;\n"
        "in vec3 frag_pos;\n"
        "in vec2 tex_coords;\n"
        "out vec4 frag_color;\n"
        "uniform vec3 object_color;\n"
        "uniform vec3 view_pos;\n"
        "uniform Material material;\n"
        "uniform Light light;\n"
        "void main() {\n"
        "    // Ambient\n"
        "    vec3 ambient = light.ambient * texture(material.diffuse, tex_coords).rgb;\n"
        ""
        "    // Diffuse\n"
        "    vec3 pos_nv = normalize(pos_nor_vec);\n"
        "    vec3 light_nv = normalize(light.pos - frag_pos);\n"
        "    float diff = max(dot(pos_nv, light_nv), 0.0f);\n"
        "    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, tex_coords).rgb;\n"
        ""
        "    // Specular\n"
        "    vec3 view_nv = normalize(view_pos - frag_pos);\n"
        "    vec3 reflect_nv = normalize(reflect(-light_nv, pos_nv));\n"
        "    float spec = pow(max(dot(view_nv, reflect_nv), 0.0f), material.shininess);\n"
        "    vec3 specular = light.specular * (spec * material.specular);\n"
        ""
        "    vec3 result = ambient + diffuse + specular;\n"
        "    frag_color = vec4(result, 1.0f);\n"
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

    const char *light_fs_glsl[] = {
        "#version 460 core\n"
        "out vec4 frag_color;\n"
        "void main() {\n"
        "    frag_color = vec4(1.0f);\n"
        "}\n"
    };

    unsigned int light_frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(light_frag_shader, 1, light_fs_glsl, nullptr);
    glCompileShader(light_frag_shader);
    glGetShaderiv(light_frag_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(light_frag_shader, sizeof(err_msg), nullptr, err_msg);
        cout << "Compile light fragment shader failed: " << err_msg << endl;
        glfwTerminate();
        return -1;
    }

    // shader programe
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

    unsigned int light_shader_program = glCreateProgram();
    glAttachShader(light_shader_program, vertex_shader);
    glAttachShader(light_shader_program, light_frag_shader);
    glLinkProgram(light_shader_program);
    glGetProgramiv(light_shader_program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(light_shader_program, sizeof(err_msg), nullptr, err_msg);
        cout << "Link program failed: " << err_msg << endl;
        glfwTerminate();
        return -1;
    }

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glUseProgram(shader_program);
    glUniform1i(glGetUniformLocation(shader_program, "material.diffuse"), 0);

    float last_time = 0;
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::vec3 light_color;
        light_color.x = sin(glfwGetTime() * 2.0f);
        light_color.y = sin(glfwGetTime() * 0.7f);
        light_color.z = sin(glfwGetTime() * 1.3f);

        /*
        glm::vec3 diffuse = light_color * glm::vec3(0.5f);
        glm::vec3 ambient = diffuse * glm::vec3(0.2f);
        */
        glm::vec3 diffuse(sin(glfwGetTime()));
        glm::vec3 ambient(cos(glfwGetTime()));

        glUseProgram(shader_program);
        glUniform3f(glGetUniformLocation(shader_program, "object_color"), 1.0f, 0.5f, 0.32f);
        glUniform3f(glGetUniformLocation(shader_program, "view_pos"), cam_pos.x, cam_pos.y, cam_pos.z);
        glUniform3f(glGetUniformLocation(shader_program, "material.specular"), 0.5f, 0.5f, 0.5f);
        glUniform1f(glGetUniformLocation(shader_program, "material.shininess"), 64.0f);
        glUniform3f(glGetUniformLocation(shader_program, "light.pos"), g_light_pos.x, g_light_pos.y, g_light_pos.z);
        glUniform3f(glGetUniformLocation(shader_program, "light.ambient"), ambient.x, ambient.y, ambient.z);
        glUniform3f(glGetUniformLocation(shader_program, "light.diffuse"), diffuse.x, diffuse.y, diffuse.z);
        glUniform3f(glGetUniformLocation(shader_program, "light.specular"), 1.0f, 1.0f, 1.0f);

        float radius = 2.0f;
        glm::mat4 view = glm::mat4(1.0f);
        view = glm::lookAt(cam_pos, cam_pos + cam_front, cam_up);
        glUniformMatrix4fv(glGetUniformLocation(shader_program, "view"), 1, GL_FALSE, glm::value_ptr(view));
     
        glm::mat4 projection = glm::perspective(glm::radians(fov), (float)(width / height), 0.1f, 100.0f);
        glUniformMatrix4fv(glGetUniformLocation(shader_program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

        glm::mat4 model = glm::mat4(1.0f);
        glUniformMatrix4fv(glGetUniformLocation(shader_program, "model"), 1, GL_FALSE, glm::value_ptr(model));


        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, tex);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 36);
   
        glUseProgram(light_shader_program);
        glUniformMatrix4fv(glGetUniformLocation(light_shader_program, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(light_shader_program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

        model = glm::translate(model, g_light_pos);
        model = glm::scale(model, glm::vec3(0.2f));
        glUniformMatrix4fv(glGetUniformLocation(light_shader_program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        
        glBindVertexArray(light_vao);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

