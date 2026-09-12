#include <glad/gl.h>
#include <stdio.h>
#include <stdlib.h>
// shader.c
// OOP style C
typedef struct{
    GLuint program;
    GLuint GetCameraMatrix;
} shader;

shader* myshader() {
    char log[(int)512];
    GLint success;
    shader* S = malloc(sizeof(shader));
    const char* fmShader = 
        "#version 120\n"
        "void main(){\n"
        "   gl_FragColor = vec4(1.0,1.0,1.0,1.0);\n"
        "}";
    const char* vtShader = 
        "#version 120\n"
        "attribute vec2 MainPos;\n"
        "uniform mat3 uTRS;\n"
        "void main(){\n"
        "   vec3 OrthoPos = uTRS*vec3(MainPos,1.0);\n"
        "   gl_Position = vec4(OrthoPos.xy,0.0,1.0);\n"
        "}";
    GLuint fmSource = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fmSource,1,&fmShader,0);
    glCompileShader(fmSource);
    GLuint vtSource = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vtSource,1,&vtShader,0);
    glCompileShader(vtSource);
    S->program = glCreateProgram();
    glGetShaderiv(vtSource,GL_COMPILE_STATUS,&success); //changethis if u want vt debug
    if (!success){
        glGetShaderInfoLog(vtSource,512,NULL,log);
        printf("shader vt/fm error: %s\n",log);
        fflush(stdout);
        exit(0); // crash intentionally
    }
    else{printf("\n");}
    glAttachShader(S->program,fmSource);
    glAttachShader(S->program,vtSource);
    glLinkProgram(S->program);
    S->GetCameraMatrix = glGetUniformLocation(S->program,"uTRS");
    return S;
}

void useprogram(shader* self){
    glUseProgram(self->program);
}

