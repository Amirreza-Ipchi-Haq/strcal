#ifndef CPPSTRCAL_H
#define CPPSTRCAL_H
#include<string>
namespace strcal{
	bool isWhole(std::string n){//Assign a function which checks if a string contains digits only
		for(size_t i=n.size();i--;)//Check each index
			if(n[i]<'0'||n[i]>'9')//Return false if the current index character is not a digit
				return 0;
		return 1;//Return true if not
	}
	std::string mltstr(std::string s,std::string s0,size_t n){//Assign a function which "multiplies" the second string and appends it to the first one
		while(n--)//Append the second string `n` times which `n` is initialized
			s+=s0;
		return s;//Return the result
	}
	bool strExists(std::string s,std::string s0){//Assign a function which checks if a certain substring exists
		return s.find(s0)!=std::string::npos;//Return the answer (This is actually a shortcut function)
	}
	std::string rmstr(std::string s,std::string s0){//Assign a function which entirely removes a certain substring from a string
		while(strExists(s,s0))//Continue deleting the substring until it's gone
			s.erase(s.find(s0),s0.size());
		return s;//Return the result
	}
	std::string absstr(std::string n){//Assign a fuction which removes the first '-' from a string if there's any
		if(n[0]=='-')//Remove the first '-' from the string if it exists
			n.erase(0,1);
		return n;//Return the results
	}
	bool isnum(std::string n){//Assign a function which checks if a string represents a number (standard (like 1) or non-standard (like 1.0))
		if(!n.size()||(n.size()<2&&!isWhole(n)))//Return false if the string is empty, or if it contains one character, it's not a digit
			return 0;
		n=absstr(n);//Remove the first '-' from the string if there's any
		if(strExists(n,"-"))//Return false if there are more '-'s
			return 0;
		if(strExists(n,".")){//(A '.' exists)
			if(n[0]=='.'||n.back()=='.'||n.find('.')!=n.rfind('.'))//Return false if the first/last index of the string is '.', or there are more than one '.'
				return 0;
			n=rmstr(n,".");//Remove the '.' from a string
		}
		return isWhole(n);//Check if the result is a whole number and return the result
	}
	std::string fixnum(std::string n){//Assign a function which turns a number string into its standard form
		if(n.size()<2)//Return the same string if it contains only 1 character (since it can only hold a digit)
			return n;
		char sign=n[0]=='-';//Assign the sign variable
		n=absstr(n);//Turn the number into it's absolute form
		while((strExists(n,".")?n.find('.')-1:n.size())>1&&n[0]=='0')//Remove the '0's at the left
			n.erase(0,1);
		if(strExists(n,"."))//(The string contains '.')
			while(n.back()=='0'||n.back()=='.')//Remove the '0's at the right
				n.pop_back();
		return n=="0"?"0":sign?n.insert(0,1,'-'):n;//Return the result with the sign back (If it's "0", the sign is ignored)
	}
	std::string returnPoint(std::string n,size_t posFromRight){//Assign a function which returns '.' back to a string
		if(!posFromRight)//Return the original string if the position of '.' to be put from the right is 0
			return n;
		return fixnum("0"+n.insert(n.size()-posFromRight,"."));//Return the string with the '.' back
	}
	void removeDecimals(std::string &x,std::string &y){//Assign a function which removes the floating point by multiplying both numbers by 10
		if(strExists(x,".")&&!strExists(y,"."))//Add '0's with the number of decimals in the first string to the second string and remove the '.' from the first one if the first string contains '.' and the second string doesn't
			y=fixnum(mltstr(y,"0",x.size()-x.find('.')-1)),x=fixnum(rmstr(x,"."));
		else if(!strExists(x,".")&&strExists(y,"."))//Do the exact opposite of the statement above if the condition above was exactly the opposite
			x=fixnum(mltstr(x,"0",y.size()-y.find('.')-1)),y=fixnum(rmstr(y,"."));
		else if(strExists(x,".")&&strExists(y,".")){//(Both strings contain '.')
			char swap=0;//Assign the swap indicator
			if(x.size()-x.find('.')<y.size()-y.find('.'))//Swap both strings and set the indicator to 1 (which represents true) if the second string has more decimals than the first string
				std::swap(x,y),swap=1;
			y=mltstr(fixnum(rmstr(y,".")),"0",x.size()-x.find('.')-y.size()+y.find('.')),x=fixnum(rmstr(x,"."));//Add '0's with the number of the difference between decimals of both strings to the second string and remove the '.' from the first string
			if(swap)//Swap both strings back if they've been swapped before
				std::swap(x,y);
		}
		return;
	}
	std::string addWhole(std::string x,std::string y){//Assign a function which adds 2 whole numbers as a string
		if(y=="0")//Return the first string if the second string is "0"
			return x;
		std::string answer;//Assing the answer string
		char add=0;//Assign the addition variable
		if(x.size()<y.size())//Swap both strings if the second string contains more characters
			std::swap(x,y);
		for(size_t i=x.size();i--;)//Do the addition digit by digit
			if(i<x.size()-y.size())
				answer.insert(0,1,(x[i]-'0'+add)%10+'0'),add=(x[i]-'0'+add)/10;
			else
				answer.insert(0,1,(x[i]+y[i-(x.size()-y.size())]-2*'0'+add)%10+'0'),add=(x[i]+y[i-(x.size()-y.size())]-2*'0'+add)/10;
		return add?answer.insert(0,1,'1'):answer;//Return the answer (with the '1' at the left if the addition variable is 1)
	}
	uint8_t cmpstr(std::string a,std::string b){//Assign a function which compares strings (Same as `strcmp` whith the difference that it works with C++ style strings and the return type & value are different)
		if(a.size()>b.size())//Return 1 indicating that the first string is bigger if it has more characters than the second string
			return 1;
		if(a.size()<b.size())//Return 2 indicating the exact opposite if the condition above is exactly the opposite
			return 2;
		for(size_t i=0;i<a.size();i++)//Check each character inside both strings (because both have the same length)
			if(a[i]>b[i])//Return 1 indicating that the first string is bigger if the current index character is bigger than the one in the second string
				return 1;
			else if(a[i]<b[i])//Return 2 indicating the exact opposite if the condition above is exactly the opposite
				return 2;
		return 0;//Return 0 indicating that both strings are exactly the same
	}
	uint8_t mod10(int8_t n){//Assign a function which finds mod10
		return n<0?10+n%10:n%10;//Return the answer
	}
	std::string subtractWhole(std::string x,std::string y){//Assign a function which subtracts a whole number from another as strings
		if(x==y)//Return "0" if both numbers are equal
			return "0";
		if(y=="0")//Return the first string if the second string is "0"
			return x;
		std::string answer;//Assign the answer string
		char sign=cmpstr(x,y)>1,subtract=0;//Assign the sign indicator (which is 1 (true) if the second string is bigger)
		if(sign)//Swap both strings if the sign indicator represents true
			std::swap(x,y);
		for(size_t i=x.size();i--;)//Do the subtraction digit by digit
			if(i<x.size()-y.size())
				answer.insert(0,1,mod10(x[i]-'0'-subtract)+'0'),subtract=x[i]-'0'-subtract<0?1:0;
			else
				answer.insert(0,1,mod10(x[i]-y[i-(x.size()-y.size())]-subtract)+'0'),subtract=x[i]-y[i-(x.size()-y.size())]-subtract<0?1:0;
		return fixnum(sign?answer.insert(0,1,'-'):answer);//Return the answer in its standard form with the sign back
	}
	std::string simpleWholeDivide(std::string x,std::string y,bool option){//Assign a function which does division between 2 numbers as strings in a simple way (useful if x/y<10)
		if(y=="0")//Return an empty string if the second string is "0"
			return "";
		if(y=="1"){//(The second string is "1")
			if(option)//Return "0" if the function asks for the remainder
				return "0";
			return x;//Return the first string if not
		}
		if(x=="0")//Return "0" if the first string is also "0"
			return "0";
		if(option&&(y=="2"||y=="5"))//Return the remainder of the last digit of the first string divided by the second string if the function asks for the remainder and the second string is either "2" or "5"
			return std::string(1,(x.back()-'0')%(y[0]-'0')+'0');
		if(option&&y[0]=='1'&&fixnum(y.substr(1,-1))=="0")//Return the second first string's last characters with the number of '0's of the second string, or if the second string is bigger than the first one, return the first string, if the function asks for the remainder and the second string is a power of 10
			return x.size()<y.size()?x:x.substr(x.size()-y.size()+1,-1);
		if(x==y)//(Both strings are equal)
			return option?"0":"1";//Return "0" if the function asks for the remainder, unless, return "1"
		if(cmpstr(x,y)>1)//(The second string is bigger)
			return option?x:"0";//Return the first string if the function asks for the remainder, unless, return "0"
		std::string answer="0";//Assign the answer string with the value of "0"
		while(cmpstr(x,y)<2)//Continue subtracting the second string from the first string and add 1 to the answer until the second string is bigger than the first one
			answer=addWhole(answer,"1"),x=subtractWhole(x,y);
		return option?x:answer;//Return the remainder if the function asks for the remainder, unless, return the answer string
	}
	std::string divideWhole(std::string x,std::string y,bool option){//(Same as the function above with speed improvements (Uses the function above))
		if(y=="0")//Return an empty string if the second string is "0"
			return "";
		if(y=="1"){//(The second string is "1")
			if(option)//Return "0" if the function asks for the remainder
				return "0";
			return x;//Return the first string if not
		}
		if(x=="0")//Return "0" if the first string is also "0"
			return "0";
		if(option&&(y=="2"||y=="5"))//Return the remainder of the last digit of the first string divided by the second string if the function asks for the remainder and the second string is either "2" or "5"
			return std::string(1,(x.back()-'0')%(y[0]-'0')+'0');
		if(option&&y[0]=='1'&&fixnum(y.substr(1,-1))=="0")//Return the second first string's last characters with the number of '0's of the second string, or if the second string is bigger than the first one, return the first string, if the function asks for the remainder and the second string is a power of 10
			return x.size()<y.size()?x:x.substr(x.size()-y.size()+1,-1);
		if(x==y)//(Both strings are equal)
			return option?"0":"1";//Return "0" if the function asks for the remainder, unless, return "1"
		if(cmpstr(x,y)>1)//(The second string is bigger)
			return option?x:"0";//Return the first string if the function asks for the remainder, unless, return "0"
		std::string answer0="",answer1=std::string(1,x[0]);//Assign the answer and the remainder strings
		for(size_t i=x.size();i--;answer0=answer0+simpleWholeDivide(answer1,y,0),answer1=fixnum(simpleWholeDivide(answer1,y,1)+(i?std::string(1,x[x.size()-i]):"")));//Do the division digit by digit
		return option?answer1:fixnum(answer0);//Return what the function asked for
	}
	std::string gcd(std::string x,std::string y){//Assign a function which finds the greatest common divisor between 2 natural numbers as strings using the Euclidean algorithm
		if(x=="0"||y=="0")//Return an empty string if either one of the strings is "0"
			return "";
		if(x==y)//Return the first string if both strings are equal
			return x;
		std::string tmp;//Assign a temporary string
		while(x.back()<'1'&&y.back()<'1')//Remove the common factor 10 from both strings
			x.pop_back(),y.pop_back();
		while(x!="0"&&y!="0")//Find the remainder of both strings until one of them is "0"
			tmp=divideWhole(x,y,1),y=divideWhole(y,x,1),x=tmp;
		return x=="0"?y:x;//Return the non-"0" string
	}
	std::string calculate(std::string x,std::string y,char operation){//Assign the function which calculates 2 numbers with a given operator
		std::string answer=operation=='*'?"0":operation=='/'&&((x[0]=='-')^(y[0]=='-'))?"-":"";//Assign the answer string
		size_t divide=operation=='+'||operation=='-'||operation=='*'||operation=='%'?!strExists(x,".")&&!strExists(y,".")?0:strExists(x,".")&&!strExists(y,".")?x.size()-x.find('.')-1:!strExists(x,".")&&strExists(y,".")?y.size()-y.find('.')-1:operation=='*'?x.size()+y.size()-x.find('.')-y.find('.')-2:x.size()-x.find('.')>y.size()-y.find('.')?x.size()-x.find('.')-1:y.size()-y.find('.')-1:0;//Assign the division variable for returning the floating point (usless for division)
		switch(operation){//Check the operator
			case '+'://Do the addition
				removeDecimals(x,y);//Turn both strings into integers
				if(x[0]=='-'&&y[0]!='-')//Subtract the absolute value of the first string from the second string if the first string has '-' and the second doesn't
					answer=subtractWhole(y,absstr(x));
				else if(x[0]!='-'&&y[0]=='-')//Do the exact opposite if the condition above is exactly the opposite
					answer=subtractWhole(x,absstr(y));
				else//Do the addition to both strings with their sign at the left if both strings are either positive or negative
					answer=(x[0]=='-'?"-":"")+addWhole(absstr(x),absstr(y));
				return returnPoint(answer,divide);//Return the answer with the floating point back
			case '-':
				removeDecimals(x,y);//Turn both strings into integers
				if((x[0]=='-')^(y[0]=='-'))//Do the addition to the absolute value of both strings if only one of them has '-' and add the '-' to the left of the answer if the first string has it
					answer=(x[0]=='-'?"-":"")+addWhole(absstr(x),absstr(y));
				else//Do the subtraction to the absolute value of both strings if not (The sub-condition which is commented above is also done here)
					answer=(x[0]=='-'?"-":"")+subtractWhole(absstr(x),absstr(y)),answer.erase(0,2*(answer.substr(0,2)=="--"));
				return returnPoint(answer,divide);//Return the answer with the floating point back
			case '*'://Do the multiplication
				if(x=="0"||y=="0")//Return "0" if one of the strings has the same value
					return "0";
				if(x=="1"||y=="1"){//(One of the strings is "1")
					if(x=="1")//Return the second string if the first string is "1"
						return y;
					else//Return the second string if not
						return x;
				}
				{//(Has local variables)
					std::string answer0;//Assign the sub-answer string
					char add0=0,add1=0,sign=(x[0]=='-')^(y[0]=='-');//Assign the first addition variable, the second addition variable & the sign indicator
					x=fixnum(rmstr(absstr(x),".")),y=fixnum(rmstr(absstr(y),"."));//Remove '.' & '-' from both strings
					for(size_t i=x.size();i--;answer=addWhole(answer,(add0?std::string(1,add0+'0'):"")+answer0),add0=0,answer0=mltstr("","0",x.size()-i))//Do the multiplication digit by digit
						for(size_t j=y.size();j--;answer0.insert(0,1,(add0+add1)%10+'0'),add0=(add0+add1)/10,add1=0)
							for(char k=x[i]-'0';k--;add1+=y[j]-'0');
					return returnPoint(mltstr(sign?"-":"","0",divide)+answer,divide);//Return the answer if the sign & the floating point back
				}
			case '%'://Find the remainder
				if(y=="0")//Break out of the switch-case statement if the second string is "0" (which is invalid)
					break;
				removeDecimals(x,y);//Turn both strings into integers
				return returnPoint(((x[0]=='-')^(y[0]=='-')?"-":"")+divideWhole(absstr(x),absstr(y),1),divide);//Return the remainder with the floating point back
			case '/':
				if(y=="0")//Break out of the switch-case statement if the second string is "0" (which is invalid)
					break;
				if(x=="0")//Return "0" if the first string has the same value
					return "0";
				if(x==y)//Return "1" if both strings are equal
					return "1";
				removeDecimals(x,y),x=absstr(x),y=absstr(y);//Turn both strings into whole numbers
				{//(Has local variables
					std::string divide=gcd(x,y);//Assign the division simplifier string
					x=divideWhole(x,divide,0),y=divideWhole(y,divide,0);//Divide both numbers by their greatest common divisor
				}
				answer=answer+divideWhole(x,y,0),x=divideWhole(x,y,1);//Store the integer part of the division and store the remainder inside the first string
				if(x!="0"){//(The answer has decimals)
					answer=answer+".";//Append "." to the answer string
					std::string tmp=y;//Assign a temporary string with the value of the second string (to find the terminating decimals)
					for(;tmp.back()<'1';tmp.pop_back(),x=x+"0",answer=answer+simpleWholeDivide(x,y,0),x=simpleWholeDivide(x,y,1))//Continue the division digit by digit and divide the temporary string by 10 until it's not divisible by 10
						if(x=="0")//Skip to the returning if the remainder is "0"
							goto finish;
					if(tmp.back()=='5'){//(The temporary string is still divisible by 5)
						for(;tmp.back()=='5';tmp=divideWhole(tmp,"5",0),x=x+"0",answer=answer+simpleWholeDivide(x,y,0),x=simpleWholeDivide(x,y,1))//Continue the division digit by digit and divide the temporary string by 5 until it's not divisible by 5
							if(x=="0")//Skip to the returning if the remainder is "0"
								goto finish;
					}else//(The temporary string is not divisible by 5)
						for(;(tmp.back()-'0')%2<1;tmp=divideWhole(tmp,"2",0),x=x+"0",answer=answer+simpleWholeDivide(x,y,0),x=simpleWholeDivide(x,y,1))//Continue the division digit by digit and divide the temporary string by 2 until it's not divisible by 2
							if(x=="0")//Skip to the finalization if the remainder is "0"
								goto finish;
					if(tmp=="1")//Skip to the returning if the temporary string is "1"
						goto finish;
					for(tmp=x,x=x+"0",answer=answer+"("+simpleWholeDivide(x,y,0),x=simpleWholeDivide(x,y,1);x!=tmp;x=x+"0",answer=answer+simpleWholeDivide(x,y,0),x=simpleWholeDivide(x,y,1))//Store the current remainder in the temporary string, append "(" to the answer string and continue the division digit by digit until the current remainder is the same as the stored one
						if(x=="0"){//Remove the '(' from the answer string and skip to the returning if the remainder is "0"
							answer=rmstr(answer,"(");//(Removement part)
							goto finish;//(Skipping part)
						}
					answer=fixnum(answer.substr(answer.find('(')+1,-1))=="0"?fixnum(rmstr(answer,"(")):answer+")";//Finalize the answer string
				}
				finish:
				return answer;//Return the answer
		}
		return "";//Return an empty string if the operation is invalid
	}
	class strnum{//Assign a class which stores a number string and does some of the operations above on it
		public://(All properties are public)
			std::string num;//Assign the main string
			strnum(std::string n="0"){//Assign the initializer (All the methods below are basically the functions above)
				num=n;//Initialize the number string
				return;
			}
			bool isWhole(){
				return strcal::isWhole(num);
			}
			bool strExists(std::string s){
				return strcal::strExists(num,s);
			}
			std::string rmstr(std::string s){
				num=strcal::rmstr(num,s);
				return num;
			}
			std::string absstr(){
				num=strcal::absstr(num);
				return num;
			}
			bool isnum(){
				return strcal::isnum(num);
			}
			std::string fixnum(){
				num=strcal::fixnum(num);
				return num;
			}
			std::string returnPoint(size_t posFromRight){
				num=strcal::returnPoint(num,posFromRight);
				return num;
			}
			uint8_t cmpstr(std::string s){
				return strcal::cmpstr(num,s);
			}
			std::string gcd(std::string n){
				return strcal::gcd(num,n);
			}
			std::string calculate(std::string n,char operation){
				num=strcal::calculate(num,n,operation);
				return num;
			}
	};
}
#endif
