#include <glad/gl.h>
#include <stdlib.h>
//ball.c
typedef struct {
    GLuint vbo, vao;
    float r;
} ball;
// tomorrow i need balls not squere
ball* Player(){
    ball* b = malloc(sizeof(ball));
    b->r = 0.1;
    float* vertex = malloc(sizeof(float)*18);
    // x y and z
    vertex[0] = b->r; vertex[1] = b->r; vertex[2] = 0.0;
    vertex[3] = -b->r; vertex[4] = -b->r; vertex[5] = 0.0;
    vertex[6] = -b->r; vertex[7] = b->r; vertex[8] = 0.0;
    vertex[9] = b->r; vertex[10] = b->r; vertex[11] = 0.0;
    vertex[12] = b->r; vertex[13] = -b->r; vertex[14] = 0.0;
    vertex[15] = -b->r; vertex[16] = -b->r; vertex[17] = 0.0;
    glGenVertexArrays(1,&b->vao);
    glBindVertexArray(b->vao);
    glGenBuffers(1,&b->vbo);
    glBindBuffer(GL_ARRAY_BUFFER,b->vbo);
    glBufferData(GL_ARRAY_BUFFER,sizeof(float)*18,vertex,GL_STATIC_DRAW);
    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    free(vertex);
    return b;
}
void Draw(ball* self){
    glBindVertexArray(self->vao);
    glBindBuffer(GL_ARRAY_BUFFER,self->vbo);
    glDrawArrays(GL_TRIANGLES,0,6);
}
