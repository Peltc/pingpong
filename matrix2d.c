#include <stdlib.h>
#include <math.h>
// math maker here
// matrix2d.c
typedef struct { 
    float matfloat[9];
    float fuckingslot[16];
} matt3;

matt3* identity(){
    matt3* mat = malloc(sizeof(matt3));
    mat->matfloat[0]=1; mat->matfloat[1]=0; mat->matfloat[2]=0;
    mat->matfloat[3]=0; mat->matfloat[4]=1; mat->matfloat[5]=0;
    mat->matfloat[6]=0; mat->matfloat[7]=0; mat->matfloat[8]=1;
    return mat;
} 
matt3* translate(float tx, float ty){
    matt3* mat = identity();
    mat->matfloat[2] = tx;
    mat->matfloat[5] = ty;
    return mat;
}
matt3* rotate(float angle){
    matt3* mat = identity();
    float rad = angle*M_PI/(float)180.0f;
    mat->matfloat[0] = cos(rad); mat->matfloat[1] = -sin(rad);
    mat->matfloat[3] = sin(rad); mat->matfloat[4] = cos(rad);
    return mat;
}
matt3* scale(float sx, float sy){
    matt3* mat = identity();
    mat->matfloat[0] = sx;
    mat->matfloat[4] = sy;
    return mat;
}
matt3* multiply(matt3* a,matt3* b) {
    matt3* r = identity();
    for(int x=0;x<3;x++){
        for(int y=0;y<3;y++){
            r->matfloat[y*3+x] =
                a->matfloat[y*3+0]*b->matfloat[0*3+x]+
                a->matfloat[y*3+1]*b->matfloat[1*3+x]+
                a->matfloat[y*3+2]*b->matfloat[2*3+x];
            }
        }
    return r;
}

