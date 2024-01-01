#include<strcal.h>
strcal::strnum number;
String n;
char operation;
void setup(){
	Serial.begin(9600);
  	return;
}
void loop(){
	Serial.print("The first number: ");
	while(!Serial.available());
	number.num=Serial.readString(),number.num.trim(),Serial.println(number.num),Serial.print("The operator: ");
	while(!Serial.available());
	operation=Serial.readString()[0],Serial.println(operation),Serial.print("The second number: ");
	while(!Serial.available());
	n=Serial.readString(),n.trim(),Serial.println(n);
	if(number.isnum()&&strcal::isnum(n)){
		number.fixnum(),number.calculate(strcal::fixnum(n),operation);
		if(number.num=="")
			Serial.println("Cannot divide by zero!");
		else
			Serial.print("The answer: "),Serial.println(number.num);
	}else
		Serial.println(number.isnum()^strcal::isnum(n)?number.isnum()?"The first input isn't a number!":"The second input isn't a number!":"The first & the second input aren't numbers!");
	return;
}
