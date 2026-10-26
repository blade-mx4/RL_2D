#include<iostream>
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<utility> 
#include<thread>
#include "gl_function.h"

Window Engine ;
Shaders shader ; 
Pad_1 move_paddle_1 ;
Pad_2 move_paddle_2 ; 
Ball ball ;


int main (){
    Engine.makeWindow() ;
    
    shader.vertex_shader() ;
    shader.fragment_shader() ;

    shader.shader_program() ;
 
    shader.del_shader() ;
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

// =========================== ball =================================== // 

    std::vector<float> circle_vertex ; 

    for (int i = 0 ; i < 32 ; i++){
        float angle  = 2.f * 3.142* i / 32 ;
        float x = .2*std::cos(angle) ; // radius is .2
        float y = .2*std::sin(angle) * 1.3333333f ;
        
        circle_vertex.push_back(x) ;
        circle_vertex.push_back(y) ;
    }


    GLuint circle_vbo , circle_vao ; 

    glGenBuffers(1,&circle_vbo) ;
    glGenVertexArrays(1,&circle_vao) ;


    glBindVertexArray(circle_vao) ;

    glBindBuffer(GL_ARRAY_BUFFER , circle_vbo);
    glBufferData(GL_ARRAY_BUFFER,circle_vertex.size()*sizeof(float),circle_vertex.data(),GL_STATIC_DRAW) ;
    
    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE , 2*sizeof(float) ,(void*)0) ;
    glEnableVertexAttribArray(0) ;



    while (!glfwWindowShouldClose(Engine.window)){
        glClearColor(.2f,.7f,.1f,1.f) ;
        glClear(GL_COLOR_BUFFER_BIT) ;
        glUseProgram(shader.shader) ;
        glBindVertexArray(vao) ;

        move_paddle_1.Pad_1_control(Engine.window) ;
        move_paddle_1.Pad_1_init(shader.shader) ;
        glDrawElements(GL_TRIANGLES , 6 ,GL_UNSIGNED_INT ,0); 

        move_paddle_2.Pad_2_control(Engine.window) ;
        move_paddle_2.Pad_2_init(shader.shader) ;
        glDrawElements(GL_TRIANGLES , 6 ,GL_UNSIGNED_INT ,0); 
        
        glBindVertexArray(circle_vao) ;
        ball.move_ball();
        ball.ball_init(shader.shader) ;
        glDrawArrays(GL_TRIANGLE_FAN,0,32) ;
        

        glfwSwapBuffers(Engine.window) ;
        glfwPollEvents() ;
        
    }
    glfwTerminate() ;

} 