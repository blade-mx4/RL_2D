#ifndef GL_FUNCTION_H
#define GL_FUNCTION_H 

#include<iostream>
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<utility> 

// ============= Some Declerations ============== //
/*
WARNING : 
    CODE MAY LOOK TO CLEAN BUT IT IS NOT AI GEN 
    AND PLUS AS AT WRITING THIS AM @ MTU AND RALLY TIRED 
    JUST HAD TO FORCE MYSELF TO JUST CLEAN THE CODE AND PACK EVRYTHING INTO A SINGLE .h FILE 

*/

struct Window {
    GLFWwindow *window ; 
    Window(){
        glfwInit() ;
    }
    void makeWindow() ;
}; //Window Engine ; 

struct Shaders {
    GLuint fs ;
    GLuint vs  ; 
    GLuint shader ; 
    
    const char*vs_code = R"(
        #version 330 core 
        layout(location = 0 ) in vec3 Pos ; 
        
        uniform mat4 pos ;  
    
        void main (){
            gl_position = pos*vec4(Pos ,1.0) ; 
        }
    )" ;

    const char*fs_code = R"(
        #version  330 core  
        out vec4 fs_color ; 

        void main (){
            fs_color = vec4(.2f,.2f,.7f,1.f) ;
        }    
    )" ;

    void vertex_shader() ; 
    void fragment_shader() ; 
    void shader_program() ; 
    void del_shader() ; 

} ; //Shaders shader ; 

struct Pad_1 {
    glm::mat4 size = glm::scale(glm::mat4(1.f) , glm::vec3(.3f,.3f,.3f)) ;
    glm::mat4 pos_init = glm::mat4(1.f) ;

    GLfloat POSx = .97f ; 
    GLfloat POSy = .0f ;

    Pad_1 (){
        pos_init = glm::translate(glm::mat4(1.f) , glm::vec3(POSx , POSy ,.0f)) ;
    }

    void Pad_1_init(GLuint shader_program) ;
    void Pad_1_control(GLFWwindow *window ) ;

} ;

struct Pad_2 {
    glm::mat4 size = glm::scale(glm::mat4(1.f) , glm::vec3(.3f,.3f,.3f)) ;
    glm::mat4 pos_init = glm::mat4(1.f) ;

    GLfloat POSx = .97f ; 
    GLfloat POSy = .0f ;

    Pad_2(){
        pos_init = glm::translate(glm::mat4(1.f) , glm::vec3(POSx , POSy ,.0f)) ;
    }

    void Pad_2_init(GLuint shader_program) ; // run pad from previous func 
    void Pad_2_control(GLFWwindow *window ) ;

} ;

struct Ball {
    glm::mat4 ball_pos = glm::mat4(1.f) ; 
    glm::mat4 size = glm::scale(glm::mat4(1.f) , glm::vec3(.3f,.3f,.3f))  ;

    GLfloat POSx = .0f ; // starts at the center 
    GLfloat POSy = .0f ; // starts at the center 
    
    GLfloat Speedx = .001f ;
    GLfloat Speedy = .001f ;
    

    Ball(){
        ball_pos = glm::translate(glm::mat4(1.f) , glm::vec3(POSx , POSy ,0.0f)) ; 
    }

    void ball_init(GLuint shader_program) ;
    void move_ball() ;
};

struct Collison{
    float left , right , bottom , top ; 
    



} ;
// =============== Implementation  ============== //  

// =========== Engine ============= // 

inline void Window::makeWindow(){
    if (!glfwInit()){
        std::cout<< "Window Not Init "  << "\n" ; 
        glfwTerminate() ;
    } 
    
    window = glfwCreateWindow(640,480 , "PONG" ,NULL ,NULL) ;
    
    if (window == NULL){
        std::cerr<<"Window OBJ NULL " << "\n" ;
        glfwTerminate() ;
    }
    glfwMakeContextCurrent(window); 
    glewInit() ;
    std::cout<<"Window SuccessFull "<<"\n" ;

}

// =========== Shader ========= // 

inline void Shaders::vertex_shader(){
    vs = glCreateShader(GL_VERTEX_SHADER); 
    glShaderSource(vs,1,&vs_code,NULL);
    glCompileShader(vs) ;
}

inline void Shaders::fragment_shader(){
    fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs , 1, &fs_code ,NULL) ;
    glCompileShader(fs) ;
}

void Shaders::shader_program(){
    shader = glCreateProgram() ;
    glAttachShader(shader,vs) ;
    glAttachShader(shader,fs) ;
    glLinkProgram(shader) ;
}

inline void Shaders::del_shader(){
    glDeleteShader(vs) ;
    glDeleteShader(fs) ;
    glDeleteProgram(shader);
} 

// ========= Pad 1 =========== //  

inline void Pad_1::Pad_1_init(GLuint shader) { 
    GLuint pos = glGetUniformLocation(shader , "pos"); 
    glUniformMatrix4fv(pos,1,GL_FALSE,glm::value_ptr(pos_init));

} 
inline void Pad_1::Pad_1_control(GLFWwindow *window){
    if (glfwGetKey(window ,GLFW_KEY_W)==GLFW_PRESS){
        POSy += .002f ;
    }

    if (glfwGetKey(window ,GLFW_KEY_S)==GLFW_PRESS){
        POSy += -.002f ;
    }
    pos_init = glm::translate(glm::mat4(1.f) , glm::vec3(POSx , POSy ,0.0f)) ;  

    if (POSx > .86 || POSy < -.86){
        POSx = .86 ;
        POSy = -.86 ; 
    }
}

// ===== PAD 2 ======== // 

inline void Pad_2::Pad_2_init(GLuint shader) { 
    GLuint pos = glGetUniformLocation(shader , "pos"); 
    glUniformMatrix4fv(pos,1,GL_FALSE,glm::value_ptr(pos_init));

} 

inline void Pad_2::Pad_2_control(GLFWwindow *window){
    if (glfwGetKey(window ,GLFW_KEY_W)==GLFW_PRESS){
        POSy += .002f ;
    }

    if (glfwGetKey(window ,GLFW_KEY_S)==GLFW_PRESS){
        POSy += -.002f ;
    }
    pos_init = glm::translate(glm::mat4(1.f) , glm::vec3(POSx , POSy ,0.0f)) ;  

    if (POSx > .86 || POSy < -.86){
        POSx = .86 ;
        POSy = -.86 ; 
    }
}

inline void Ball::ball_init(GLuint shader){ 
        GLuint pos = glGetUniformLocation(shader , "pos") ;
        glUniformMatrix4fv(pos , 1,GL_FALSE , glm::value_ptr(ball_pos)) ;

}

inline void Ball::move_ball(){
        POSy += Speedy ;
        POSx += Speedx ; 

        if (POSy >.9f ){
            Speedy = -Speedy ;
        }
        if (POSy < -.9f ){
            Speedy = -Speedy ; 
        }

        if (POSx > 1.f ){
            Speedx = -Speedx ;
        }
        if (POSx < -1.f ){
            Speedx = -Speedx ; 
        }        
        ball_pos = glm::translate(glm::mat4(1.f),glm::vec3(POSx,POSy,0.f))*size ;
       
    }




#endif 