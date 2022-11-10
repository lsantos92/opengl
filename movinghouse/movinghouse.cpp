// Include standard headers
#include <stdio.h>
#include <stdlib.h>

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
GLuint QuadradoID;
GLuint TrianguloID;
GLuint PortaID;
GLuint JanelaID;

// Vertex buffer object (VBO)
GLuint quadradobuffer;
GLuint triangulobuffer;
GLuint portabuffer;
GLuint janelabuffer;

// color buffer object (CBO)
GLuint quadradocolorbuffer;
GLuint triangulocolorbuffer;
GLuint portacolorbuffer;
GLuint janelacolorbuffer;

// GLSL program from the shaders
GLuint programID;


GLint WindowWidth = 800;
GLint WindowHeight = 800;

float delta = 0.0;

//--------------------------------------------------------------------------------
void transferDataToGPUMemory(void)
{
    // VAO
    glGenVertexArrays(1, &QuadradoID);
    glBindVertexArray(QuadradoID);
    glGenVertexArrays(1, &TrianguloID);
    glBindVertexArray(TrianguloID);
    glGenVertexArrays(1, &PortaID);
    glBindVertexArray(PortaID);
    glGenVertexArrays(1, &JanelaID);
    glBindVertexArray(JanelaID);
    
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders( "/Users/luissantos/Documents/UBI/22:23/Computação Gráfica/Prática/opengl_cg/movinghouse/SimpleVertexShader.vertexshader", "/Users/luissantos/Documents/UBI/22:23/Computação Gráfica/Prática/opengl_cg/movinghouse/SimpleFragmentShader.fragmentshader" );
    
    
    static const GLfloat quadrado_buffer_data[] = {
        0.0f,  0.0f,  0.0f,
        20.0f, 0.0f,  0.0f,
        20.0f, 20.0f, 0.0f,
        0.0f,  0.0f,  0.0f,
        20.0f, 20.0f, 0.0f,
        0.0f,  20.0f, 0.0f,
        
    };
    static const GLfloat triangulo_buffer_data[] = {
        0.0f,  20.0f, 0.0f,
        20.0f, 20.0f, 0.0f,
        10.0f, 30.0f, 0.0f,
    };
    
    static const GLfloat janela_buffer_data[] = {
        12.0f, 12.0f,  0.0f,
        18.0f, 12.0f,  0.0f,
        18.0f, 18.0f, 0.0f,
        12.0f, 12.0f,  0.0f,
        18.0f, 18.0f, 0.0f,
        12.0f, 18.0f, 0.0f,
        
    };
    static const GLfloat porta_buffer_data[] = {
        8.0f,  0.0f,  0.0f,
        14.0f, 0.0f,  0.0f,
        14.0f, 10.0f, 0.0f,
        8.0f,  0.0f,  0.0f,
        14.0f, 10.0f, 0.0f,
        8.0f,  10.0f, 0.0f,
    };
    
    // One color for each vertex. They were generated randomly.
    static const GLfloat quadrado_color_buffer_data[] = {
        1.0f,  0.0f,  0.0f,
        1.0f,  0.0f,  0.0f,
        1.0f,  0.0f,  0.0f,
        1.0f,  0.0f,  0.0f,
        1.0f,  0.0f,  0.0f,
        1.0f,  0.0f,  0.0f,
     
    };
    static const GLfloat triangulo_color_buffer_data[] = {
        0.0f,  1.0f,  0.0f,
        0.0f,  1.0f,  0.0f,
        0.0f,  1.0f,  0.0f,
        
    };
   
    
    // One color for each vertex. They were generated randomly.
    static const GLfloat janela_color_buffer_data[] = {
        1.0f,  0.0f,  1.0f,
        1.0f,  0.0f,  1.0f,
        1.0f,  0.0f,  1.0f,
        1.0f,  0.0f,  1.0f,
        1.0f,  0.0f,  1.0f,
        1.0f,  0.0f,  1.0f,
      
    };
    static const GLfloat porta_color_buffer_data[] = {
        1.0f,  1.0f,  0.0f,
        1.0f,  1.0f,  0.0f,
        1.0f,  1.0f,  0.0f,
        1.0f,  1.0f,  0.0f,
        1.0f,  1.0f,  0.0f,
        1.0f,  1.0f,  0.0f,
    };

    //Criaçao do buffer vertex e do buffer color
    // Move vertex data to video memory; specifically to VBO called vertexbuffer
    glGenBuffers(1, &quadradobuffer);
    glBindBuffer(GL_ARRAY_BUFFER, quadradobuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadrado_buffer_data), quadrado_buffer_data, GL_STATIC_DRAW);
    
    // Move color data to video memory; specifically to CBO called colorbuffer
    glGenBuffers(1, &quadradocolorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, quadradocolorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadrado_color_buffer_data), quadrado_color_buffer_data, GL_STATIC_DRAW);
    // Move vertex data to video memory; specifically to VBO called vertexbuffer
    glGenBuffers(1, &triangulobuffer);
    glBindBuffer(GL_ARRAY_BUFFER, triangulobuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangulo_buffer_data), triangulo_buffer_data, GL_STATIC_DRAW);
    
    // Move color data to video memory; specifically to CBO called colorbuffer
    glGenBuffers(1, &triangulocolorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, triangulocolorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangulo_color_buffer_data), triangulo_color_buffer_data, GL_STATIC_DRAW);
    // Move vertex data to video memory; specifically to VBO called vertexbuffer
    glGenBuffers(1, &portabuffer);
    glBindBuffer(GL_ARRAY_BUFFER, portabuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(porta_buffer_data), porta_buffer_data, GL_STATIC_DRAW);
    
    // Move color data to video memory; specifically to CBO called colorbuffer
    glGenBuffers(1, &portacolorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, portacolorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(porta_color_buffer_data), porta_color_buffer_data, GL_STATIC_DRAW);
    // Move vertex data to video memory; specifically to VBO called vertexbuffer
    glGenBuffers(1, &janelabuffer);
    glBindBuffer(GL_ARRAY_BUFFER, janelabuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(janela_buffer_data), janela_buffer_data, GL_STATIC_DRAW);
    
    // Move color data to video memory; specifically to CBO called colorbuffer
    glGenBuffers(1, &janelacolorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, janelacolorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(janela_color_buffer_data), janela_color_buffer_data, GL_STATIC_DRAW);
}

