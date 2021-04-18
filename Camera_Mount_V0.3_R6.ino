#include <Servo.h>

int comm = 2;
int commstate;
int LED = 5;
bool launch;

//kinematics
float a = 90;
int t; //used to reference the data array
float tzero;
float ontime;
float s; //altitude value
float sfrompad = 1; //distance form pad in metres
float anglerad;
float angledeg;
float angleoffset = 91;

Servo cam;

//delete the following data and insert yours
float data[] = {
0, 
0, 
0, 
0, 
0, 
0, 
0.000068, 
0.000395, 
0.0012651, 
0.0030052, 
0.0059531, 
0.010446, 
0.016817, 
0.025395, 
0.036504, 
0.050476, 
0.067662, 
0.088436, 
0.11317, 
0.14225, 
0.17601, 
0.2148, 
0.25892, 
0.30865, 
0.36418, 
0.42575, 
0.49361, 
0.56794, 
0.64893, 
0.73673, 
0.83147, 
0.93297, 
1.0357, 
1.1991, 
1.4622, 
1.8909, 
2.601, 
3.3544, 
4.0639, 
4.7972, 
5.5907, 
6.3876, 
7.3666, 
8.5419, 
9.7646, 
10.988, 
12.186, 
13.355, 
14.362, 
15.296, 
16.248, 
17.267, 
18.257, 
19.203, 
20.186, 
21.141, 
22.068, 
22.968, 
23.841, 
24.687, 
25.506, 
26.3, 
27.067, 
27.808, 
28.524, 
29.215, 
29.88, 
30.52, 
31.135, 
31.725, 
32.29, 
32.831, 
33.346, 
33.837, 
34.303, 
34.744, 
35.16, 
35.552, 
35.919, 
36.261, 
36.579, 
36.873, 
37.142, 
37.387, 
37.607, 
37.804, 
37.977, 
38.126, 
38.25, 
38.351, 
38.428, 
38.481, 
38.511, 
38.516, 
};

void setup() {
  // put your setup code here, to run once:
  cam.attach(7);
  pinMode(LED, OUTPUT);
  pinMode(comm, INPUT);
  Serial.begin(9600);
  launch = false;
  digitalWrite(LED, HIGH);
  
  angledeg = 0;
  cam.write(angleoffset-angledeg);
  tzero = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  commstate = digitalRead(comm);
  if (commstate == 1 && launch == false){
    delay(333); //delay from igniton to liftoff
    launch = true;
    tzero = millis();
  }
  if (launch == true){
    t = (millis() - tzero)/10;
    
    //cam tilt
    kinematics();
    Serial.println(angledeg);
    cam.write(angleoffset-angledeg);
  }
  if (angledeg > 88){
    launch = false;
    delay(17000);
    cam.write(angleoffset-80);
    delay(300);
    cam.write(angleoffset-70);
    delay(300);
    cam.write(angleoffset-50);
    delay(300);
    cam.write(angleoffset-30);
    delay(300);
    cam.write(angleoffset);
    delay(16000);
  }
}

void kinematics(){
  s = data[t];
  anglerad = atan(s/sfrompad);
  angledeg = anglerad*(180/PI);
}
