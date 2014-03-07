  float t = 0.0;
  float y[] = {0.1,0};
  float ynext[] = {0,0};
  float gamma = 0.01; 
  float omega0 = 10.0;
  float a[2];
  float b[2];
  float c[2];
  float d[2];
  float arg_a[2];
  float arg_b[2];
  float arg_c[2];
  float arg_d[2];
  float h = 0.001;
  float vibespeed = 0.0;
  int ledPin = 3;    // vibe on pin 3


void setup(){
  //Serial.begin(9600);
}


void loop() {

  a[0] = getf0(t,y,gamma,omega0);
  a[1] = getf1(t,y,gamma,omega0);
  
  arg_b[0] = y[0] + 0.5*h*a[0];
  arg_b[1] = y[1] + 0.5*h*a[1];
  
  b[0] = getf0(t + 0.5*h,arg_b,gamma,omega0);
  b[1] = getf1(t + 0.5*h,arg_b,gamma,omega0);

  arg_c[0] = y[0] + 0.5*h*b[0];
  arg_c[1] = y[1] + 0.5*h*b[1];
  
  c[0] = getf0(t + 0.5*h,arg_c,gamma,omega0);
  c[1] = getf1(t + 0.5*h,arg_c,gamma,omega0);
  
  arg_d[0] = y[0] + h*c[0];
  arg_d[1] = y[1] + h*c[1];
  
  d[0] = getf0(t + h,arg_d,gamma,omega0);
  d[1] = getf1(t + h,arg_d,gamma,omega0);

  ynext[0] = y[0] + 0.167*(a[0] + 2*b[0] + 2*c[0] + d[0]);
  ynext[1] = y[1] + 0.167*(a[1] + 2*b[1] + 2*c[1] + d[1]);  

  y[0] = ynext[0];
  y[1] = ynext[1];
  t = t + h;
  if(t>=10000){
   t = 0;
  } 
    
  vibespeed = 10*abs(y[0]);
  analogWrite(ledPin,vibespeed);
  delay(100);

  //ynext = getf(t,y,gamma,omega0); // k now contains 6
  //Serial.println(k);
  //delay(500);
}



float getf0(float t,float y[],float gamma, float omega0){
  float result;
  result = y[1];
  return result;
}
int getf1(float t,float y[],float gamma, float omega0){
  float result;
  result = -pow(omega0,2)*y[0] - gamma*y[1];
  //  result = -pow(omega0,2)*sin(y[0]) - gamma*y[1];
  return result;
}
