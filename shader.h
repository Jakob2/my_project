#ifndef SHADER_H
#define SHADER_H

#include "general.h"
#include "world.h"

class Shader
{
public:
    Shader();

    void lightsOn();

private:
    /*const GLfloat light_ambient[4]  = { .1f, .1f, .1f, 1.0f }; // 0
    const GLfloat light_diffuse[4]  = { .9f, .9f, .9f, 1.0f }; // 1
    const GLfloat light_specular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat light_position[4] = { -0.5f, .5, -0.5f, 1.0f };

    const GLfloat mat_ambient[4]    = { 0.2f, 0.2f, 0.2f, 1.0f };
    const GLfloat mat_diffuse[4]    = { 0.8f, 0.8f, 0.8f, 1.0f };
    const GLfloat mat_specular[4]   = { 1.0f, 1.0f, 1.0f, 1.0f };
    const GLfloat high_shininess[4] = { 100.0f };*/

    /*GLfloat light_ambient[4];
    GLfloat light_diffuse[4];
    GLfloat light_specular[4];
    GLfloat light_position[4];

    GLfloat mat_ambient[];
    GLfloat mat_diffuse[];
    GLfloat mat_specular[];
    GLfloat high_shininess[];*/

    /*std::vector<float> light_ambient;
    std::vector<float> light_diffuse;
    std::vector<float> light_specular;
    std::vector<float> light_position;

    std::vector<float> mat_ambient;
    std::vector<float> mat_diffuse;
    std::vector<float> mat_specular;
    std::vector<float> high_shininess;*/


};

#endif // SHADER_H
