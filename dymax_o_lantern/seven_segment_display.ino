//for four digit seven segment displays

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

//      A
//    F   B
//      G
//    E   C
//      D   dp (H)
// LOW == on
// HIGH == off
void sn(int num){
	// take the latchPin low so 
	// the LEDs don't change while you're sending in bits:
	digitalWrite(latchPin, LOW);
	// shift out the bits:
	shiftOut(dataPin, clockPin, MSBFIRST, dataArray[num]);  
	//take the latch pin high so the LEDs will light up:
	digitalWrite(latchPin, HIGH);
}
/*
//segment numbers
void sn(int num){

	
	switch(num){
		case 0:
			digitalWrite(A,LOW);
			digitalWrite(B,LOW);
			digitalWrite(C,LOW);
			digitalWrite(D,LOW);
			digitalWrite(E,LOW);
			digitalWrite(F,LOW);
			digitalWrite(G,HIGH);
		break;
		case 1:
			digitalWrite(A,HIGH);
			digitalWrite(B,LOW);
			digitalWrite(C,LOW);
			digitalWrite(D,HIGH);
			digitalWrite(E,HIGH);
			digitalWrite(F,HIGH);
			digitalWrite(G,HIGH);
		break;
		case 2:
			digitalWrite(A,LOW);
			digitalWrite(B,LOW);
			digitalWrite(C,HIGH);
			digitalWrite(D,LOW);
			digitalWrite(E,LOW);
			digitalWrite(F,HIGH);
			digitalWrite(G,LOW);
		break;
		case 3:
			digitalWrite(A,LOW);
			digitalWrite(B,LOW);
			digitalWrite(C,LOW);
			digitalWrite(D,LOW);
			digitalWrite(E,HIGH);
			digitalWrite(F,HIGH);
			digitalWrite(G,LOW);
		break;
		case 4:
			digitalWrite(A,HIGH);
			digitalWrite(B,LOW);
			digitalWrite(C,LOW);
			digitalWrite(D,HIGH);
			digitalWrite(E,HIGH);
			digitalWrite(F,LOW);
			digitalWrite(G,LOW);
		break;
		case 5:
			digitalWrite(A,LOW);
			digitalWrite(B,HIGH);
			digitalWrite(C,LOW);
			digitalWrite(D,LOW);
			digitalWrite(E,HIGH);
			digitalWrite(F,LOW);
			digitalWrite(G,LOW);
		break;
		case 6:
			digitalWrite(A,LOW);
			digitalWrite(B,HIGH);
			digitalWrite(C,LOW);
			digitalWrite(D,LOW);
			digitalWrite(E,LOW);
			digitalWrite(F,LOW);
			digitalWrite(G,LOW);
		break;
		case 7:
			digitalWrite(A,LOW);
			digitalWrite(B,LOW);
			digitalWrite(C,LOW);
			digitalWrite(D,HIGH);
			digitalWrite(E,HIGH);
			digitalWrite(F,HIGH);
			digitalWrite(G,HIGH);
		break;
		case 8:
			digitalWrite(A,LOW);
			digitalWrite(B,LOW);
			digitalWrite(C,LOW);
			digitalWrite(D,LOW);
			digitalWrite(E,LOW);
			digitalWrite(F,LOW);
			digitalWrite(G,LOW);
		break;
		case 9:
			digitalWrite(A,LOW);
			digitalWrite(B,LOW);
			digitalWrite(C,LOW);
			digitalWrite(D,HIGH);
			digitalWrite(E,HIGH);
			digitalWrite(F,LOW);
			digitalWrite(G,LOW);
		break;
		default:
			//your fault
		break;
	}
}

void sl(char let){
	
	switch(let){
		case 'A':
			digitalWrite(A,LOW);
			digitalWrite(B,LOW);
			digitalWrite(C,LOW);
			digitalWrite(D,HIGH);
			digitalWrite(E,LOW);
			digitalWrite(F,LOW);
			digitalWrite(G,LOW);
		break;
		case 'B':
			digitalWrite(A,HIGH);
			digitalWrite(B,HIGH);
			digitalWrite(C,LOW);
			digitalWrite(D,LOW);
			digitalWrite(E,LOW);
			digitalWrite(F,LOW);
			digitalWrite(G,LOW);
		break;
		case 'C':
			digitalWrite(A,LOW);
			digitalWrite(B,HIGH);
			digitalWrite(C,HIGH);
			digitalWrite(D,LOW);
			digitalWrite(E,LOW);
			digitalWrite(F,LOW);
			digitalWrite(G,HIGH);
		break;
		case 'D':
			digitalWrite(A,HIGH);
			digitalWrite(B,LOW);
			digitalWrite(C,LOW);
			digitalWrite(D,LOW);
			digitalWrite(E,LOW);
			digitalWrite(F,HIGH);
			digitalWrite(G,LOW);
		break;
		case 'E':
			digitalWrite(A,LOW);
			digitalWrite(B,HIGH);
			digitalWrite(C,HIGH);
			digitalWrite(D,LOW);
			digitalWrite(E,LOW);
			digitalWrite(F,LOW);
			digitalWrite(G,LOW);
		break;
		case 'F':
			digitalWrite(A,LOW);
			digitalWrite(B,HIGH);
			digitalWrite(C,HIGH);
			digitalWrite(D,HIGH);
			digitalWrite(E,LOW);
			digitalWrite(F,LOW);
			digitalWrite(G,LOW);
		break;
		case 'G':
			digitalWrite(A,LOW);
			digitalWrite(B,LOW);
			digitalWrite(C,LOW);
			digitalWrite(D,LOW);
			digitalWrite(E,HIGH);
			digitalWrite(F,LOW);
			digitalWrite(G,LOW);
		break;
		case 'H':
			digitalWrite(A,HIGH);
			digitalWrite(B,LOW);
			digitalWrite(C,LOW);
			digitalWrite(D,HIGH);
			digitalWrite(E,LOW);
			digitalWrite(F,LOW);
			digitalWrite(G,LOW);
		break;
		case 'I':
			digitalWrite(A,HIGH);
			digitalWrite(B,HIGH);
			digitalWrite(C,HIGH);
			digitalWrite(D,HIGH);
			digitalWrite(E,LOW);
			digitalWrite(F,LOW);
			digitalWrite(G,HIGH);
		break;
		case 'J':
			digitalWrite(A,HIGH);
			digitalWrite(B,LOW);
			digitalWrite(C,LOW);
			digitalWrite(D,LOW);
			digitalWrite(E,LOW);
			digitalWrite(F,HIGH);
			digitalWrite(G,HIGH);
		break;
		case 'L':
			digitalWrite(A,HIGH);
			digitalWrite(B,HIGH);
			digitalWrite(C,HIGH);
			digitalWrite(D,LOW);
			digitalWrite(E,LOW);
			digitalWrite(F,LOW);
			digitalWrite(G,HIGH);
		break;
		case 'P':
			digitalWrite(A,LOW);
			digitalWrite(B,LOW);
			digitalWrite(C,HIGH);
			digitalWrite(D,HIGH);
			digitalWrite(E,LOW);
			digitalWrite(F,LOW);
			digitalWrite(G,LOW);
		break;
		case 'U':
			digitalWrite(A,HIGH);
			digitalWrite(B,LOW);
			digitalWrite(C,LOW);
			digitalWrite(D,LOW);
			digitalWrite(E,LOW);
			digitalWrite(F,LOW);
			digitalWrite(G,HIGH);
		break;
		case 'Y':
			digitalWrite(A,HIGH);
			digitalWrite(B,LOW);
			digitalWrite(C,LOW);
			digitalWrite(D,LOW);
			digitalWrite(E,HIGH);
			digitalWrite(F,LOW);
			digitalWrite(G,LOW);
		break;
		case '-':
			digitalWrite(A,HIGH);
			digitalWrite(B,HIGH);
			digitalWrite(C,HIGH);
			digitalWrite(D,HIGH);
			digitalWrite(E,HIGH);
			digitalWrite(F,HIGH);
			digitalWrite(G,LOW);
		break;
		default:
			//your fault
		break;
	}
}
*/


