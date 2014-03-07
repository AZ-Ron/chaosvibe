  float t = 0.0;
  float y[] = {0.0,0.0};
  float E;
  float f0 = 0.0;  //velocity
  float f1 = 0.0;  //accelleration
  float f[] = {0.0,0.0};
  float k1[] = {0.0,0.0};
  float k2[] = {0.0,0.0};
  float k3[] = {0.0,0.0};
  float k4[] = {0.0,0.0};
  
  int LEDpos = 0;
  int num_LED = 32;
  
  float pi = 3.14159;
  
  float xpos = 0.0;
  float ypos = 0.0;

  float yindex = 0.1;
  float ynext[] = {0.0,0.0};
 
  float gamma = 0.05; 
  float omega0 = 0.9;
  float h = 0.1; //time step in fractions of natural period 
  float vibespeed_y = 0.0;
  float vibespeed_x = 0.0;
  float A = 0.2;
  int ledPin = 3;    // vibe on pin 3


void setup(){
  //Serial.begin(9600);
   size(800 , 800);
   frameRate(60);
   background(255);
}


void draw() {

//  background(255);
  ellipse(400,400,425,425);
  ellipse(100,100,255,255);
  k1[0] = getf0(t,y,gamma,omega0,A);
  k1[1] = getf1(t,y,gamma,omega0,A);

  ynext[0] = y[0] + 0.5*h*k1[0];
  ynext[1] = y[1] + 0.5*h*k1[1];
  
  k2[0] = getf0(t+0.5*h,ynext,gamma,omega0,A);
  k2[1] = getf1(t+0.5*h,ynext,gamma,omega0,A);

  ynext[0] = y[0] + 0.5*h*k2[0];
  ynext[1] = y[1] + 0.5*h*k2[1];
  
  k3[0] = getf0(t+0.5*h,ynext,gamma,omega0,A);
  k3[1] = getf1(t+0.5*h,ynext,gamma,omega0,A);

  ynext[0] = y[0] + h*k3[0];
  ynext[1] = y[1] + h*k3[1];

  k4[0] = getf0(t+h,ynext,gamma,omega0,A);
  k4[1] = getf1(t+h,ynext,gamma,omega0,A);
  
  
  ynext[0] = y[0] + 0.1667*h*(k1[0] + 2*k2[0] + 2*k3[0] + k4[0]);
  ynext[1] = y[1] + 0.1667*h*(k1[1] + 2*k2[1] + 2*k3[1] + k4[1]);  
    
  //stroke(255, 0, 0);//red for RK4
 // line(50*y[0] + 400, 50*y[1] + 400,50*ynext[0] + 400, 50*ynext[1] + 400);    

  xpos = sin(y[0]);
  ypos = cos(y[0]);

 E = 0.5*(y[1]*y[1]) - cos(y[0]) + 1;
 E = abs(25*E);
 ellipse(100,100,E,E);
 
 line(400,400,200*xpos + 400, 200*ypos + 400);
 ellipse(200*xpos + 400, 200*ypos + 400,20,20);    
// ellipse(400,400,380,380);    
  line(25*y[0] + 400, 25*y[1] + 100,25*ynext[0] + 400, 25*ynext[1] + 100);    

  if(ynext[0] >= pi){
     ynext[0] = ynext[0] - 2*pi;
  }
  if(ynext[0] <= -pi){
     ynext[0] = ynext[0] + 2*pi;
  }

  
  LEDpos = int(num_LED*(y[0]+pi)/(2*pi));
  ellipse(750,160,320,320);
  ellipse(750,10*LEDpos,10,10);

  y[0] = ynext[0];
  y[1] = ynext[1];

  t = t + h;

}


float getf0(float t,float y[],float gamma, float omega0, float A){
  float result;
  result = y[1];
  return result;
}
float getf1(float t,float y[],float gamma, float omega0,float A){
  float result;
  result = -sin(y[0]) - gamma*y[1] + A*cos(omega0*t);
  return result;
}

