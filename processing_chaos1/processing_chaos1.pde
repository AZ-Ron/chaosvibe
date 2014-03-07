  float t = 0.0;
  float y[] = {0.0,0.5};
  float f0 = 0.0;  //velocity
  float f1 = 0.0;  //accelleration
  float yindex = 0.1;
  float ynext[] = {0.0,0.0};
  float gamma = 0.45; 
  float omega0 = 0.73;
  float h = 0.1; //time step in fractions of natural period 
  float vibespeed_y = 0.0;
  float vibespeed_x = 0.0;
  float A = 1.2;
  int ledPin = 3;    // vibe on pin 3


void setup(){
  //Serial.begin(9600);
   size(800 , 800);
   frameRate(40);
   background(255);
}


void draw() {

  f0 = getf0(t,y,gamma,omega0,A);
  f1 = getf1(t,y,gamma,omega0,A);
  vibespeed_x = 120*abs(f0);
  vibespeed_y = 120*abs(f1);
  if(vibespeed_x > 255.0){
    vibespeed_x = 255.0;
  }
  if(vibespeed_y > 255.0){
    vibespeed_y = 255.0;
  }
  
  ynext[0] = y[0] + h*f0;
  ynext[1] = y[1] + h*f1;  

  //ellipse(50*y[0] + 400, 50*y[1] + 400, 1, 1);
  
  line(50*y[0] + 400, 50*y[1] + 400,50*ynext[0] + 400, 50*ynext[1] + 400);
  fill(255-vibespeed_x);
  ellipse(200,100,100,100);
  fill(255-vibespeed_y);
  ellipse(500,100,100,100);

  y[0] = ynext[0];
  y[1] = ynext[1];
  t = t + h;
//  if(t>=25.0){
//   t = 0.0;
//   y[1]=-1.0+yindex;
//   yindex = yindex + 0.2;
 //  y[0]=0.0;
//   } 
    
//  vibespeed_x = 700*pow(y[0],2);
//  vibespeed_y = 700*pow(y[1],2);
//  analogWrite(ledPin,vibespeed);
//      ellipse(vibespeed_x, vibespeed_y, 1, 1);

 // delay(25);

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
