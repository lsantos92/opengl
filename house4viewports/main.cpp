// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

// GLM header file
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

// shaders header file
#include "common/shader.hpp"

// Vertex array object (VAO)
GLuint VertexArrayID;

// Vertex buffer object (VBO)
GLuint vertexbuffer;
GLuint vertex_cos_buffer;

// color buffer object (CBO)
GLuint colorbuffer;
GLuint color_cos_buffer;
// GLSL program from the shaders
GLuint programID;


GLint WindowWidth = 600;
GLint WindowHeight = 600;

//--------------------------------------------------------------------------------
void transferDataToGPUMemory(void)
{
    GLfloat x = -20.0f;
    GLfloat y = -20.0f;// xmin of the domain
    
    // VAO
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders( "/Users/luissantos/Documents/UBI/22:23/Computação Gráfica/Prática/opengl_cg/house4viewports/SimpleVertexShader.vertexshader", "/Users/luissantos/Documents/UBI/22:23/Computação Gráfica/Prática/opengl_cg/house4viewports/SimpleFragmentShader.fragmentshader" );
    
  /*
    static const GLfloat g_vertex_buffer_data[] = {
        0.0f,  0.0f,  0.0f,
        20.0f, 0.0f,  0.0f,
        20.0f, 20.0f, 0.0f,
        0.0f,  0.0f,  0.0f,
        20.0f, 20.0f, 0.0f,
        0.0f,  20.0f, 0.0f,
        0.0f,  20.0f, 0.0f,
        20.0f, 20.0f, 0.0f,
        10.0f, 30.0f, 0.0f,
        
        
    };
    
    // One color for each vertex. They were generated randomly.
    static const GLfloat g_color_buffer_data[] = {
        1.0f,  0.0f,  0.0f,
        1.0f,  0.0f,  0.0f,
        1.0f,  0.0f,  0.0f,
        1.0f,  0.0f,  0.0f,
        1.0f,  0.0f,  0.0f,
        1.0f,  0.0f,  0.0f,
        0.0f,  1.0f,  0.0f,
        0.0f,  1.0f,  0.0f,
        0.0f,  1.0f,  0.0f,
    };
   */
    //EXERCISE 1
    
    GLfloat g_vertex_buffer_data[200*3];
    for (int i = 0; i < 200; i++)// i<80 pois como vai de -10 a 10 e anda 0.25 é fazer 20/0.25=8
    {
        g_vertex_buffer_data[i * 3] = x;

       
        g_vertex_buffer_data[(i * 3) + 1] = sinf(x);
        
        g_vertex_buffer_data[(i * 3) + 2] = 0;
        x = x + 0.2f;

    }
    

    GLfloat g_color_buffer_data[200*3];
    for (int i = 0; i < 200; i++)// i<80 pois como vai de -10 a 10 e anda 0.25 é fazer 20/0.25=8
    {
        
        g_color_buffer_data[i * 3] = 1.0f;
        g_color_buffer_data[(i * 3) + 1] = 0.0f;
        g_color_buffer_data[(i * 3) + 2] = 0.0f;
    }
    //COS X
    GLfloat g_vertex_cos_buffer_data[200*3];
    for (int i = 0; i < 200; i++)// i<80 pois como vai de -10 a 10 e anda 0.25 é fazer 20/0.25=8
    {
        g_vertex_cos_buffer_data[i * 3] = y;

        g_vertex_cos_buffer_data[(i * 3) + 1] = cosf(y);
        
        g_vertex_cos_buffer_data[(i * 3) + 2] = 0;
        y = y + 0.2f;

    }
    

    GLfloat g_color_cos_buffer_data[200*3];
    for (int i = 0; i < 200; i++)// i<80 pois como vai de -10 a 10 e anda 0.25 é fazer 20/0.25=8
    {
        
        g_color_cos_buffer_data[i * 3] = 0.0f;
        g_color_cos_buffer_data[(i * 3) + 1] = 1.0f;
        g_color_cos_buffer_data[(i * 3) + 2] = 0.0f;
    }
    //END EXERCISE 1
    // Move vertex data to video memory; specifically to VBO called vertexbuffer
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
    
    // Move color data to video memory; specifically to CBO called colorbuffer
    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
    
    // Move vertex data to video memory; specifically to VBO called vertexbuffer
    glGenBuffers(1, &vertex_cos_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_cos_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_cos_buffer_data), g_vertex_cos_buffer_data, GL_STATIC_DRAW);
    
    // Move color data to video memory; specifically to CBO called colorbuffer
    glGenBuffers(1, &color_cos_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, color_cos_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_cos_buffer_data), g_color_cos_buffer_data, GL_STATIC_DRAW);
}

//--------------------------------------------------------------------------------
void cleanupDataFromGPU()
{
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteBuffers(1, &colorbuffer);
    glDeleteBuffers(1, &vertex_cos_buffer);
    glDeleteBuffers(1, &color_cos_buffer);
    glDeleteVertexArrays(1, &VertexArrayID);
    glDeleteProgram(programID);
}

