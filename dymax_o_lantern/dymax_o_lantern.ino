//
//  dymax_o_lantern.ino
//
//  Created by jamie gilmartin on 2012-01-29.
//  Copyright (c) 2012 jamiegilmartin. All rights reserved.
//

//mucho help from ahmad's thermo lamp code
//https://github.com/asaeed/ThermoLamp/blob/master/Thermolamp/Thermolamp.pde

//TODO:
//PWM brightness on digits 2 - 4, reverse of LED
//abstraction

#include <math.h>

const int thermistor = 0;
const int photoresistor = 1;
const int buttonPin = 13;
const int redPin = 11;    // RED pin of the LED to PWM
const int greenPin = 10;  // GREEN pin of the LED to PWM
const int bluePin = 9;   // BLUE pin of the LED to PWM

//7 segment display
const int digit1 = 2;
const int digit2 = 3;
const int digit3 = 5;
const int digit4 = 6;

//shift register 74HC595
const int latchPin = 8; //Pin connected to latch pin (ST_CP) of 74HC595
const int clockPin = 12; //Pin connected to clock pin (SH_CP) of 74HC595
const int dataPin = 7; //Pin connected to Data in (DS) of 74HC595

int buttonValue = 0;
unsigned long buttonStartTime = 0;
unsigned long buttonTime = 0;
boolean buttonPressed = false;
boolean buttonLongPressed = false;
char scale = 'C';

byte dataArray[13];  //segments in binary
const int MINUS_IDX = 10;
const int CELCIUS_IDX = 11;
const int FARENHEIT_IDX = 12;

const int segmentDelay = 5; //millisecond pulse btwn digit display

unsigned long currentTime = 0;
unsigned long prevTempTime = 0;

int temperature = 0; //initially in celsius

void setup() {
	Serial.begin(9600);
	
	pinMode(redPin, OUTPUT); 
	pinMode(greenPin, OUTPUT); 
	pinMode(bluePin, OUTPUT);
	pinMode(thermistor, INPUT);
	pinMode(photoresistor, INPUT);
	
	pinMode(digit1, OUTPUT);
	pinMode(digit2, OUTPUT);
	pinMode(digit3, OUTPUT);
	pinMode(digit4, OUTPUT);
	
	pinMode(latchPin, OUTPUT);
	pinMode(clockPin, OUTPUT);
	pinMode(dataPin, OUTPUT);
	
	//      A
	//    F   B
	//      G
	//    E   C
	//      D   dp (H)
	//
	//  In binary representation, right most digit is A

	dataArray[0] = B11000000;
	dataArray[1] = B11111001;
	dataArray[2] = B10100100;
	dataArray[3] = B10110000; 
	dataArray[4] = B10011001; 
	dataArray[5] = B10010010; 
	dataArray[6] = B10000010; 
	dataArray[7] = B11111000; 
	dataArray[8] = B10000000; 
	dataArray[9] = B10010000; 

	//temperature specific characters
	dataArray[MINUS_IDX] = B10111111;  // minus sign
	dataArray[CELCIUS_IDX] = B11000110;  // C
	dataArray[FARENHEIT_IDX] = B10001110;  // F
	
	

}


void loop() {
	currentTime = millis();
	buttonValue = digitalRead(buttonPin);
	
	if (buttonValue == 1){
		if (buttonPressed == false) {
			buttonPressed = true;
			buttonStartTime = currentTime; 
		} else {
			buttonTime = currentTime - buttonStartTime; 
			if (buttonTime > 1500) {
				buttonPressed = false;
				buttonLongPressed = true;
				buttonTime = 0;
				//longPressEvent();
				//do something cool here like hello world display
			}
		} 

	} else {
		if (buttonPressed == true){
			buttonPressed = false;
			if (buttonLongPressed) {
				buttonLongPressed = false;
			} else if (buttonTime < 1500) {
				changeScale();
			}
		} 
	}
	
	
	if(currentTime < 5){
		temperature = int(Thermistor(analogRead(thermistor)));
	}
	
	//every 10 seconds, refresh the temp reading
	if (prevTempTime + 10000 < currentTime || prevTempTime == 0){
		//Serial.println(currentTime);
		temperature = int(Thermistor(analogRead(thermistor)));
		
		prevTempTime = currentTime;
	}
	
	displayTemperature(temperature);
	tempLightGuage(temperature);

}

