/*
Error code 
*/
#ifndef ERROR_H
#define ERROR_H
#include<GL/glew.h>

GLenum _glCheckError_(const char *file , int line ) ;

#define glCheckError() _glCheckError_(__FILE__ , __LINE__)

#endif