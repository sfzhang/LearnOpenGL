#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>
#include <unordered_map>

class Shader {

public:

    GLuint getProgram() const
    {
        return m_program;
    }

    GLuint getShader(GLenum type) const
    {
        auto it = m_shader_set.find(type);
        if (it != m_shader_set.end()) {
            return it->second;
        }
        else {
            return 0;
        }
    }

    GLuint createShaderFromFile(GLenum type, const std::string &file);

    GLuint createShaderFromString(GLenum type, const std::string &str_glsl);

    GLuint createShaderFromString(GLenum type, const char *str_glsl);

    bool use();

private:

    std::string loadFile(const std::string &file);

private:

    GLuint m_program;
    std::unordered_map<GLenum, GLuint> m_shader_set;

};


#endif