double Thermistor(int RawADC) {
	double Temp;
	Temp = log(((10240000/RawADC) - 10000));
	Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp );
	Temp = Temp - 273.15;            // Convert Kelvin to Celsius
	//Temp = (Temp * 9.0)/ 5.0 + 32.0; // Convert Celcius to Fahrenheit
	return Temp; //return Celsius
}

void changeScale(){
	if (scale == 'C') {
		scale = 'F';
	} else {
		scale = 'C';
	}
}

void displayTemperature(int temp){
	int unit;
	if (scale == 'C') {
		unit = CELCIUS_IDX;
	} else {
		unit = FARENHEIT_IDX;
		temp = (temp * 9.0)/ 5.0 + 32.0; 
	}
	
	//if temp is negative, set negitive sign to correct digit
	if(temp < 0){
		if(temp < -9){
			dd(1);
		}else{
			dd(2);
		}
		sn(MINUS_IDX);
		delay(segmentDelay);
		//set temp to positive int
		temp = abs(temp);
	}
	
	if(temp >= 100){
		//1st digit temp - 100's place
		dd(1);
		sn(temp / 100);
		delay(segmentDelay);
		
		if( (temp % 100) > 9){
			//2nd digit temp - 10's place
			dd(2);
			sn((temp % 100) / 10);
			delay(segmentDelay);
			//3rd digit temp - 1's plance
			dd(3);
			sn((temp % 100) % 10);
			delay(segmentDelay);
		}else{
			//2nd digit temp - 10's place
			dd(2);
			sn(0);
			delay(segmentDelay);
			//3rd digit temp - 1's plance
			dd(3);
			sn((temp % 100));
			delay(segmentDelay);
		}
		
		
	}else if(temp > 9 && temp < 100){
		//2nd digit temp - 10's place
		dd(2);
		sn(temp / 10);
		delay(segmentDelay);
		//3rd digit temp - 1's plance
		dd(3);
		sn(temp % 10);
		delay(segmentDelay);
	}else{
		//3rd digit temp - 1's place
		dd(3);
		sn(temp);
		delay(segmentDelay);
	}
	
	dd(4);
	
	sn(unit);

	delay(segmentDelay);
}

void tempLightGuage(int temp){
	//http://www.digikey.com/us/en/techzone/lighting/resources/articles/mcus-tune-led-color-via-algorithms.html?WT.z_sm_link=google+_tz_0124_lighting
	
	//TODO: better colors & prop temping 16-20

	int photoResistance = analogRead(photoresistor);
	//Serial.println("temp");
	//Serial.println("photoresistance");
	//Serial.println(photoResistance); 


	int brightness = map(photoResistance,0,1023,50,0); //0-255
	//Serial.println("brightness");
	//Serial.println(brightness); 
	int tLow = 15;
	int tHigh = 25;
	int tIdeal = 20;
	int justRightRange = 2;
	int cool = map( temp, (tIdeal-justRightRange), tIdeal, 0, brightness );
	int warm = map( temp, tIdeal, (tIdeal+justRightRange), 0, brightness ); 
	int cold =  map(temp, tHigh, tLow, 0, brightness );
	int hot = map(temp, tLow, tHigh, 0, brightness );

	if(temp == tIdeal){
		analogWrite(greenPin, brightness);
		analogWrite(redPin, 0);
		analogWrite(bluePin, 0);
		//Serial.println("tIdeal");
	}else if(temp < tLow){
		//bottom out - too cold
		analogWrite(greenPin, 0);
		analogWrite(redPin, 0);
		analogWrite(bluePin, brightness);
		//Serial.println("bottom out");
	}else if(temp > tHigh){
		//top out - too high
		analogWrite(greenPin, 0);
		analogWrite(redPin, brightness);
		analogWrite(bluePin, 0);
		//Serial.println("top out");
	}else{

		//ok range
		if(temp > (tIdeal-justRightRange) && temp < tIdeal ){
			analogWrite(greenPin, cool);
			//analogWrite(redPin, 0);
			//analogWrite(bluePin, cold/2);
			//Serial.println("cool");
		}else if(temp < (tIdeal+justRightRange) && temp > tIdeal){
			analogWrite(greenPin, warm);
			//analogWrite(redPin, hot/2);
			//analogWrite(bluePin, 0);
			//Serial.println("warm");
		}else{
			analogWrite(greenPin, 0);
			//hot and cold going
			analogWrite(redPin, hot);
			analogWrite(bluePin, cold);
		}

		
	}

}
