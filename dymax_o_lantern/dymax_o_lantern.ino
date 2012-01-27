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

//      A
//    F   B
//      G
//    E   C
//      D   dp (H)
//
//  In binary representation, right most digit is A
*/



#include <math.h>
int thermistor = 0;

/*
int photoresistor = 1;
int REDPin = 11;    // RED pin of the LED to PWM pin 4 
int GREENPin = 9;  // GREEN pin of the LED to PWM pin 5
int BLUEPin = 10;   // BLUE pin of the LED to PWM pin 6
*/
int digit1 = 9, digit2 = 10, digit3 = 11, digit4 = 12;

int A = 2;
int B = 3;
int C = 4;
int D = 5;
int E = 6;
int F = 7;
int G = 8;
//int dp = NEED IT?

int i = 0;
unsigned long currentTime = 0;

//http://arduino.cc/playground/ComponentLib/Thermistor2
double Thermistor(int RawADC) {
	double Temp;
	Temp = log(((10240000/RawADC) - 10000));
	Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp );
	Temp = Temp - 273.15;            // Convert Kelvin to Celsius
	//Temp = (Temp * 9.0)/ 5.0 + 32.0; // Convert Celcius to Fahrenheit
	return Temp;
}

void setup() {
	Serial.begin(9600);
	/*
	pinMode(REDPin, OUTPUT); 
	pinMode(GREENPin, OUTPUT); 
	pinMode(BLUEPin, OUTPUT);
	pinMode(photoresistor, INPUT);
	//pinMode(motor, OUTPUT); 
	*/
	pinMode(digit1, OUTPUT);
	pinMode(digit2, OUTPUT);
	pinMode(digit3, OUTPUT);
	pinMode(digit4, OUTPUT);
	
	pinMode(A,OUTPUT);
	pinMode(B,OUTPUT);
	pinMode(C,OUTPUT);
	pinMode(D,OUTPUT);
	pinMode(E,OUTPUT);
	pinMode(F,OUTPUT);
	pinMode(G,OUTPUT);
}

void loop() {
	currentTime = millis() / 1000;
	
	int temp = int(Thermistor(analogRead(thermistor)));
	//tempLightGuage();

	//Serial.println("temperature:");
	//Serial.print(tempC);  // display Celsius
	//Serial.print(" C | ");
	//Serial.print(tempF); 
	//Serial.println(" F");
	//Serial.println(currentTime);
	
	
	/* for later
	
	if(unit == "C"){
		displayTemperature(temp, 'C');
	}else if(unit == "F"){
		displayTemperature((temp * 9.0)/ 5.0 + 32.0, 'F');
	}
	
	*/
	if(currentTime % 2){
		displayTemperature(temp, 'C');
	}else{
		displayTemperature((temp * 9.0)/ 5.0 + 32.0, 'F');
	}
	
	
	
	/*testing
	if(currentTime < 3){
		displayTemperature(-8);
	}else if(currentTime >= 3 && currentTime < 6){
		displayTemperature(-86);
	}else if(currentTime >= 6 && currentTime < 9){
		displayTemperature(4);
	}else if(currentTime >= 9 && currentTime < 12){
		displayTemperature(36);
	}else if(currentTime >= 12 && currentTime < 15){
		displayTemperature(100);
	}else if(currentTime >= 15 && currentTime < 18){
		displayTemperature(105);
	}else if(currentTime >= 18 && currentTime < 21){
		displayTemperature(157);
	}else if(currentTime >= 21 && currentTime < 24){
		displayTemperature(-157); interesting... negitive sign is combinded with 1 on first digit. when hell freezes over
	}
	*/
	
}

