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
  
  float theta = 0.0;
  float thetadot = 0.0;
  float force;
  float force0;
  float forcearray[] = {0.0,0.0,0.0,0.0};
  float force_constant = 0.35  ;//scaling factor from input to force
  
  int LEDpos = 0;
  int num_LED = 32;
    
  float pi = 3.14159;
  
  float xpos = 0.0;
  float ypos = 0.0;

  float yindex = 0.1;
  float ynext[] = {0.0,0.0};
 
  float gamma = 0.4; 
  float omega0 = 0.7;
  float h = 0.1; //time step in fractions of natural period 
  float vibespeed_y = 0.0;
  float vibespeed_x = 0.0;
  float A = 0.0;
  int ledPin = 3;    // vibe on pin 3
  
  int index=0;

void setup(){
  
  force0 = analogRead(A0);
  for(index = 0;index<=3;index++){
     forcearray[index] = force0; 
  }
  
}

void loop(){

  force = force_constant*abs(forcearray[0] - (forcearray[1]+forcearray[2]+forcearray[3])/3.0);
  
  
  k1[0] = getf0(t,y,gamma,omega0,A,force);
  k1[1] = getf1(t,y,gamma,omega0,A,force);

  ynext[0] = y[0] + 0.5*h*k1[0];
  ynext[1] = y[1] + 0.5*h*k1[1];
  
  k2[0] = getf0(t+0.5*h,ynext,gamma,omega0,A,force);
  k2[1] = getf1(t+0.5*h,ynext,gamma,omega0,A,force);

  ynext[0] = y[0] + 0.5*h*k2[0];
  ynext[1] = y[1] + 0.5*h*k2[1];
  
  k3[0] = getf0(t+0.5*h,ynext,gamma,omega0,A,force);
  k3[1] = getf1(t+0.5*h,ynext,gamma,omega0,A,force);

  ynext[0] = y[0] + h*k3[0];
  ynext[1] = y[1] + h*k3[1];

  k4[0] = getf0(t+h,ynext,gamma,omega0,A,force);
  k4[1] = getf1(t+h,ynext,gamma,omega0,A,force);
  
  
  ynext[0] = y[0] + 0.1667*h*(k1[0] + 2*k2[0] + 2*k3[0] + k4[0]);
  ynext[1] = y[1] + 0.1667*h*(k1[1] + 2*k2[1] + 2*k3[1] + k4[1]);  

  xpos = sin(y[0]);
  ypos = cos(y[0]);

// E = 0.5*(y[1]*y[1]) - cos(y[0]) + 1;
// E = abs(50*E);
//analogWrite(ledPin,int(E));

theta = 255.0*abs(y[0])/pi;
thetadot = 255.0*abs(y[1])/pi;
analogWrite(3,theta);
analogWrite(5,thetadot);


  if(ynext[0] >= pi){
     ynext[0] = ynext[0] - 2*pi;
  }
  if(ynext[0] <= -pi){
     ynext[0] = ynext[0] + 2*pi;
  }

  
  LEDpos = int(num_LED*(y[0]+pi)/(2*pi));

  y[0] = ynext[0];
  y[1] = ynext[1];

  t = t + h;
 
  
  for(index=3;index > 0;index--){
     forcearray[index] = forcearray[index-1]; 
  }  
  forcearray[0] = analogRead(A0);
          
 delay(50);

}


float getf0(float t,float y[],float gamma, float omega0, float A,float force){
  float result;
  result = y[1];
  return result;
}
float getf1(float t,float y[],float gamma, float omega0,float A, float force){
  float result;
  result = -sin(y[0]) - gamma*y[1] + A*cos(omega0*t) + force;
  return result;
}

