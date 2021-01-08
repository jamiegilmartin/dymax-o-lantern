#include <Servo.h>
Servo myservo;  
const int pos = 0; 
const int red_light_pin= 11;
const int green_light_pin = 10;
const int blue_light_pin = 9;

const int potPin = 2; // A2
int val = 0;
int rotation_angle = 0;

float red = 0;
float green = 0;
float blue = 0;

float angle = 0;
int sides = 3;
float angles[3];

// red, orange, yellow, green, blue, indigo, violet
String rainbow_names[7] = { "red", "orange", "yellow", "green", "blue", "indigo", "violet" };
int rainbow[7][3] = { {255, 0, 0}, {255, 127, 0}, {255, 255, 0}, {0, 255, 0}, {0, 0, 255}, {138, 43, 226}, {139, 0, 255}}; 
int rainbow_index = 0;
int last_rgb[3] = {0, 0, 0};
int current_rgb[3] = {0, 0, 0};

int update_counter = 0;

float get_radians(int d) {
  float rah_rah_radians = d * ( PI / 180.0 );
  return rah_rah_radians;
}

int get_degrees(float r) {
  int d = r * (180.0 / PI );
  return d;
}

float hype(float x, float y) {
  return sqrt(x * x + y * y);
}

void setup() {
  while(!Serial);
  Serial.begin(9600);
  myservo.attach(6);
  
  pinMode(red_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
  pinMode(blue_light_pin, OUTPUT);

  int index = 0;
  while (angle < 360) {
//    float x = cos(get_radians(angle));
//    float y = sin(get_radians(angle));
    angles[index] = angle;
    Serial.println("index : "+String(index) + " angle "+String(angle));
    index += 1;
    angle += 360 / sides;
  }
  
  setRGB(red,green,blue);
}

void loop() {
  val = analogRead(potPin);
  /**/
  float angle = map( val, 0, 1023, 0, 360);

  int servo_angle = map(angle, 0, 360, 0, 180);
  myservo.write(servo_angle);
     

  rainbow_index = map( val, 0, 1023, 0, 6);;
  if(rainbow_index >= 7) {
    rainbow_index = 0;
  }
  

  current_rgb[0] = rainbow[rainbow_index][0];
  current_rgb[1] = rainbow[rainbow_index][1];
  current_rgb[2] = rainbow[rainbow_index][2];

//  float lerp_rate = 0.8;
//  if (current_rgb[0] > last_rgb[0]) {
//    red += (current_rgb[0] - last_rgb[0]) * lerp_rate;
//  } else {
//    red -= (last_rgb[0] - current_rgb[0]) * lerp_rate;
//  }
//
//  if (current_rgb[1] > last_rgb[1]) {
//    green += (current_rgb[1] - last_rgb[1]) * lerp_rate;
//  } else {
//    green -= (last_rgb[1] - current_rgb[1]) * lerp_rate;
//  }
//
//  if (current_rgb[2] > last_rgb[2]) {
//    blue += (current_rgb[2] - last_rgb[2]) * lerp_rate;
//  } else {
//    blue -= (last_rgb[2] - current_rgb[2]) * lerp_rate;
//  }


  
  red = current_rgb[0];
  green = current_rgb[1];
  blue = current_rgb[2]; 
  setRGB(int(red), int(blue), int(green));

  last_rgb[0] = current_rgb[0];
  last_rgb[1] = current_rgb[1];
  last_rgb[2] = current_rgb[2];
  
   
  // Serial.println("update_counter : "+  String( update_counter % 25) );
  if (update_counter % 25 == 0) {
    Serial.println("index : "+  String(rainbow_index) +" color : "+  rainbow_names[rainbow_index]);
    Serial.println("red : "+  String( red ) + ", green : "+  String( green ) + ", blue : "+  String( blue ) );
    
    // rainbow_index += 1;
  }
  
  update_counter += 1;
  delay(100);
}

void setRGB(int red_light_value, int green_light_value, int blue_light_value) {
  analogWrite(red_light_pin, red_light_value);
  analogWrite(green_light_pin, green_light_value);
  analogWrite(blue_light_pin, blue_light_value);
}
