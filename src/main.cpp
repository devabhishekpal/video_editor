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

    for(int y= 25; y< 75; ++y){
        for(int x=25; x<75; ++x){
            data[y*100*3 + x*3] = 0x00; //R component fill with 0 which is none
            data[y*100*3 + x*3 +1] = 0x00;//G component fill with 0 which is none
            data[y*100*3 + x*3 +2] = 0xff;//B component fill with 255 which is full saturation
        }
        //Hence the blocks are filled as RGB(255,0,0)
    }

    //------------------------------------------------
    //|R|G|B| -||- |R|G|B| -||- |R|G|B| ......... 100
    //------------------------------------------------
    //0,0 (3bits) || 0,1 (3bits)|| 0,2 .... 0,100...... ...... 100,0 || 100,1||.....


    glfwMakeContextCurrent(window);

    GLuint tex_handle;
    int texture_w = 100;
    int texture_h = 100;
    glGenTextures(1, &tex_handle);
    glBindTexture(GL_TEXTURE_2D, tex_handle);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture_w, texture_h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    
    while(!glfwWindowShouldClose(window)){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //orthographic
        int window_width, window_height;
        glfwGetFramebufferSize(window, &window_width, &window_height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, window_width, 0, window_height, -1, 1);
        glMatrixMode(GL_MODELVIEW);

        //RENDERING
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, tex_handle);
        //Begin Mapping
        glBegin(GL_QUADS);
        //Mapping texture i.e projecting it
        //gltexCoord2d is the texture in 2d and glVertext2i is world coordinate
        glTexCoord2d(0,0); glVertex2i(0,0); //texture in 2d at 0,0 should go to world coordinate of 0,0
        glTexCoord2d(1,0); glVertex2i(texture_w,0); //texture in 2d at 1,0 should go to world coordinate of 100,0
        glTexCoord2d(1,1); glVertex2i(texture_w,texture_h);
        glTexCoord2d(0,1); glVertex2i(0,texture_h); //same as above
        //NOTE: Here the order of the statements in mapping is important. Each coordinate is mapped one by one so changing order will make a different shape than you want.
        //End Mapping
        glEnd();
        glDisable(GL_TEXTURE_2D); //freeing up

        glfwSwapBuffers(window);
        glfwWaitEvents();
    }

    return 0;
}

//46:22