#include "error.h"
#include<iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

GLenum _glCheckError_(const char *file , int line ) {
    GLenum error_code ; 
    while ((error_code = glGetError())!=GL_NO_ERROR ){
        std::string error  ;

        switch(error_code){
            case GL_INVALID_ENUM : error = "INVALID_ENUM " ; break ; 
            case GL_INVALID_VALUE :error = "INVALID_VALUE" ; break ;
            case GL_INVALID_OPERATION : error = "INVALID OPERATION" ; break;
            case GL_INVALID_INDEX: error = "INVALID INDEX" ; break ;
            case GL_INVALID_FRAMEBUFFER_OPERATION : error = "INVALID BUFFER OPS" ;break ; 
        }
        std::cout<<"FILE :"<<file<<"["<<error << " ] " <<"Line :"<<line<<"\n";
    }
    return error_code ;
}
