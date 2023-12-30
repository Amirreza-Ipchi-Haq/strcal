#ifndef _CSTRCAL_H_
#define _CSTRCAL_H_
#include<stdlib.h>
#include<string.h>
#define CHR2STR(c) (char[2]){c,0}//Assign a character-to-string function
#define MOD10(n) (char)(n<0?10+n%10:n%10)//Assign a function which finds `n mod 10`
char* strtmp(char* s,char release){//Assign a function which creates a temporary string (Same as `strdup` with memory management included)
	if(!s)//(The string is NULL)
		return s;//Return NULL
	char *s0=malloc((strlen(s)+1)*sizeof(char));//Allocate memory as much as the length of the string (until NUL) plus one more byte for NUL
	strcpy(s0,s);//Copy string content to the new string
	if(release)//Free the old string if told to
		free(s);
	return s0;//Return a pointer to the array allocated in the heap
}
char* strntmp(char* s,size_t len,char release){//(Same as the function above with a character limit from the left)
	if(!s)//(The string is NULL)
		return 0;//Return NULL
	if(!len){//(The number of characters to be copied is 0)
		if(release)//Free the string if told to
			free(s);
		return strtmp("",0);//Return a copy of an empty string
	}
	if(len>=strlen(s))//(The number of characters to be printed is more than the length os the string)
		return strtmp(s,release);//Return a copy of the string and free the original one if told to
	char s0[len+1];//Create a character array as much as the length limit plus one more index for NUL
	s0[len]=0;//Set the last index as NUL
	while(len--)//Copy the original string content to the array until the length limit
		s0[len]=s[len];
	if(release)//Free the original string if told to
		free(s);
	return strtmp(s0,0);//Return a copy of the character array
}
char* strnrtmp(char* s,size_t len,char release){//(Same as the function above with the limit starting from the right)
	if(!s)//(The string is NULL)
		return 0;//Return NULL
	if(!len){//(The number of characters to be copied is 0)
		if(release)//Free the string if told to
			free(s);
		return strtmp("",0);//Return a copy of an empty string
	}
	if(len>=strlen(s))//(The number of characters to be printed is more than the length os the string)
		return strtmp(s,release);//Return a copy of the string and free the original one if told to
	char s0[len+1];//Create a character array as much as the length limit plus one more index for NUL
	s0[len]=0;//Set the last index as NUL
	for(size_t i=strlen(s);len--;s0[len]=s[--i]);//Copy the original string content to the array from the right until the length limit
	if(release)//Free the original string if told to
		free(s);
	return strtmp(s0,0);//Return a copy of the character array
}
char* strappend(char* s0,char* s1,char release){//Assign a function which sticks 2 strings together and returns the result
	char s[strlen(s0)+strlen(s1)+1];//Create a char array as much as the sum of both string's length until NUL plus one more index for NUL
	strcat(strcpy(s,s0),s1);//Copy both string content into the character array
	if(release&2)//Free the first string if told to
		free(s0);
	if(release&1)//Free the second string if told to
		free(s1);
	return strtmp(s,0);//Return a copy of the character array
}
char isWhole(char* n){//Assign a function which checks if a string only contains digits
	for(size_t i=strlen(n);i--;)//Check every index
		if(n[i]<'0'||n[i]>'9')//(The current index contains something other than digits)
			return 0;//Return 0 which indicates as false
	return 1;//Return 1 which indicates as true
}
char* mltstr(char* s0,char* s1,size_t n,char release){//Assign a function which "multiplies" the second string and appends it to the first one
	char *s=strtmp(s0,release&2);//Create a copy of the first string an free the first string if told to
	while(n--)//Append the second string to the copy `n` times which `n` is initialized while calling the function
		s=strappend(s,s1,2);
	if(release&1)//Free the second string if told to
		free(s1);
	return s;//Return the copy
}
char* rmchr(char* n,char c,char release){//Assign a function which removes a character completely from a string
	char *n0=strtmp(n,release);//Create a copy of the string and free the original one if told to
	while(strchr(n0,c))//Remove the assigned character from the string until it doesn't exist in it
		n0=mltstr(strappend(strntmp(n0,strlen(n0)-strlen(strchr(n0,c)),0),strchr(strchr(n0,c),strchr(n0,c)[1]),2),n0,0,3);
	return n0;//Return the result
}
char* absstr(char* n,char release){//Assign a function which removes the first '-' if it exists from a string
	char *n0=n[0]=='-'?strtmp(strchr(n,n[1]),0):strtmp(n,0);//Create a copy of the original string without the first '-' if it exists
	if(release)//Free the original string if told to
		free(n);
	return n0;//Return the result
}
char isnum(char* n){//Check is a string represents a number (standard (like 1) or non-standard (like 01.0))
	if(!n||!strlen(n)||((n[0]<'0'||n[0]>'9')&&strlen(n)<2))//(The string is NULL/empty, or if it's length is 1, it contains something other than digits)
		return 0;//Return 0 which indicates as false
	char *n0=absstr(n,0);//Create a copy of the original string without the first '-' if it exists
	if(strchr(n0,'-')){//(There's more than one '-')
		free(n0);//Free the copy
		return 0;//Return 0 which indicates as false
	}
	if(strchr(n0,'.')){//(There's a '.' inside the string)
		if(n0[0]=='.'||n0[strlen(n0)-1]=='.'||strchr(strchr(strchr(n0,'.'),strchr(n0,'.')[1]),'.')){//(The first/last index of the string is '.', or there is more than one '.')
			free(n0);//Free the copy
			return 0;//Return 0 which indicates as false
		}
		n0=rmchr(n0,'.',1);//Remove the '.' from the string
	}
	if(isWhole(n0)){//(The remaining characters of the string are only digits after removing '-' & '.')
		free(n0);//Free the copy
		return 1;//Return 1 which indicates as true
	}
	free(n0);//Free the copy
	return 0;//Return 0 which indicates as false (because the condition above was false)
}
char* fixnum(char* n,char release){//Assign a function which turns the numbers in their standard form in form of string
	if(strlen(n)<2)//(The string only contains 1 character, so it's definitely in the standard form)
		return strtmp(n,release);//Return a copy of the string and free the original one if told to
	char sign=(n[0]=='-'?'-':0),*n0=absstr(n,release);//Save the sign of the number and turn the number into its absolute form
	while(strlen(n0)-(strchr(n0,'.')?strlen(strchr(n0,'.')):0)>1&&n0[0]=='0')//Remove the zeros from the left
		n0=strnrtmp(n0,strlen(n0)-1,1);
	if(strchr(n0,'.')){//(The number has a floating point)
		while(n0[strlen(n0)-1]=='0'||n0[strlen(n0)-1]=='.')//Remove the zeros from the right
			n0=strntmp(n0,strlen(n0)-1,1);
	}
	return n0[0]<'1'&&strlen(n0)<2?strtmp("0",0):strappend(CHR2STR(sign),n0,1);//Return the result, or if the result is "0", return a copy of "0" (so it wouldn't return "-0")
}
void swapstr(char** a,char** b){//Assign a function which swaps 2 strings allocated in the heap
	char *tmp=strtmp(*a,1);//Create a copy of the first string
	*a=strtmp(*b,1),*b=strtmp(tmp,1);//Swap values and free the copy after it
	return;
}
char* returnPoint(char* n,size_t posFromRight,char release){//Assign a function which returns the '.' to an integer string
	if(!posFromRight)//Cancel the purpose of the function if `posFromRight` is zero
		return strtmp(n,release);//Return a copy of the string and free the original one if told to
	char *result=posFromRight<strlen(absstr(n,0))?"":"0",sign=n[0]=='-'?'-':0;//Assign variables
	for(size_t i=sign=='-';i<strlen(n);result=strappend(result,i==strlen(n)-posFromRight?strappend(".",CHR2STR(n[i]),0):CHR2STR(n[i]),0),i++);//Return the '.' to the whole number
	if(release)//Free the string if told to
		free(n);
	return fixnum(strappend(CHR2STR(sign),result,1),1);//Put the sign at the back of the result and return it
}
void removeDecimals(char** x,char** y){//Assign a function which removes the '.' from 2 string numbers by multiplying them by 10
	if(strchr(*x,'.')&&!strchr(*y,'.'))//(The first string has '.' while the second string hasn't)
		*y=fixnum(mltstr(*y,"0",strlen(strchr(*x,'.'))-1,2),1),*x=fixnum(rmchr(*x,'.',1),1);
	else if(!strchr(*x,'.')&&strchr(*y,'.'))//(The second string has '.' while the first string hasn't)
		*x=fixnum(mltstr(*x,"0",strlen(strchr(*y,'.'))-1,2),1),*y=fixnum(rmchr(*y,'.',1),1);
	else if(strchr(*x,'.')&&strchr(*y,'.')){//(Both strings have '.')
		char swap=0;//Assign a variable which checks if the strings have been swapped
		if(strlen(strchr(*x,'.'))<strlen(strchr(*y,'.')))//Swap the strings if the second string has more decimals than the first one (and save it)
			swapstr(x,y),swap=1;
		*y=mltstr(mltstr(fixnum(rmchr(*y,'.',0),1),"0",strlen(strchr(*x,'.'))-strlen(strchr(*y,'.')),2),*y,0,3),*x=fixnum(rmchr(*x,'.',1),1);//Remove decimals
		if(swap)//Swap the strings back if they've been swapped before
			swapstr(x,y);
	}
	return;
}
char* addWhole(char* x,char* y,char release){//Assign a function which does addition to 2 whole number strings
	char *x0=strtmp(x,release&2),*y0=strtmp(y,release&1),*answer=strtmp("",0),add=0;//Create copies of both strings (and freeing the original ones if told to) and assign the answer string
	if(strlen(x0)<strlen(y0))//Swap the copies if the second string has more characters than the first one
		swapstr(&x0,&y0);
	for(size_t i=strlen(x0);i--;)//Do the addition digit by digit
		if(i<strlen(x0)-strlen(y0))
			answer=strappend(CHR2STR((x0[i]-'0'+add)%10+'0'),answer,1),add=(x0[i]-'0'+add)/10;
		else
			answer=strappend(CHR2STR((x0[i]+y0[i-(strlen(x0)-strlen(y0))]-2*'0'+add)%10+'0'),answer,1),add=(x0[i]+y0[i-(strlen(x0)-strlen(y0))]-2*'0'+add)/10;
	free(x0),free(y0);//Free the copies
	return strappend(add?"1":"",answer,1);//Return the result
}
char cmpstr(char* a,char *b){//Assign a function which compares 2 strings by their value (Same as `strcmp` with some differences such as return type)
	if(strlen(a)>strlen(b))//(The length of the first string is more than the second string)
		return 1;//Return 1 indicating that the first string is bigger
	if(strlen(a)<strlen(b))//(The length of the first string is less than the second string)
		return 2;//Return 2 indicating that the second string is bigger
	for(size_t i=0;i<strlen(a);i++)//Compare both strings'content values if they have the same length
		if(a[i]>b[i])//(The character of the current index of the first string is bigger than the character of the current index of the second string)
			return 1;//Return 1 indicating that the first string is bigger
		else if(a[i]<b[i])//(The character of the current index of the first string is smaller than the character of the current index of the second string)
			return 2;//Return 2 indicating that the second string is bigger
	return 0;//Return 0 indicating that both strings are equal
}
char* subtractWhole(char* x,char* y,char release){//Assign a function which does subtraction to 2 whole number strings
	if(!cmpstr(x,y)){//(Both numbers are equal)
		if(release&2)//Free the first string if told to
			free(x);
		if(release&1)//Free the second string if told to
			free(y);
		return strtmp("0",0);//Return a copy of "0"
	}
	char *x0=strtmp(x,release&2),*y0=strtmp(y,release&1),*answer=strtmp("",0),sign=cmpstr(x0,y0)>1?'-':0,subtract=0;//Assign copies of both strings, answer & sign character
	if(sign)//Swap if the second string is bigger than the first one
		swapstr(&x0,&y0);
	for(size_t i=strlen(x0);i--;)//Do the subtraction digit by digit
		if(i<strlen(x0)-strlen(y0))
			answer=strappend(CHR2STR(MOD10(x0[i]-'0'-subtract)+'0'),answer,1),subtract=x0[i]-'0'-subtract<0?1:0;
		else
			answer=strappend(CHR2STR(MOD10(x0[i]-y0[i-(strlen(x0)-strlen(y0))]-subtract)+'0'),answer,1),subtract=x0[i]-y0[i-(strlen(x0)-strlen(y0))]-subtract<0?1:0;
	free(x0),free(y0);//Free the copies
	return strappend(CHR2STR(sign),fixnum(answer,1),1);//Return the result with the sign back
}
char* simpleWholeDivide(char* x,char* y,char option,char release){//Assign a function which does division to 2 whole number strings in a simple way (useful if x/y<10)
	if(y[0]<'1'){//(The second string is "0")
		if(release&2)//Free the first string if told to
			free(x);
		if(release&1)//Free the second string if told to
			free(y);
		return 0;//Return NULL
	}
	if(y[0]=='1'&&strlen(y)<2){//(The second string is "1")
		if(release&1)//Free the second string if told to
			free(y);
		if(option){//(The function asked for the remainder)
			if(release&2)//Free the first string if told to
				free(x);
			return strtmp("0",0);//Return a copy of "0"
		}
		return strtmp(x,release&2);//Return a copy of the first string and free the original one if told to if the condition above was false
	}
	if(x[0]<'1'){//(The first string is "0")
		if(release&2)//Free the first string if told to
			free(x);
		if(release&1)//Free the second string if told to
			free(y);
		return strtmp("0",0);//Return a copy of "0"
	}
	if(option&&(y[0]=='2'||y[0]=='5')&&strlen(y)<2)//(The function asked for the remainder and the second string is either "2" or "5")
		return mltstr(mltstr(strtmp(CHR2STR((x[strlen(x)-1]-'0')%(y[0]-'0')+'0'),0),x,0,2+(release&2)),y,0,2+(release&1));//Return the remainder of the last digit of the first string divided by the second string and free both if told to
	if(option&&y[0]=='1'){//(The function asked for the remainder and the first digit of the second string is '1' (It is possible that the second string is a power of 10))
		char *tmp=fixnum(strchr(y,y[1]),0);//Fix the second string without the first digit and store the result in a temporary string
		if(tmp[0]<'1'){//(The second string is definitely a power of 10)
			free(tmp);//Free the temporary string
			return mltstr(strnrtmp(x,strlen(y)-1,release&2),y,0,2+(release&1));//Return a copy of the first string with a character limit of the number of '0's of the second string and free both strings if told to
		}
		free(tmp);//Free the temporary string
	}
	if(!cmpstr(x,y)){//(Both strings are equal)
		if(release&2)//Free the first string if told to
			free(x);
		if(release&1)//Free the second string if told to
			free(y);
		return option?strtmp("0",0):strtmp("1",0);//Return a copy of "0" if it asked for the remainder; unless, return a copy of "1"
	}
	if(cmpstr(x,y)>1){//(The second string is bigger than the first string
		if(release&1)//Free the second string if told to
			free(y);
		if(option)//(The function asked for the remainder)
			return strtmp(x,release&2);
		if(release&2)//Free the first string if told to
			free(x);
		return strtmp("0",0);//Return a copy of "0"
	}
	char *answer0=strtmp("0",0),*answer1=strtmp(x,release&2);//Assign the answer & the remainder string
	while(cmpstr(answer1,y)<2)//Continue addition 1 to the answer and subtracting the second string from the remainder until the remainder is smaller than the second string
		answer0=addWhole(answer0,"1",2),answer1=subtractWhole(answer1,y,2);
	if(release&1)//Free the second string if told to
		free(y);
	if(option){//Return the remainder if the function asked for the remainder
		free(answer0);//Free the answer string
		return answer1;//Return the remainder
	}
	free(answer1);//Free the remainder string
	return answer0;//Return the answer
}
char* divideWhole(char* x,char* y,char option,char release){//(Same as the function above with speed improvements (Uses the function above))
	if(y[0]<'1'){//(The second string is "0")
		if(release&2)//Free the first string if told to
			free(x);
		if(release&1)//Free the second string if told to
			free(y);
		return 0;//Return NULL
	}
	if(y[0]=='1'&&strlen(y)<2){//(The second string is "1")
		if(release&1)//Free the second string if told to
			free(y);
		if(option){//(The function asked for the remainder)
			if(release&2)//Free the first string if told to
				free(x);
			return strtmp("0",0);//Return a copy of "0"
		}
		return strtmp(x,release&2);//Return a copy of the first string and free the original one if told to if the condition above was false
	}
	if(x[0]<'1'){//(The first string is "0")
		if(release&2)//Free the first string if told to
			free(x);
		if(release&1)//Free the second string if told to
			free(y);
		return strtmp("0",0);//Return a copy of "0"
	}
	if(option&&(y[0]=='2'||y[0]=='5')&&strlen(y)<2)//(The function asked for the remainder and the second string is either "2" or "5")
		return mltstr(mltstr(strtmp(CHR2STR((x[strlen(x)-1]-'0')%(y[0]-'0')+'0'),0),x,0,2+(release&2)),y,0,2+(release&1));//Return the remainder of the last digit of the first string divided by the second string and free both if told to
	if(option&&y[0]=='1'){//(The function asked for the remainder and the first digit of the second string is '1' (It is possible that the second string is a power of 10))
		char *tmp=fixnum(strchr(y,y[1]),0);//Fix the second string without the first digit and store the result in a temporary string
		if(tmp[0]<'1'){//(The second string is definitely a power of 10)
			free(tmp);//Free the temporary string
			return mltstr(strnrtmp(x,strlen(y)-1,release&2),y,0,2+(release&1));//Return a copy of the first string with a character limit of the number of '0's of the second string and free both strings if told to
		}
		free(tmp);//Free the temporary string
	}
	if(!cmpstr(x,y)){//(Both strings are equal)
		if(release&2)//Free the first string if told to
			free(x);
		if(release&1)//Free the second string if told to
			free(y);
		return option?strtmp("0",0):strtmp("1",0);//Return a copy of "0" if it asked for the remainder; unless, return a copy of "1"
	}
	if(cmpstr(x,y)>1){//(The second string is bigger than the first string
		if(release&1)//Free the second string if told to
			free(y);
		if(option)//(The function asked for the remainder)
			return strtmp(x,release&2);
		if(release&2)//Free the first string if told to
			free(x);
		return strtmp("0",0);//Return a copy of "0"
	}
	char *answer0=strtmp("",0),*answer1=strtmp(CHR2STR(x[0]),0);//Assign the answer & the remainder string
	for(size_t i=strlen(x);i--;answer0=strappend(answer0,simpleWholeDivide(answer1,y,0,0),3),answer1=fixnum(strappend(simpleWholeDivide(answer1,y,1,2),CHR2STR(i?x[strlen(x)-i]:0),2),1));//Do the division digit by digit
	if(release&2)//Free the first string if told to
		free(x);
	if(release&1)//Free the second string if told to
		free(y);
	if(option){//Return the remainder if the function asked for the remainder
		free(answer0);//Free the answer string
		return answer1;//Return the remainder
	}
	free(answer1);//Free the remainder string
	return fixnum(answer0,1);//Return the answer
}
char* gcd(char* x,char* y,char release){//Assign a function which returns the greatest common divisor of 2 whole numbers as strings using the Euclidean algorithm
	if(x[0]<'1'||y[0]<'1'){//(Either the first or the second string is "0")
		if(release&2)//Free the first string if told to
			free(x);
		if(release&1)//Free the second string if told to
			free(y);
		return 0;//Return NULL
	}
	if(!cmpstr(x,y)){//(Both the first & the second strings are equal)
		if(release&1)//Free the second string if told to
			free(y);
		return strtmp(x,release&2);//Return a copy of the first string and free the original one if told to
	}
	char *x0=strtmp(x,release&2),*y0=strtmp(y,release&1),*tmp;//Assign a copy of both strings and free the original ones if told to, and assign a temporary string
	while(x0[strlen(x0)-1]<'1'&&y0[strlen(y0)-1]<'1')//Divide both copies by 10 until one of them is not divisable by 10
		x0=strntmp(x0,strlen(x0)-1,1),y0=strntmp(y0,strlen(y0)-1,1);
	while(x0[0]>'0'&&y0[0]>'0')//Continue finding remainders of both copies until one of them becomes "0"
		tmp=divideWhole(x0,y0,1,0),y0=divideWhole(y0,x0,1,3),x0=strtmp(tmp,1);
	if(cmpstr(x0,y0)>1){//(The second copy is not 0)
		free(x0);//Free the first copy
		return y0;//Return the second copy
	}
	free(y0);//Free the second copy
	return x0;//Return the first copy
}
char* calculate(char* x,char* y,char operation,char release){//Assign the main function which calculates strings by the main programming operators as if they were numbers
	char *x0=strtmp(x,release&2),*y0=strtmp(y,release&1),*answer=strtmp(operation=='*'?"0":operation=='/'?(x0[0]=='-')^(y0[0]=='-')?"-":"":0,0);//Assign a copy of both strings and free them if told to, and the answer
	size_t divide=operation=='+'||operation=='-'||operation=='*'||operation=='%'?!strchr(x0,'.')&&!strchr(y0,'.')?0:strchr(x0,'.')&&!strchr(y0,'.')?strlen(strchr(x0,'.'))-1:!strchr(x0,'.')&&strchr(y0,'.')?strlen(strchr(y0,'.'))-1:operation=='*'?strlen(strchr(x0,'.'))+strlen(strchr(y0,'.'))-2:strlen(strchr(x0,'.'))>strlen(strchr(y0,'.'))?strlen(strchr(x0,'.'))-1:strlen(strchr(y0,'.'))-1:0;//Assign the number used for division (useless if `operation` (The operator) is '/')
	switch(operation){//Check the operator
		case '+'://Do the addition
			removeDecimals(&x0,&y0);//Remove the floating point from both strings
			if(x0[0]=='-'&&y0[0]!='-')//(The first string is negative, and the second string isn't)
				answer=subtractWhole(strtmp(y0,1),absstr(x0,1),3);//Subtract the strings by their absolute value
			else if(x0[0]!='-'&&y0[0]=='-')//(The first string is negative, and the second string isn't)
				answer=subtractWhole(strtmp(x0,1),absstr(y0,1),3);//Subtract the strings by their absolute value
			else//(Both strings are either negative or non-negative)
				answer=strappend(x0[0]=='-'?"-":"",addWhole(absstr(x0,1),absstr(y0,1),3),1);//Do the addition with the strings' absolute values, and put the sign if both are negative
			return returnPoint(answer,divide,1);//Return the result with the floating point back
		case '-'://Do the subtraction
			removeDecimals(&x0,&y0);//Remove the floating point from both strings
			if((x0[0]=='-')^(y0[0]=='-'))//(Only one of the strings is negative)
				answer=strappend(x0[0]=='-'?"-":"",addWhole(absstr(x0,0),absstr(y0,1),3),1),free(x0);//Do the addition with the strings' absolute values plus the '-' if the first string is negative
			else//(Both strings are either negative or non-negative)
				answer=strappend(x0[0]=='-'?"-":"",subtractWhole(absstr(x0,0),absstr(y0,1),3),1),free(x0),answer=answer[1]=='-'?strchr(answer,answer[2]):answer;//Subtract the strings by their absolute value, and if the answer has 2 '-', remove both of them
			return returnPoint(answer,divide,1);//Return the result with the floating point back
		case '*'://Do the multiplication
			char *answer0=strtmp("",0),add0=0,add1=0,sign=(x0[0]=='-')^(y0[0]=='-')?'-':0;//Assign the answer, the first addition variable, a the second addition variable & the sign character
			x0=fixnum(rmchr(absstr(x0,1),'.',1),1),y0=fixnum(rmchr(absstr(y0,1),'.',1),1);//Turn the number strings into whole number strings
			for(size_t i=strlen(x0);i--;answer=addWhole(answer,strappend(add0?CHR2STR(add0+'0'):"",answer0,1),3),add0=0,answer0=mltstr("","0",strlen(x0)-i,0))//Do the multiplication digit by digit
				for(size_t j=strlen(y0);j--;answer0=strappend(CHR2STR((add0+add1)%10+'0'),answer0,1),add0=(add0+add1)/10,add1=0)
					for(char k=x0[i]-'0';k--;add1+=y0[j]-'0');
			free(x0),free(y0);//Free both copies
			return returnPoint(strappend(mltstr(CHR2STR(sign),"0",divide,0),answer,3),divide,1);//Return the result with the floating point & the sign back
		case '%'://Find the remainder of a division
			if(y0[0]<'1'&&strlen(y0)<2)//(The second string is "0")
				break;//Break out of the switch-case statement
			removeDecimals(&x0,&y0),answer=returnPoint(strappend((x0[0]=='-')^(y0[0]=='-')?"-":"",divideWhole(absstr(x0,0),absstr(y0,0),1,3),1),divide,1),free(x0),free(y0);//Turn the number strings into whole number strings, and find the answer with the floating point back
			return answer;//Return the result
		case '/'://Do the division
			if(y0[0]<'1'&&strlen(y0)<2)//(The second string is "0")
				break;//Break out of the switch-case statement
			if(x0[0]<'1'&&strlen(x0)<2){//(The first string is "0")
				free(x0),free(y0),free(answer);//Free every array allocated in the heap
				return strtmp("0",0);//Return a copy of "0"
			}
			if(!cmpstr(x0,y0)){//(Both strings are equal)
				free(x0),free(y0),free(answer);//Free every array allocated in the heap
				return strtmp("1",0);//Return a copy of "1"
			}
			removeDecimals(&x0,&y0),x0=absstr(x0,1),y0=absstr(y0,1);//Remove the floating point from both strings, and turn them into their absolute value
			{//(For local usage)
				char *divide=gcd(x0,y0,0);//Assign the greatest common divisor of both strings
				x0=divideWhole(x0,divide,0,2),y0=divideWhole(y0,divide,0,3);//Simplify the division by dividing both strings by their greatest common divisor
			}
			answer=strappend(answer,divideWhole(x0,y0,0,0),3),x0=divideWhole(x0,y0,1,2);//Append the whole division answer into the answer string and store its remainder in the first string
			if(x0[0]>'0'){//(The remainder isn't "0")
				answer=strappend(answer,".",2);//Add the '.' to the answer string
				char *tmp=strtmp(y0,0);//Create a copy of the second string (for the terminating decimal part)
				for(;tmp[strlen(tmp)-1]<'1';tmp=strntmp(tmp,strlen(tmp)-1,1),x0=strappend(x0,"0",2),answer=strappend(answer,simpleWholeDivide(x0,y0,0,0),3),x0=simpleWholeDivide(x0,y0,1,2))//Continue the division digit by digit and divide the copy by 10 until it's not divisibla by 10
					if(x0[0]<'1'){//(In case that the remainder becomes 0)
						free(tmp);//Free the copy
						goto finish;//Break out of the condition
					}
				if(tmp[strlen(tmp)-1]=='5'){//(The copy is still divisible by 5)
					for(;tmp[strlen(tmp)-1]=='5';tmp=divideWhole(tmp,"5",0,2),x0=strappend(x0,"0",2),answer=strappend(answer,simpleWholeDivide(x0,y0,0,0),3),x0=simpleWholeDivide(x0,y0,1,2))//Continue the division digit by digit and divide the copy by 5 until it's not divisibla by 5
						if(x0[0]<'1'){//(In case that the remainder becomes 0)
							free(tmp);//Free the copy
							goto finish;//Break out of the condition
						}
				}else//(The division isn't divisible by 5)
					for(;(tmp[strlen(tmp)-1]-'0')%2<1;tmp=divideWhole(tmp,"2",0,2),x0=strappend(x0,"0",2),answer=strappend(answer,simpleWholeDivide(x0,y0,0,0),3),x0=simpleWholeDivide(x0,y0,1,2))//Continue the division digit by digit and divide the copy by 2 until it's not divisibla by 2
						if(x0[0]<'1'){//(In case that the remainder becomes 0)
							free(tmp);//Free the copy
							goto finish;//Break out of the condition
						}
				if(tmp[0]=='1'&&strlen(tmp)<2){//(The answer has no repeating decimals)
					free(tmp);//Free the copy
					goto finish;//Break out of the condition
				}
				for(free(tmp),tmp=strtmp(x0,0),x0=strappend(x0,"0",2),answer=strappend(answer,strappend("(",simpleWholeDivide(x0,y0,0,0),1),3),x0=simpleWholeDivide(x0,y0,1,2);cmpstr(x0,tmp);x0=strappend(x0,"0",2),answer=strappend(answer,simpleWholeDivide(x0,y0,0,0),3),x0=simpleWholeDivide(x0,y0,1,2))//Continue the division digit by digit until the end of the repeating decimals has been found
					if(x0[0]<'1'){//(In case that the remainder becomes 0)
						free(tmp),answer=rmchr(answer,'(',1);//Free the copy, and remove the '(' from the answer string (because it's a terminating decimal)
						goto finish;//Break out of the condition
					}
				free(tmp),tmp=fixnum(strchr(strchr(answer,'('),strchr(answer,'(')[1]),0),answer=tmp[0]>'0'?strappend(answer,")",2):fixnum(rmchr(answer,'(',1),1),free(tmp);//Free the copy, and finalize the answer string
			}
			finish:
			free(x0),free(y0);//Free both strings
			return answer;//Return the answer
	}
	free(x0),free(y0),free(answer);//Free every array which was allocated in the heap
	return 0;//Return NULL (because the division was dividing by 0 which is undefined)
}
#endif
