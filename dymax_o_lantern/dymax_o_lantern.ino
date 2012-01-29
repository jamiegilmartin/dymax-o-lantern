//http://arduino.cc/playground/ComponentLib/Thermistor2
//https://github.com/asaeed/ThermoLamp/blob/master/Thermolamp/Thermolamp.pde
//http://www.instructables.com/id/4-Digit-7-Segment-LED-Display-Arduino/
//http://allaboutee.com/2011/07/09/arduino-4-digit-7-segment-display-tutorial/

/*
pin arrangement mod from:
//http://allaboutee.com/2011/07/09/arduino-4-digit-7-segment-display-tutorial

pic of display's pins
//http://www.pavius.net/2010/02/rotary-encoder-based-cooking-timer/

1: Digit 1						*d9 1k
2: Digit 2						*d10 1k
3: D							*d5
4: Colon Anode					--- (5v 1k - took out, don't need)
5: E 							*d6
6: Digit 3						d11 1k
7: Decimal Point				---
8: Digit 4						d12 1k

16: B							*d3
15: G							d8
14: A							d2
13: C							d4
12: Colon Cathode				--- (ground - took out, don't need)
11: F							d7
10: Apostrophe Anode			--- (add 5v 1k)
9:  Apostrophe Cathode			--- (ground)

*pwm

//now with shift register

1: Digit 1						*d9 1k
2: Digit 2						*d10 1k
3: D							sr
4: Colon Anode					---
5: E 							sr
6: Digit 3						d11 1k
7: Decimal Point				---
8: Digit 4						d12 1k

16: B							sr
15: G							sr
14: A							sr
13: C							sr
12: Colon Cathode				--- 
11: F							sr
10: Apostrophe Anode			--- (add 5v 1k)
9:  Apostrophe Cathode			--- (ground)

8 Bit Shift Register

 1: display's B    16: 5V    
 2: display's C    15: display's A
 3: display's D    14: arduino's dataPin
 4: display's E    13: Gnd
 5: display's F    12: arduino's latchPin
 6: display's G    11: arduino's clockPin
 7: display's DP   10: 5V
 8: Gnd            9:  none


//Thermistor

============================================================
 (Ground) ---- (10k-Resister) -------|------- (Thermistor) ---- (+5v)
                                     |
                                Analog Pin 0


//photoresistor
----------------------------------------------------

           PhotoR     10K
 +5    o---/\/\/--.--/\/\/---o GND
                  |
 Pin 0 o-----------

----------------------------------------------------


//LED


1 2 3 4
| | | |
| | | |
| | | 
  | |
  |

1 = red
2 = ground
3 = green
4 = blue

*/



#include <math.h>


int thermistor = 0;
int photoresistor = 1;
int redPin = 11;    // RED pin of the LED to PWM
int greenPin = 10;  // GREEN pin of the LED to PWM
int bluePin = 9;   // BLUE pin of the LED to PWM

//7 segment display
int digit1 = 2, digit2 = 3, digit3 = 5, digit4 = 6;

/*
int A = 2;
int B = 3;
int C = 4;
int D = 5;
int E = 6;
int F = 7;
int G = 8;
*/

byte dataArray[13];
const int MINUS_IDX = 10;
const int CELCIUS_IDX = 11;
const int FARENHEIT_IDX = 12;

int segmentDelay = 5;

//shift register 74HC595 - http://www.sparkfun.com/products/733
//shift out
/*
DS (pin 14) to Ardunio DigitalPin 11 (blue wire)
SH_CP (pin 11) to to Ardunio DigitalPin 12 (yellow wire)
ST_CP (pin 12) to Ardunio DigitalPin 8 (green wire)
*/
//Pin connected to latch pin (ST_CP) of 74HC595
const int latchPin = 8;
//Pin connected to clock pin (SH_CP) of 74HC595
const int clockPin = 12;
////Pin connected to Data in (DS) of 74HC595
const int dataPin = 7;


int i = 0;
unsigned long currentTime = 0;



