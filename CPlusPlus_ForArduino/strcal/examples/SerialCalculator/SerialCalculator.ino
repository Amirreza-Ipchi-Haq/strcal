//(Tip: You can avoid using `strcal::` namespace by using `using namespace strcal;` in the line after including strcal.h (Don't do this if it conflicts with other libraries))
#include<strcal.h>//https://github.com/Amirreza-Ipchi-Haq/strcal
String input,x,y;//Assign 3 strings which the first one stores the input and the last 2 store numbers
char operation;//Assign the operator character
void setup(){
	Serial.begin(9600);//Setup serial communication at 9600 bits per second (Default baud rate)
  	return;
}
void loop(){
	x="",y="";//Clears both number strings
	while(!Serial.available());//Waits for input
	input=Serial.readString();//Reads the operation
	input.trim();//Removes leading/trailing whitespaces from the input
	{//Assigns the number strings & the operator in a temporary scope
		size_t i=0;//Assigns an iterator
		for(;input[i]!='+'&&(input[i]!='-'||!i)&&input[i]!='*'&&input[i]!='/'&&input[i]!='%';x+=String(input[i]),i++)//Reads the first number string
			if(i+1==input.length()){//(Have reached the end)
				Serial.println("Not a valid operation!");
				return;
			}
		x.trim();//Trims the first number string
		operation=input[i],y=input.substring(i+1);//Reads the operator & the second number string
	}
	y.trim();//Trims the second number string
	if(strcal::isrnum(x)&&strcal::isrnum(y)){//(Both numbers are valid)
		x=strcal::rcalculate(strcal::fixrnum(x),strcal::fixrnum(y),operation);//Does operation on both numbers in their standard form based on the operator and stores the answer
		if(x=="")//Alerts if the calculation was dividing by 0 (An empty string returned by the `calculate` function indicates such)
			Serial.println("Cannot divide by zero!");
		else//Shows the answer
			Serial.println(x);
	}else//Tells which numbers are invalid
		Serial.println(strcal::isrnum(x)^strcal::isrnum(y)?strcal::isrnum(x)?"The first input isn't a number!":"The third input isn't a number!":"The first & the third input aren't numbers!");
	return;
}