//--------------------------------------------------------------------------------
void cleanupDataFromGPU()
{
    //clean the buffers
    glDeleteBuffers(1, &quadradobuffer);
    glDeleteBuffers(1, &quadradocolorbuffer);
    glDeleteBuffers(1, &triangulobuffer);
    glDeleteBuffers(1, &triangulocolorbuffer);
    glDeleteBuffers(1, &portabuffer);
    glDeleteBuffers(1, &portacolorbuffer);
    glDeleteBuffers(1, &janelabuffer);
    glDeleteBuffers(1, &janelacolorbuffer);
    glDeleteVertexArrays(1, &QuadradoID);
    glDeleteVertexArrays(1, &TrianguloID);
    glDeleteVertexArrays(1, &PortaID);
    glDeleteVertexArrays(1, &JanelaID);
    glDeleteProgram(programID);
}

//--------------------------------------------------------------------------------

//Funçao para desenhar o quadrado
void drawQuadrado (void)
{
    // Clear the screen
    glClear( GL_COLOR_BUFFER_BIT );
    
    // Use our shader
    glUseProgram(programID);
    
    // create transformations
    //glm::mat4 model = glm::mat4(1.0f);
    //glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 mvp = glm::ortho(-40.0f, 40.0f, -40.0f, 40.0f);
    
    // Our ModelViewProjection : multiplication of our 3 matrices
    //glm::mat4 mvp = projection * view * model;
    // Remember, matrix multiplication is the other way around
    
    // retrieve the matrix uniform locations
    unsigned int matrix = glGetUniformLocation(programID, "mvp");
    glUniformMatrix4fv(matrix, 1, GL_FALSE, &mvp[0][0]);
    
    
    glm::mat4 trans;
    trans = glm::translate(glm::mat4(1.0), glm::vec3(delta, delta, 0.0f));
    unsigned int m = glGetUniformLocation(programID, "trans");
    glUniformMatrix4fv(m, 1, GL_FALSE, &trans[0][0]);
    
    
    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, quadradobuffer);
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
    glBindBuffer(GL_ARRAY_BUFFER, quadradocolorbuffer);
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
    glDrawArrays(GL_TRIANGLES, 0, 6); // 3 indices starting at 0 -> 1 triangle
    //glDrawArrays(GL_POINTS, 0, 9); // 3 indices starting at 0 -> 1 triangle
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    // 1rst attribute buffer : vertices
    
}
//funçao para desenhar o triangulo (telhado)
void drawTriangulo(void){
    // Clear the screen
    //glClear( GL_COLOR_BUFFER_BIT );
    
    // Use our shader
    glUseProgram(programID);
    
    // create transformations
    //glm::mat4 model = glm::mat4(1.0f);
    //glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 mvp = glm::ortho(-40.0f, 40.0f, -40.0f, 40.0f);
    
    // Our ModelViewProjection : multiplication of our 3 matrices
    //glm::mat4 mvp = projection * view * model;
    // Remember, matrix multiplication is the other way around
    
    // retrieve the matrix uniform locations
    unsigned int matrix = glGetUniformLocation(programID, "mvp");
    glUniformMatrix4fv(matrix, 1, GL_FALSE, &mvp[0][0]);
    
    
    glm::mat4 trans;
    trans = glm::translate(glm::mat4(1.0), glm::vec3(-delta, -delta, 0.0f));
    unsigned int m = glGetUniformLocation(programID, "trans");
    glUniformMatrix4fv(m, 1, GL_FALSE, &trans[0][0]);
    
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, triangulobuffer);
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
    glBindBuffer(GL_ARRAY_BUFFER, triangulocolorbuffer);
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
    glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle
    
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}
//funçao para desenhar o rectangulo (porta)

