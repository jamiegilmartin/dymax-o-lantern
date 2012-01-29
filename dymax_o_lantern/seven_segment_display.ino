//display digit
void dd(int num){
	//int digit1 = 9, digit2 = 10, digit3 = 11, digit4 = 12;
	switch(num){
		case 1:
			digitalWrite(digit2,LOW);
			digitalWrite(digit3,LOW);
			digitalWrite(digit4,LOW);
			digitalWrite(digit1,HIGH);
		break;
		case 2:
			digitalWrite(digit1,LOW);
			digitalWrite(digit3,LOW);
			digitalWrite(digit4,LOW);
			digitalWrite(digit2,HIGH);
		break;
		case 3:
			digitalWrite(digit1,LOW);
			digitalWrite(digit2,LOW);
			digitalWrite(digit4,LOW);
			digitalWrite(digit3,HIGH);
		break;
		case 4:
			digitalWrite(digit1,LOW);
			digitalWrite(digit2,LOW);
			digitalWrite(digit3,LOW);
			digitalWrite(digit4,HIGH);
		break;
		default:
		//your fault
		break;
	}
}

//display correct segments as numbers
void sn(int num){
	// take the latchPin low so 
	// the LEDs don't change while you're sending in bits:
	digitalWrite(latchPin, LOW);
	// shift out the bits:
	shiftOut(dataPin, clockPin, MSBFIRST, dataArray[num]);  
	//take the latch pin high so the LEDs will light up:
	digitalWrite(latchPin, HIGH);
}