void displayTemperature(int temp, char unit){
	//if temp is negative, set negitive sign to correct digit
	if(temp < 0){
		if(temp < -9){
			dd(1);
		}else{
			dd(2);
		}
		sl('-');
		delay(2);
		//set temp to positive int
		temp = abs(temp);
	}
	
	if(temp >= 100){
		//1st digit temp - 100's place
		dd(1);
		sn(temp / 100);
		delay(2);
		
		if( (temp % 100) > 9){
			//2nd digit temp - 10's place
			dd(2);
			sn((temp % 100) / 10);
			delay(2);
			//3rd digit temp - 1's plance
			dd(3);
			sn((temp % 100) % 10);
			delay(2);
		}else{
			//2nd digit temp - 10's place
			dd(2);
			sn(0);
			delay(2);
			//3rd digit temp - 1's plance
			dd(3);
			sn((temp % 100));
			delay(2);
		}
		
		
	}else if(temp > 9 && temp < 100){
		//2nd digit temp - 10's place
		dd(2);
		sn(temp / 10);
		delay(2);
		//3rd digit temp - 1's plance
		dd(3);
		sn(temp % 10);
		delay(2);
	}else{
		//3rd digit temp - 1's place
		dd(3);
		sn(temp);
		delay(2);
	}
	
	dd(4);
	sl(unit);
	delay(2);
}
/*
void tempLightGuage(){
	//gauged arbitrarily in fahrenheit
	int tempF = (int(Thermistor(analogRead(thermistor))) * 9.0)/ 5.0 + 32.0;
	int photoResistance = analogRead(photoresistor);
	Serial.println("temp");
	Serial.println(tempF);  // display Fahrenheit
	Serial.println("photoresistance");
	Serial.println(photoResistance); 


	int brightness = map(photoResistance,0,1023,50,0); //0-255
	Serial.println("brightness");
	Serial.println(brightness); 
	int tLow = 60;
	int tHigh = 90;
	int tIdeal = 72;
	int justRightRange = 5;
	int cool = map( tempF, (tIdeal-justRightRange), tIdeal, 0, brightness );
	int warm = map( tempF, tIdeal, (tIdeal+justRightRange), 0, brightness ); 
	int tooCold =  map(tempF, tHigh, tLow, 0, brightness );
	int tooHot = map(tempF, tLow, tHigh, 0, brightness );

	if(tempF == tIdeal){
		analogWrite(GREENPin, brightness);
		analogWrite(REDPin, 0);
		analogWrite(BLUEPin, 0);
		Serial.println("tIdeal");
	}else if(tempF < tLow){
		//bottom out
		analogWrite(GREENPin, 0);
		analogWrite(REDPin, 0);
		analogWrite(BLUEPin, brightness);
		Serial.println("bottom out");
	}else if(tempF > tHigh){
		//top out
		analogWrite(GREENPin, 0);
		analogWrite(REDPin, brightness);
		analogWrite(BLUEPin, 0);
		Serial.println("top out");
	}else{

		//ok range
		if(tempF > (tIdeal-justRightRange) && tempF < tIdeal ){
			analogWrite(GREENPin, cool);
			Serial.println("cool");
		}else if(tempF < (tIdeal+justRightRange) && tempF > tIdeal){
			analogWrite(GREENPin, warm);
			Serial.println("warm");
		}else{
			analogWrite(GREENPin, 0);
		}

		//hot and cold going
		analogWrite(REDPin, tooHot);
		analogWrite(BLUEPin, tooCold); 
	}

}
*/
//hi();
/*
dd(1);
sl('C');
delay(1000);

dd(2);
sl('F');
delay(1000);

dd(3);
sl('H');
delay(1000);

dd(4);
sl('I');
delay(1000);

dd(1);
sl('E');
delay(1000);

dd(2);
sl('L');
delay(1000);

dd(3);
sl('U');
delay(1000);

dd(4);
sl('Y');
delay(1000);


dd(1);
sl('J');
delay(1000);

dd(2);
sl('B');
delay(1000);

dd(3);
sl('D');
delay(1000);

dd(4);
sl('G');
delay(1000);

dd(1);
sl('J');
delay(1000);

dd(2);
sl('A');
delay(1000);

dd(3);
sl('P');
delay(1000);

dd(4);
sl('G');
delay(1000);

void hi(){
	//digit
	dd(2);
	
	//segment
	sl('H');
	
	//digitalWrite(8,LOW);
	delay(2);
	
	//digit
	dd(3);
	
	//segment
	sl('I');
	
	//digitalWrite(8,HIGH);
	delay(2);
}
*/
/**/