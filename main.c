#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "shader.c"
#include "ball.c"
#include "matrix2d.c"
/*Project Started: Friday, Sep 11 18:08*/
/*developer:Pel*/
GLFWwindow* window;
GLFWmonitor* monitor;
const GLFWvidmode* video;
bool running = true;
int x=1000;
int y=1000;
float test = 0.0f;
void Camera2DCaller(ball* Player,shader* MainShader,matt3* OrthoCamera){
    test+=1.0f;
    matt3* T = translate(0.0f,0.0f);
    matt3* R = rotate(test);
    matt3* S = scale(1.0f,1.0f);

    matt3* TRS = multiply(T,multiply(R, S));
    glUniformMatrix3fv(MainShader->GetCameraMatrix,1,GL_FALSE,TRS->matfloat);
    free(T);
    free(R);
    free(S);
    free(TRS);
}

void drawobjects(ball* player){
    Draw(player);
}
void InitializeShaderFiles(shader* MainShader){
    useprogram(MainShader);
}
void ReposWindow(){
    monitor = glfwGetPrimaryMonitor();
    video = glfwGetVideoMode(monitor);
    float reposx = (video->width-x)/2.0f;
    float reposy = (video->height-y)/2.0f;
    glfwSetWindowPos(window,reposx,reposy);
    glViewport(0,0,x,y);
}
void OpenGLStuff(){
    glEnable(GL_BLEND);
    glDisable(GL_CULL_FACE);
}
void windowcheck(GLFWwindow* paramwindow){
    if(paramwindow==NULL){
        printf("Window Void\n");
    }
    else{
        printf("Window Initialize\n");
    }
}
void Initializer(){
    glfwInit();
    window = glfwCreateWindow(x,y,"pingpongmyballs",NULL,NULL);
    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);
    /* method/function caller here */
    windowcheck(window);
    ReposWindow();
    OpenGLStuff();
    /* variable stuff */
    shader* MainShader = myshader();
    ball* player = Player();
    matt3* OrthoCamera = identity();
    while(running){
        glClearColor(0.06f,0.06,0.06,1);
        glClear(GL_COLOR_BUFFER_BIT);
        InitializeShaderFiles(MainShader);
        Camera2DCaller(player,MainShader,OrthoCamera);
        drawobjects(player);
        glfwSwapInterval(1);
        glfwPollEvents();
        glfwSwapBuffers(window);
        if (glfwGetKey(window,GLFW_KEY_ESCAPE)==GLFW_PRESS||glfwWindowShouldClose(window)){
            printf("program exit\n");
            running = false;
        }
    }
    free(MainShader);
    glfwTerminate();
}
int main(int argv,char*args[]){
    Initializer();
    return 0;
}