//--------------------------------------------------------------------------------
void draw_sin (void)
{
    // Use our shader
    glUseProgram(programID);
    
    // create transformations
    //glm::mat4 model = glm::mat4(1.0f);
    //glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 mvp = glm::ortho(-20.0f, 20.0f, -1.0f, 1.5f); //ALTEREI AQUI
    
    // Our ModelViewProjection : multiplication of our 3 matrices
    //glm::mat4 mvp = projection * view * model;
    // Remember, matrix multiplication is the other way around
    
    // retrieve the matrix uniform locations
    unsigned int matrix = glGetUniformLocation(programID, "mvp");
    glUniformMatrix4fv(matrix, 1, GL_FALSE, &mvp[0][0]);
    
    
    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
                          0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                          3,                  // size
                          GL_FLOAT,           // type
                          GL_FALSE,           // normalized?
                          0,                  // stride
                          (void*)0            // array buffer offset
                          );
    
    // 2nd attribute buffer : colors
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glVertexAttribPointer(
                          1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
                          3,                                // size
                          GL_FLOAT,                         // type
                          GL_FALSE,                         // normalized?
                          0,                                // stride
                          (void*)0                          // array buffer offset
                          );
    
    
    //glEnable(GL_PROGRAM_POINT_SIZE);
    //glPointSize(10);
    // Draw the triangle !
    //glDrawArrays(GL_TRIANGLES, 0, 9); // 3 indices starting at 0 -> 1 triangle
    //glDrawArrays(GL_POINTS, 0, 9); // 3 indices starting at 0 -> 1 triangle
    glDrawArrays(GL_LINE_STRIP, 0, 200);
    
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}
void draw_cos (void)
{
    // Use our shader
    glUseProgram(programID);
    
    // create transformations
    //glm::mat4 model = glm::mat4(1.0f);
    //glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 mvp = glm::ortho(-20.0f, 20.0f, -1.0f, 1.5f); //ALTEREI AQUI
    
    // Our ModelViewProjection : multiplication of our 3 matrices
    //glm::mat4 mvp = projection * view * model;
    // Remember, matrix multiplication is the other way around
    
    // retrieve the matrix uniform locations
    unsigned int matrix = glGetUniformLocation(programID, "mvp");
    glUniformMatrix4fv(matrix, 1, GL_FALSE, &mvp[0][0]);
    
    
    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_cos_buffer);
    glVertexAttribPointer(
                          0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                          3,                  // size
                          GL_FLOAT,           // type
                          GL_FALSE,           // normalized?
                          0,                  // stride
                          (void*)0            // array buffer offset
                          );
    
    // 2nd attribute buffer : colors
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, color_cos_buffer);
    glVertexAttribPointer(
                          1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
                          3,                                // size
                          GL_FLOAT,                         // type
                          GL_FALSE,                         // normalized?
                          0,                                // stride
                          (void*)0                          // array buffer offset
                          );
    
    
    //glEnable(GL_PROGRAM_POINT_SIZE);
    //glPointSize(10);
    // Draw the triangle !
    //glDrawArrays(GL_TRIANGLES, 0, 9); // 3 indices starting at 0 -> 1 triangle
    //glDrawArrays(GL_POINTS, 0, 9); // 3 indices starting at 0 -> 1 triangle
    glDrawArrays(GL_LINE_STRIP, 0, 200);
    
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}
//--------------------------------------------------------------------------------



int main( void )
{
    // Initialise GLFW
    glfwInit();
    
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // Open a window
    window = glfwCreateWindow( 600, 600, "House in 4 Viewports", NULL, NULL);
    
    // Create window context
    glfwMakeContextCurrent(window);
    
    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    glewInit();
    
    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    
    // White background
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    
    // Clear the screen
    glClear( GL_COLOR_BUFFER_BIT );
    
    // transfer my data (vertices, colors, and shaders) to GPU side
    transferDataToGPUMemory();
    
    
    GLuint FramebufferName = 0;
    glGenFramebuffers(1, &FramebufferName);
    //glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
    
    
    // render scene for each frame
    do{
        //left bottom
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, WindowWidth*0.5, WindowHeight*1);
        draw_cos();
        
        //right bottom
        glViewport(WindowWidth*0.5, 0, WindowWidth*1, WindowHeight*1);
        draw_sin();
        /*
        //left top
        glViewport(0, WindowHeight*0.5, WindowWidth*0.5, WindowHeight*0.5);
        draw_sin();
        
        //right top
        glViewport(WindowWidth*0.5, WindowHeight*0.5, WindowWidth*0.5, WindowHeight*0.5);
        draw_cos();
        */
        // Swap buffers
        glfwSwapBuffers(window);
        // looking for events
        glfwPollEvents();
        
    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
          glfwWindowShouldClose(window) == 0 );
    
    // delete framebuffer
    glDeleteFramebuffers(1,&FramebufferName);
    
    // Cleanup VAO, VBOs, and shaders from GPU
    cleanupDataFromGPU();
    
    // Close OpenGL window and terminate GLFW
    glfwTerminate();
    
    return 0;
}