void setup() {
	Serial.begin(9600);
	
	pinMode(redPin, OUTPUT); 
	pinMode(greenPin, OUTPUT); 
	pinMode(bluePin, OUTPUT);
	pinMode(photoresistor, INPUT);
	//pinMode(motor, OUTPUT); 
	
	pinMode(digit1, OUTPUT);
	pinMode(digit2, OUTPUT);
	pinMode(digit3, OUTPUT);
	pinMode(digit4, OUTPUT);
	/*
	pinMode(A,OUTPUT);
	pinMode(B,OUTPUT);
	pinMode(C,OUTPUT);
	pinMode(D,OUTPUT);
	pinMode(E,OUTPUT);
	pinMode(F,OUTPUT);
	pinMode(G,OUTPUT);
	*/
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
	
	
	pinMode(latchPin, OUTPUT);
	pinMode(clockPin, OUTPUT);
	pinMode(dataPin, OUTPUT);
}

void loop() {
	currentTime = millis() / 1000;
	
	int temp = int(Thermistor(analogRead(thermistor)));
	tempLightGuage();

	//Serial.println("temperature:");
	//Serial.print(temp);  // display Celsius
	//Serial.print(" C | ");
	//Serial.println(currentTime);

	/* temp 
	if(currentTime % 2){
		displayTemperature(temp, CELCIUS_IDX);
	}else{
		displayTemperature((temp * 9.0)/ 5.0 + 32.0, FARENHEIT_IDX);
	}*/
	displayTemperature((temp * 9.0)/ 5.0 + 32.0, FARENHEIT_IDX);
}

//http://arduino.cc/playground/ComponentLib/Thermistor2
double Thermistor(int RawADC) {
	double Temp;
	Temp = log(((10240000/RawADC) - 10000));
	Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp );
	Temp = Temp - 273.15;            // Convert Kelvin to Celsius
	//Temp = (Temp * 9.0)/ 5.0 + 32.0; // Convert Celcius to Fahrenheit
	return Temp;
}

void displayTemperature(int temp, char unit){
	//if temp is negative, set negitive sign to correct digit
	if(temp < 0){
		if(temp < -9){
			dd(1);
		}else{
			dd(2);
		}
		//sl('-');
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
	//sl(unit);
	sn(unit);
	delay(segmentDelay);
}

void tempLightGuage(){
	//gauged arbitrarily in fahrenheit
	int tempF = (int(Thermistor(analogRead(thermistor))) * 9.0)/ 5.0 + 32.0;
	int photoResistance = analogRead(photoresistor);
	//Serial.println("temp");
	//Serial.println(tempF);  // display Fahrenheit
	//Serial.println("photoresistance");
	//Serial.println(photoResistance); 


	int brightness = map(photoResistance,0,1023,50,0); //0-255
	//Serial.println("brightness");
	//Serial.println(brightness); 
	int tLow = 60;
	int tHigh = 90;
	int tIdeal = 72;
	int justRightRange = 5;
	int cool = map( tempF, (tIdeal-justRightRange), tIdeal, 0, brightness );
	int warm = map( tempF, tIdeal, (tIdeal+justRightRange), 0, brightness ); 
	int tooCold =  map(tempF, tHigh, tLow, 0, brightness );
	int tooHot = map(tempF, tLow, tHigh, 0, brightness );

	if(tempF == tIdeal){
		analogWrite(greenPin, brightness);
		analogWrite(redPin, 0);
		analogWrite(bluePin, 0);
		//Serial.println("tIdeal");
	}else if(tempF < tLow){
		//bottom out
		analogWrite(greenPin, 0);
		analogWrite(redPin, 0);
		analogWrite(bluePin, brightness);
		//Serial.println("bottom out");
	}else if(tempF > tHigh){
		//top out
		analogWrite(greenPin, 0);
		analogWrite(redPin, brightness);
		analogWrite(bluePin, 0);
		//Serial.println("top out");
	}else{

		//ok range
		if(tempF > (tIdeal-justRightRange) && tempF < tIdeal ){
			analogWrite(greenPin, cool);
			//Serial.println("cool");
		}else if(tempF < (tIdeal+justRightRange) && tempF > tIdeal){
			analogWrite(greenPin, warm);
			//Serial.println("warm");
		}else{
			analogWrite(greenPin, 0);
		}

		//hot and cold going
		analogWrite(redPin, tooHot);
		analogWrite(bluePin, tooCold); 
	}

}
