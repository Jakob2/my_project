#include "shader.h"

Shader::Shader(){
    /*light_ambient = { .1f, .1f, .1f, 1.0f }; // 0
    light_diffuse = { .9f, .9f, .9f, 1.0f }; // 1
    light_specular = { 1.0f, 1.0f, 1.0f, 1.0f };
    light_position = { -0.5f, World::candleHeight, -0.5f, 1.0f };

    mat_ambient = { 0.2f, 0.2f, 0.2f, 1.0f };
    mat_diffuse = { 0.8f, 0.8f, 0.8f, 1.0f };
    mat_specular = { 1.0f, 1.0f, 1.0f, 1.0f };
    high_shininess = { 100.0f };*/
}

void Shader::lightsOn(){
    const GLfloat light_ambient[]  = { .1f, .1f, .1f, 1.0f }; // 0
    const GLfloat light_diffuse[]  = { .9f, .9f, .9f, 1.0f }; // 1
    const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat light_position[] = { -0.5f, World::candleHeight, -0.5f, 1.0f };

    const GLfloat mat_ambient[]    = { 0.2f, 0.2f, 0.2f, 1.0f };
    const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
    const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
    const GLfloat high_shininess[] = { 100.0f };

    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    //glMatrixMode(GL_MODELVIEW);
    //glPushMatrix(); // push under the stack the current modeview matrix
    //glLoadIdentity(); // reset all transformations


    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    //glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    //glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_direction);

    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    /*glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    //glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);*/

}
