  float t = 0.0;
  float y[] = {1.0,0};
  float ynext[] = {0.0,0.0};
  float gamma = 0.1; 
  float omega0 = 0.9;
  float h = 0.05; //time step in fractions of natural period 
  float vibespeed = 0.0;
  float A = 0.0;
  int ledPin = 3;    // vibe on pin 3


void setup(){
  //Serial.begin(9600);
}


void loop() {


  ynext[0] = y[0] + h*getf0(t,y,gamma,omega0,A);
  ynext[1] = y[1] + h*getf1(t,y,gamma,omega0,A);  

  y[0] = ynext[0];
  y[1] = ynext[1];
  t = t + h;
  if(t>=100){
   t = 0.0;
  } 
    
  vibespeed = 100*pow(y[0],2);
  analogWrite(ledPin,vibespeed);
  delay(50);

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