void drawPorta(void){
    // Clear the screen
    //glClear( GL_COLOR_BUFFER_BIT );
    
    // Use our shader
    glUseProgram(programID);
    
    // create transformations
    //glm::mat4 model = glm::mat4(1.0f);
    //glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 mvp = glm::ortho(-40.0f, 40.0f, -40.0f, 40.0f);
    
    // Our ModelViewProjection : multiplication of our 3 matrices
    //glm::mat4 mvp = projection * view * model;
    // Remember, matrix multiplication is the other way around
    
    // retrieve the matrix uniform locations
    unsigned int matrix = glGetUniformLocation(programID, "mvp");
    glUniformMatrix4fv(matrix, 1, GL_FALSE, &mvp[0][0]);
    
    
    glm::mat4 trans;
    trans = glm::translate(glm::mat4(1.0), glm::vec3(0.0f, -delta, 0.0f));
    unsigned int m = glGetUniformLocation(programID, "trans");
    glUniformMatrix4fv(m, 1, GL_FALSE, &trans[0][0]);
    
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, portabuffer);
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
    glBindBuffer(GL_ARRAY_BUFFER, portacolorbuffer);
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
    glDrawArrays(GL_TRIANGLES, 0, 6); // 3 indices starting at 0 -> 1 triangle
    
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}
//funçao para desenhar o quadrado (janela)

void drawJanela(void){
    // Clear the screen
    //glClear( GL_COLOR_BUFFER_BIT );
    
    // Use our shader
    glUseProgram(programID);
    
    // create transformations
    //glm::mat4 model = glm::mat4(1.0f);
    //glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 mvp = glm::ortho(-40.0f, 40.0f, -40.0f, 40.0f);
    
    // Our ModelViewProjection : multiplication of our 3 matrices
    //glm::mat4 mvp = projection * view * model;
    // Remember, matrix multiplication is the other way around
    
    // retrieve the matrix uniform locations
    unsigned int matrix = glGetUniformLocation(programID, "mvp");
    glUniformMatrix4fv(matrix, 1, GL_FALSE, &mvp[0][0]);
    
    
    glm::mat4 trans;
    trans = glm::translate(glm::mat4(1.0), glm::vec3(0.0f, -delta, 0.0f));
    unsigned int m = glGetUniformLocation(programID, "trans");
    glUniformMatrix4fv(m, 1, GL_FALSE, &trans[0][0]);
    
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, janelabuffer);
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
    glBindBuffer(GL_ARRAY_BUFFER, janelacolorbuffer);
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
    glDrawArrays(GL_TRIANGLES, 0, 6); // 3 indices starting at 0 -> 1 triangle
    
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
    window = glfwCreateWindow( WindowWidth, WindowHeight, "Moving House in 2D ", NULL, NULL);
    
    // Create window context
    glfwMakeContextCurrent(window);
    
    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    glewInit();
    
    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    
    // White background
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    
    // transfer my data (vertices, colors, and shaders) to GPU side
    transferDataToGPUMemory();
    
    // render scene for each frame
    do{
        // drawing callback
        drawQuadrado();
        drawTriangulo();
        drawPorta();
        drawJanela();
        
        // Swap buffers
        glfwSwapBuffers(window);
        
        // looking for events
        glfwPollEvents();
        
        if (delta < 20 )
            delta += 1;
        
    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
          glfwWindowShouldClose(window) == 0 );
    
    
    // Cleanup VAO, VBOs, and shaders from GPU
    cleanupDataFromGPU();
    
    // Close OpenGL window and terminate GLFW
    glfwTerminate();
    
    return 0;
}

