#include<iostream>
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//#include"utils/utils.h" 
struct Window {
    GLFWwindow *window ; 
    Window (){
        glfwInit() ;
    }
    void makeWindow(){
        if (!glfwInit()){
            std::cout<<"Window Init Error"<<"\n" ;
            glfwTerminate();
        }
        window = glfwCreateWindow(640,480,"PONG",NULL,NULL) ;
        if(window == NULL){
            std::cout<< "Window ERROR "<<"\n" ;
            glfwTerminate(); 
        }
        glfwMakeContextCurrent(window) ;
        glewInit();
        std::cout<< "GL and UI Initalized Succesflly " <<"\n";
    }
}; Window Engine ;

struct Shader {
    GLuint fs ; 
    GLuint vs ; // vertex_shader  
    GLuint shader_program ;
        
    const char *vertex_shader_glsl = R"(
        #version 330 core 
        layout(location = 0) in vec3 Pos ;
        
        uniform mat4 pos  ; // position ;

        void main (){
            gl_Position = pos*vec4(Pos ,1.0) ; 
        }    
    )" ;

    const char *fragment_shade_glsl = R"(
        #version 330 core 
        out vec4 frag_color ;

        void main(){
            frag_color = vec4(.2f,.2f,.7f,1.f) ;
        }
    )" ;

    void vertex_shader(){
        vs = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vs,1,&vertex_shader_glsl,NULL) ;
        glCompileShader(vs);
    }

    void fragment_shader(){
        fs = glCreateShader(GL_FRAGMENT_SHADER) ;
        glShaderSource(fs ,1,&fragment_shade_glsl ,NULL);
        glCompileShader(fs);
    }

    void program(){ // shader_program 
        shader_program = glCreateProgram() ;
        glAttachShader(shader_program , vs) ;
        glAttachShader(shader_program ,fs ) ;
        glLinkProgram(shader_program); 
    }
    void del(){ // function for removin shader program 
        glDeleteShader(vs) ;
        glDeleteShader(fs) ;
        glDeleteProgram(shader_program) ;
    }

} ; Shader shader ;


struct Action {
    glm::mat4 size = glm::scale(glm::mat4(1.f) , glm::vec3(.2f,.2f,.2f)) ;
    
    glm::mat4 padd_1 = glm::mat4(1.f) ; // initalizing pad 1 pos
    glm::mat4 padd_2 = glm::mat4(1.f) ; // initalizing pad 2 pos 
    
    // padd_1 pos // 
    GLfloat posX = -.8f  ;  // would move to array instead of int 
    GLfloat posY = .0f  ; 

    // padd_2 pos //     
    GLfloat PosX = .8f  ; 
    GLfloat PosY = .0f  ; 

    Action(){
        padd_1 = glm::translate(padd_1, glm::vec3(PosX ,PosY,.0f)) ;
        padd_2 = glm::translate(padd_2 , glm::vec3(posX ,posY,.0f)) ;
        
    }
    
    void run_pad1(GLuint shader_program) {
        GLuint pos = glGetUniformLocation(shader_program ,"pos") ;
        glUniformMatrix4fv(pos,1,GL_FALSE ,glm::value_ptr(padd_1)) ;
    }
    void run_pad2(GLuint shader_program) {
        GLuint pos = glGetUniformLocation(shader_program ,"pos") ;
        glUniformMatrix4fv(pos,1,GL_FALSE ,glm::value_ptr(padd_2)) ;
    }
    

}; Action move  ;


int main (){
    Engine.makeWindow() ;
    
    shader.vertex_shader() ;
    shader.fragment_shader() ;

    shader.program() ;
 

    GLfloat square_1 [] = {
        -.1f,.5f,.0f,
        -.1f,-.5f,.0f,
        -.5f,-.5f,.0f ,
        -.5f,.5f,.0f
    } ; 

    GLint square_1_index[] ={
        0 , 1 , 3 ,
        1 , 2 , 3
    } ; 

    // SQR  1// 
    GLuint vbo , vao ,ebo  ;
    glGenBuffers(1, &vbo );
    glGenVertexArrays(1,&vao) ;
    glGenBuffers(1,&ebo);

    glBindVertexArray(vao) ;

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER ,ebo ) ;
    glBufferData(GL_ELEMENT_ARRAY_BUFFER ,sizeof(square_1_index) ,square_1_index ,GL_STATIC_DRAW) ;


    glBindBuffer(GL_ARRAY_BUFFER ,vbo ) ;
    glBufferData(GL_ARRAY_BUFFER ,sizeof(square_1) ,square_1 ,GL_STATIC_DRAW) ;

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER , 0) ;
    glBindVertexArray(0) ;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER ,0) ;

    while (!glfwWindowShouldClose(Engine.window)){
        glClearColor(.2f,.7f,.1f,1.f) ;
        glClear(GL_COLOR_BUFFER_BIT) ;
        glUseProgram(shader.shader_program) ;
        glBindVertexArray(vao) ;

        move.run_pad1(shader.shader_program) ;
        glDrawElements(GL_TRIANGLES , 6 ,GL_UNSIGNED_INT ,0); 

        move.run_pad2(shader.shader_program) ;
        glDrawElements(GL_TRIANGLES , 6 ,GL_UNSIGNED_INT ,0); 
        

        glfwSwapBuffers(Engine.window) ;
        glfwPollEvents() ;
        
    }
    glfwTerminate() ;

} 