//(Tip: You can avoid using `strcal::` namespace by using `using namespace strcal;` in the line after including strcal.h (Don't do this if it conflicts with other libraries))
#include<strcal.h>//https://github.com/Amirreza-Ipchi-Haq/strcal
String x,y;//Assign 2 strings which store numbers
char operation;//Assign the operator character
void setup(){
	Serial.begin(9600);//Setup serial communication at 9600 bits per second (Default baud rate)
  	return;
}
void loop(){
	Serial.print("The first number: ");//Prompt for the first number
	while(!Serial.available());//Wait for input
	x=Serial.readString().trim(),Serial.println(x),Serial.print("The operator: ");//Store the first number, trim it, display it and prompt for the operator
	while(!Serial.available());//Wait for input
	operation=Serial.readString()[0],Serial.println(operation),Serial.print("The second number: ");//Store the operator character, display it and prompt for the second number
	while(!Serial.available());//Wait for input
	y=Serial.readString().trim(),Serial.println(y);//Store the second number, trim it and display it
	if(operation!='+'&&operation!='-'&&operation!='*'&&operation!='%'&&operation!='/')//Alert if the operator isn't valid
		Serial.println("Not a valid operator!");
	else if(strcal::isnum(x)&&strcal::isnum(y)){//Both numbers are valid
		x=strcal::calculate(strcal::fixnum(x),strcal::fixnum(y),operation);//Do operation on both numbers in their standard form based on the operator and store it
		if(x=="")//Alert if the calculation was dividing by 0 (An empty string returned by the `calculate` function indicates such)
			Serial.println("Cannot divide by zero!");
		else//Show the answer
			Serial.print("The answer: "),Serial.println(x);
	}else//Tell which numbers are invalid
		Serial.println(strcal::isnum(x)^strcal::isnum(y)?strcal::isnum(x)?"The first input isn't a number!":"The third input isn't a number!":"The first & the third input aren't numbers!");
	return;
}
