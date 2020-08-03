#include <stdio.h>
#include <GLFW/glfw3.h>


int main(int argc, const char** argv){
    GLFWwindow* window;

    if(!glfwInit()){
        printf("Couldnt init GLFW!! \n");
        return 1;
    }
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if(!window){
        printf("Couldnt create window\n");
        return 1;
    }

    //each image is a 100px * 100px with each pixel having 3bits for R,G,B components
    unsigned char* data = new unsigned char[100*100*3];
    //since each pixel is stored in a 1D matrix so first 100 parts refer to first 100 pixels in first row, then from 201 it is second row and so on..
    for(int y= 0; y< 100; ++y){
        for(int x=0; x<100; ++x){
            data[y*100*3 + x*3] = 0xff; //R component fill with 255 which is full saturation
            data[y*100*3 + x*3 +1] = 0x00;//G component fill with 0 which is none
            data[y*100*3 + x*3 +2] = 0x00;//B component fill with 0 which is none
        }
        //Hence the blocks are filled as RGB(255,0,0)
    }

    //------------------------------------------------
    //|R|G|B| -||- |R|G|B| -||- |R|G|B| ......... 100
    //------------------------------------------------
    //0,0 (3bits) || 0,1 (3bits)|| 0,2 .... 0,100...... ...... 100,0 || 100,1||.....

    glfwMakeContextCurrent(window);
    while(!glfwWindowShouldClose(window)){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDrawPixels(100,100, GL_RGB, GL_UNSIGNED_BYTE, data);
        glfwSwapBuffers(window);
        glfwWaitEvents();
    }

    return 0;
}