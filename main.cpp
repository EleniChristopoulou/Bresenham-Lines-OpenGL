#include<GL/glut.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

int counter = 0;
int xs = 0, ys = 0, xe = 50, ye = 0;
float theta = 0;

void firstOctant(int dx, int dy){
    int e = -(dx >> 1);
    
    int x = xs;
    int y = ys;

    while (x <= xe){
        glVertex2i(x,y);
        x++;
        e = e + dy;
        if(e>=0){
            y++;
            e = e - dx;
        }
    }
}

void secondOctant(int dx, int dy){
    int e = -(dy >> 1);
    
    int x = xs;
    int y = ys;

    while (y <= ye){
        glVertex2i(x,y);
        y++;           
        e = e + dx;    
        if(e>=0){
            x++;       
            e = e - dy;
        }
    }
}

void thirdOctant(int dx, int dy){
    int e = -(dy >> 1);
    
    int x = xs;
    int y = ys;

    while (y <= ye){
        glVertex2i(x,y);
        y++;           
        e = e - dx;    
        if(e>=0){
            x--;       
            e = e - dy;
        }
    }
}

void fourthOctant(int dx, int dy){
    int e = -(dy >> 1); 
    
    int x = xs;
    int y = ys;

    while (x >= xe){   
        glVertex2i(x,y);
        x--;           
        e = e - dy;     
        if(e<=0){
            y++;       
            e = e - dx; 
        }
    }
}

void fifthOctant(int dx, int dy){
    int e = -(dx >> 1);
    
    int x = xs;
    int y = ys;

    while (x >= xe){   
        glVertex2i(x,y);
        x--;           
        e = e + dy;
        if(e<=0){
            y--;       
            e = e - dx;
        }
    }
}

void sixthOctant(int dx, int dy){
    int e = (dy >> 1); 
    
    int x = xs;
    int y = ys;

    while (y >= ye){    
        glVertex2i(x,y);
        y--;            
        e = e + dx;     
        if(e<=0){
            x--;        
            e = e - dy; 
        }
    }
}

void seventhOctant(int dx, int dy){
    int e = -(dy >> 1); 
    
    int x = xs;
    int y = ys;

    while (y >= ye){    
        glVertex2i(x,y);
        y--;            
        e = e + dx;     
        if(e>=0){
            x++;        
            e = e + dy; 
        }
    }
}

void eighthOctant(int dx, int dy){
    int e = -(dy >> 1); 
    
    int x = xs;
    int y = ys;

    while (x <= xe){    
        glVertex2i(x,y);
        x++;            
        e = e + dy;       
        if(e<=0){
            y--;        
            e = e + dx; 
        }
    }
}

void bresenhamAlgorithm(){
    // Bresenham Algorithm first Octant
    int dx = xe - xs;
    int dy = ye - ys;

    glVertex2i(xs,ys);

    if(dx == 0){
        if(dy > 0){
            secondOctant(dx,dy);
        }else{
            seventhOctant(dx,dy);
        }
    }else{
        float a = ((float) dy )/ ((float) dx); 

        if( a >= 0 &&  a <= 1){                                       //  0 < a <= 1
            if(dx > 0){        // Bresenham Algorithm 1st Octant
                firstOctant(dx, dy);
            }else{              // Bresenham Algorithm 5th Octant  
                fifthOctant(dx,dy);
            }
        }else{
            if( a > 1){                                             //  a > 1
                if(dx > 0){     // Bresenham Algorithm 2nd Octant
                    secondOctant(dx, dy);
                }else{          // Bresenham Algorithm 6th Octant
                    sixthOctant(dx,dy);
                }
            }else{                                                  //  a < 0
                if( a < -1){                                        //  a < -1
                    if(dx < 0){     // Bresenham Algorithm 3rd Octant
                        thirdOctant(dx, dy);
                    }else{          // Bresenham Algorithm 7th Octant
                        seventhOctant(dx,dy);
                    }
                }else{                                              //  -1 < a < 0
                    if(dx < 0){     // Bresenham Algorithm 4th Octant
                        fourthOctant(dx, dy);
                    }else{          // Bresenham Algorithm 8th Octant
                        eighthOctant(dx,dy);
                    }
                }
            }
        }
    }
}

void display()
{
 glClearColor(1, 1, 1, 1);
 glClear(GL_COLOR_BUFFER_BIT);

 glBegin(GL_POINTS);
 glColor3f(1, 0, 0);

 bresenhamAlgorithm();
 
 glColor3f(0, 0, 1);
 glVertex2i(xs,ys);
 
 glColor3f(0, 1, 0);
 glVertex2i(xe,ye);

    if(counter%2000==0){
        theta = M_PI/16 + theta;
        ye = (int) 50*(sin(theta));
        xe = (int) 50*(cos(theta));
    }

 counter++;
 glutPostRedisplay();
 glEnd();
 glFlush();
}

int main(int argc, char** argv)
{
 glutInit(&argc,argv);
 glutInitWindowPosition(150, 150);
 glutInitWindowSize(640, 480);
 glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
 glutCreateWindow("OpenGL application");
 glMatrixMode(GL_PROJECTION);
 gluOrtho2D(-240, 240, -180, 180);
 glutDisplayFunc(display);
 glutMainLoop();
 return 0;
}