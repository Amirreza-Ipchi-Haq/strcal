#ifndef _CSTRCAL_H_
#define _CSTRCAL_H_
#include"dynastr.h"
char strcal_isWhole(const char* n){//Assign a function which checks if a string only contains digits
	if(!n||!strlen(n))//Return 0 which indicates as false if the string is NULL or the string length is 0
		return 0;
	for(size_t i=strlen(n);i--;)//Check every index
		if(n[i]<'0'||n[i]>'9')//(The current index contains something other than digits)
			return 0;//Return 0 which indicates as false
	return 1;//Return 1 which indicates as true
}
char* strcal_absstr(char* n,const char release){//Assign a function which removes the first '-' if it exists from a string
	n=n[0]=='-'?dynastr_strnrtmp(n,strlen(n)-1,release):dynastr_strtmp(n,release);//Create a copy of the original string without the first '-' if it exists
	return n;//Return the result
}
char strcal_isnum(char* n){//Assign a function which checks if a string represents a number (standard (like 1) or non-standard (like 01.0))
	if(!n)//Return 0 which indicates as false if the string is NULL
		return 0;
	if(strlen(n)<2)//Check the number string if it only contains 1 character
		return strcal_isWhole(n);//Return the result
	unsigned char isNegative=n[0]=='-';//Assign the negativity indicator
	if(((n[(size_t)isNegative]<'0'||n[(size_t)isNegative]>'9')&&n[(size_t)isNegative]!='.')||n[strlen(n)-1]<'0'||n[strlen(n)-1]>'9')//Return 0 which indicates as false if the string doesn't represent a number (Check the beginning & the end)
		return 0;
	char reachedPoint=0;//Assign the point indicator
	for(size_t i=strlen(n)-1;--i>isNegative;)//Check every digit
		if(n[i]=='.'){//(Reached the point)
			if(reachedPoint)//Return 0 which indicates as false if a point was already found
				return 0;
			reachedPoint=1;//Change the point indicator
		}else if(n[i]<'0'||n[i]>'9')//Return 0 which indicates as false if the current character isn't valid
			return 0;
	return 1;//Return 1 which indicates as true because the string represents a number
}
char* strcal_fixnum(char* n,const char release){//Assign a function which turns the numbers in their standard form in form of string
	if(strlen(n)<2)//(The string only contains 1 character, so it's definitely in the standard form)
		return dynastr_strtmp(n,release);//Return a copy of the string and free the original one if told to
	char sign=(n[0]=='-'?'-':0);
	n=strcal_absstr(n,release);//Save the sign of the number and turn the number into its absolute form
	if(n[0]=='.')
		n=dynastr_strappend("0",n,1);
	while(strlen(n)-(strchr(n,'.')?strlen(strchr(n,'.')):0)>1&&n[0]=='0')//Remove the zeros from the left
		n=dynastr_strnrtmp(n,strlen(n)-1,1);
	if(strchr(n,'.')){//(The number has a floating point)
		while(n[strlen(n)-1]=='0'||n[strlen(n)-1]=='.')//Remove the zeros from the right
			if(n[strlen(n)-1]=='.'){//Terminate removal if the last character is '.'
				n=dynastr_strntmp(n,strlen(n)-1,1);
				break;
			}else//Continue the removal
				n=dynastr_strntmp(n,strlen(n)-1,1);
	}
	return n[0]<'1'&&strlen(n)<2?dynastr_strtmp("0",0):dynastr_strappend(DYNASTR_CHR2STR(sign),n,1);//Return the result, or if the result is "0", return a copy of "0" (so it wouldn't return "-0")
}
char* strcal_returnPoint(char* n,const size_t posFromRight,const char release){//Assign a function which returns the '.' to an integer string
	if(!posFromRight)//Cancel the purpose of the function if `posFromRight` is zero
		return dynastr_strtmp(n,release);//Return a copy of the string and free the original one if told to
	char sign=n[0]=='-'?'-':0,*tmp=strcal_absstr(n,0),*result=posFromRight<strlen(tmp)?dynastr_strtmp("",0):dynastr_mltstr(sign=='-'?"0":"0.","0",posFromRight-strlen(tmp),0);//Assign variables
	free(tmp);//Free the temporary string
	for(size_t i=sign=='-';i<strlen(n);result=dynastr_strappend(result,strlen(n)>posFromRight&&i==strlen(n)-posFromRight?dynastr_strappend(".",DYNASTR_CHR2STR(n[i]),0):DYNASTR_CHR2STR(n[i]),2),i++);//Return the '.' to the whole number
	if(release)//Free the string if told to
		free(n);
	return strcal_fixnum(dynastr_strappend(DYNASTR_CHR2STR(sign),result,1),1);//Put the sign at the back of the result and return it
}
void strcal_removeDecimals(char** x,char** y){//Assign a function which removes the '.' from 2 string numbers by multiplying them by 10
	if(strchr(*x,'.')&&!strchr(*y,'.'))//(The first string has '.' while the second string hasn't)
		*y=strcal_fixnum(dynastr_mltstr(*y,"0",strlen(strchr(*x,'.'))-1,2),1),*x=strcal_fixnum(dynastr_rmchr(*x,'.',1),1);
	else if(!strchr(*x,'.')&&strchr(*y,'.'))//(The second string has '.' while the first string hasn't)
		*x=strcal_fixnum(dynastr_mltstr(*x,"0",strlen(strchr(*y,'.'))-1,2),1),*y=strcal_fixnum(dynastr_rmchr(*y,'.',1),1);
	else if(strchr(*x,'.')&&strchr(*y,'.')){//(Both strings have '.')
		const char swap=strlen(strchr(*x,'.'))<strlen(strchr(*y,'.'));//Assign a variable which checks if the strings needs to be swapped
		if(swap)//Swap the strings if the second string has more decimals than the first one (and save it)
			dynastr_swapstr(x,y);
		*y=dynastr_mltstr(dynastr_mltstr(strcal_fixnum(dynastr_rmchr(*y,'.',0),1),"0",strlen(strchr(*x,'.'))-strlen(strchr(*y,'.')),2),*y,0,3),*x=strcal_fixnum(dynastr_rmchr(*x,'.',1),1);//Remove decimals
		if(swap)//Swap the strings back if they've been swapped before
			dynastr_swapstr(x,y);
	}
	return;
}
char* strcal_addWhole(char* x,char* y,const char release){//Assign a function which does addition to 2 whole number strings
	if(x[0]=='0'){//(The first string is "0")
		if(release&2)//Free the first string if told to
			free(x);
		return dynastr_strtmp(y,release&1);//Return a copy of the second string and free the original one if told to
	}
	if(y[0]=='0'){//(The second string is "0")
		if(release&1)//Free the second string if told to
			free(y);
		return dynastr_strtmp(x,release&2);//Return a copy of the first string and free the original one if told to
	}
	x=dynastr_strtmp(x,release&2),y=dynastr_strtmp(y,release&1);
	char *answer=dynastr_strtmp("",0),add=0;//Create copies of both strings (and freeing the original ones if told to) and assign the answer string
	if(strlen(x)<strlen(y))//Swap the copies if the second string has more characters than the first one
		dynastr_swapstr(&x,&y);
	for(size_t i=strlen(x);i--;)//Do the addition digit by digit
		if(i<strlen(x)-strlen(y))
			answer=dynastr_strappend(DYNASTR_CHR2STR((x[i]-'0'+add)%10+'0'),answer,1),add=(x[i]-'0'+add)/10;
		else
			answer=dynastr_strappend(DYNASTR_CHR2STR((x[i]+y[i-(strlen(x)-strlen(y))]-2*'0'+add)%10+'0'),answer,1),add=(x[i]+y[i-(strlen(x)-strlen(y))]-2*'0'+add)/10;
	free(x),free(y);//Free the copies
	return dynastr_strappend(add?"1":"",answer,1);//Return the result
}
char strcal_cmpstr(char* a,char *b){//Assign a function which compares 2 strings by their value (Same as `strcmp` with some differences such as return type)
	if(strlen(a)!=strlen(b))//(The strings' lengths differ from each other)
		return 1+(strlen(a)<strlen(b));//Return 1 if the first string is larger, unless, return 2
	for(size_t i=0;i<strlen(a);i++)//Compare both strings'content values if they have the same length
		if(a[i]!=b[i])//(The character of the current index differ)
			return 1+(a[i]<b[i]);//Return 1 if the current index character of the first string is bigger than the one in the second string, unless, return 2
	return 0;//Return 0 indicating that both strings are equal
}
char* strcal_subtractWhole(char* x,char* y,const char release){//Assign a function which does subtraction to 2 whole number strings
	if(y[0]=='0'){//(The second string is "0")
		if(release&1)//Free the second string if told to
			free(y);
		return dynastr_strtmp(x,release&2);//Return a copy of the first string and free the original one if told to
	}
	if(x[0]=='0'){//(The first string is "0")
		if(release&2)//Free the first string if told to
			free(x);
		return dynastr_strappend("-",y,release&1);//Return a copy of the second string with '-' at the left and free the original one if told to
	}
	if(!strcal_cmpstr(x,y)){//(Both numbers are equal)
		if(release&2)//Free the first string if told to
			free(x);
		if(release&1)//Free the second string if told to
			free(y);
		return dynastr_strtmp("0",0);//Return a copy of "0"
	}
	x=dynastr_strtmp(x,release&2),y=dynastr_strtmp(y,release&1);
	char *answer=dynastr_strtmp("",0),sign=strcal_cmpstr(x,y)>1?'-':0,subtract=0;//Assign copies of both strings, answer & sign character
	if(sign)//Swap if the second string is bigger than the first one
		dynastr_swapstr(&x,&y);
#define MOD10(n) (char)(n%10<0?10+n%10:n%10)//Assign a function which finds `n mod 10`
	for(size_t i=strlen(x);i--;)//Do the subtraction digit by digit
		if(i<strlen(x)-strlen(y))
			answer=dynastr_strappend(DYNASTR_CHR2STR(MOD10(x[i]-'0'-subtract)+'0'),answer,1),subtract=x[i]-'0'-subtract<0;
		else
			answer=dynastr_strappend(DYNASTR_CHR2STR(MOD10(x[i]-y[i-(strlen(x)-strlen(y))]-subtract)+'0'),answer,1),subtract=x[i]-y[i-(strlen(x)-strlen(y))]-subtract<0;
#undef MOD10
	free(x),free(y);//Free the copies
	return dynastr_strappend(DYNASTR_CHR2STR(sign),strcal_fixnum(answer,1),1);//Return the result with the sign back
}
char* strcal_simpleWholeDivide(char* x,char* y,const char option,const char release){//Assign a function which does division to 2 whole number strings in a simple way (useful if x/y<10)
	if(y[0]<'1'){//(The second string is "0")
		if(release&2)//Free the first string if told to
			free(x);
		if(release&1)//Free the second string if told to
			free(y);
		return NULL;//Return NULL
	}
	if(y[0]<'2'&&strlen(y)<2){//(The second string is "1")
		if(release&1)//Free the second string if told to
			free(y);
		if(option){//(The function asked for the remainder)
			if(release&2)//Free the first string if told to
				free(x);
			return dynastr_strtmp("0",0);//Return a copy of "0"
		}
		return dynastr_strtmp(x,release&2);//Return a copy of the first string and free the original one if told to if the condition above was false
	}
	if(x[0]<'1'){//(The first string is "0")
		if(release&2)//Free the first string if told to
			free(x);
		if(release&1)//Free the second string if told to
			free(y);
		return dynastr_strtmp("0",0);//Return a copy of "0"
	}
	if(option&&(y[0]=='2'||y[0]=='5')&&strlen(y)<2)//(The function asked for the remainder and the second string is either "2" or "5")
		return dynastr_mltstr(dynastr_mltstr(dynastr_strtmp(DYNASTR_CHR2STR((x[strlen(x)-1]-'0')%(y[0]-'0')+'0'),0),x,0,2+(release&2)),y,0,2+(release&1));//Return the remainder of the last digit of the first string divided by the second string and free both if told to
	if(option&&y[0]=='1'){//(The function asked for the remainder and the first digit of the second string is '1' (It is possible that the second string is a power of 10))
		char *tmp=strcal_fixnum(strchr(y,y[1]),0);//Fix the second string without the first digit and store the result in a temporary string
		if(tmp[0]<'1'){//(The second string is definitely a power of 10)
			free(tmp);//Free the temporary string
			return dynastr_mltstr(dynastr_strnrtmp(x,strlen(y)-1,release&2),y,0,2+(release&1));//Return a copy of the first string with a character limit of the number of '0's of the second string and free both strings if told to
		}
		free(tmp);//Free the temporary string
	}
	if(!strcal_cmpstr(x,y)){//(Both strings are equal)
		if(release&2)//Free the first string if told to
			free(x);
		if(release&1)//Free the second string if told to
			free(y);
		return option?dynastr_strtmp("0",0):dynastr_strtmp("1",0);//Return a copy of "0" if it asked for the remainder; unless, return a copy of "1"
	}
	if(strcal_cmpstr(x,y)>1){//(The second string is bigger than the first string
		if(release&1)//Free the second string if told to
			free(y);
		if(option)//(The function asked for the remainder)
			return dynastr_strtmp(x,release&2);
		if(release&2)//Free the first string if told to
			free(x);
		return dynastr_strtmp("0",0);//Return a copy of "0"
	}
	x=dynastr_strtmp(x,release&2);
	char *answer=dynastr_strtmp("0",0);//Assign the answer & the remainder string
	while(strcal_cmpstr(x,y)<2)//Continue addition 1 to the answer and subtracting the second string from the remainder until the remainder is smaller than the second string
		answer=strcal_addWhole(answer,"1",2),x=strcal_subtractWhole(x,y,2);
	if(release&1)//Free the second string if told to
		free(y);
	if(option){//Return the remainder if the function asked for the remainder
		free(answer);//Free the answer string
		return x;//Return the remainder
	}
	free(x);//Free the remainder string
	return answer;//Return the answer
}
char* strcal_divideWhole(char* x,char* y,const char option,const char release){//(Same as the function above with speed improvements (Uses the function above))
	if(y[0]<'1'){//(The second string is "0")
		if(release&2)//Free the first string if told to
			free(x);
		if(release&1)//Free the second string if told to
			free(y);
		return NULL;//Return NULL
	}
	if(y[0]<'2'&&strlen(y)<2){//(The second string is "1")
		if(release&1)//Free the second string if told to
			free(y);
		if(option){//(The function asked for the remainder)
			if(release&2)//Free the first string if told to
				free(x);
			return dynastr_strtmp("0",0);//Return a copy of "0"
		}
		return dynastr_strtmp(x,release&2);//Return a copy of the first string and free the original one if told to if the condition above was false
	}
	if(x[0]<'1'){//(The first string is "0")
		if(release&2)//Free the first string if told to
			free(x);
		if(release&1)//Free the second string if told to
			free(y);
		return dynastr_strtmp("0",0);//Return a copy of "0"
	}
	if(option&&(y[0]=='2'||y[0]=='5')&&strlen(y)<2)//(The function asked for the remainder and the second string is either "2" or "5")
		return dynastr_mltstr(dynastr_mltstr(dynastr_strtmp(DYNASTR_CHR2STR((x[strlen(x)-1]-'0')%(y[0]-'0')+'0'),0),x,0,2+(release&2)),y,0,2+(release&1));//Return the remainder of the last digit of the first string divided by the second string and free both if told to
	if(option&&y[0]=='1'){//(The function asked for the remainder and the first digit of the second string is '1' (It is possible that the second string is a power of 10))
		char *tmp=strcal_fixnum(strchr(y,y[1]),0);//Fix the second string without the first digit and store the result in a temporary string
		if(tmp[0]<'1'){//(The second string is definitely a power of 10)
			free(tmp);//Free the temporary string
			return dynastr_mltstr(dynastr_strnrtmp(x,strlen(y)-1,release&2),y,0,2+(release&1));//Return a copy of the first string with a character limit of the number of '0's of the second string and free both strings if told to
		}
		free(tmp);//Free the temporary string
	}
	if(!strcal_cmpstr(x,y)){//(Both strings are equal)
		if(release&2)//Free the first string if told to
			free(x);
		if(release&1)//Free the second string if told to
			free(y);
		return option?dynastr_strtmp("0",0):dynastr_strtmp("1",0);//Return a copy of "0" if it asked for the remainder; unless, return a copy of "1"
	}
	if(strcal_cmpstr(x,y)>1){//(The second string is bigger than the first string
		if(release&1)//Free the second string if told to
			free(y);
		if(option)//(The function asked for the remainder)
			return dynastr_strtmp(x,release&2);
		if(release&2)//Free the first string if told to
			free(x);
		return dynastr_strtmp("0",0);//Return a copy of "0"
	}
	char *answer0=dynastr_strtmp("",0),*answer1=dynastr_strtmp(DYNASTR_CHR2STR(x[0]),0);//Assign the answer & the remainder string
	for(size_t i=strlen(x);i--;answer0=dynastr_strappend(answer0,strcal_simpleWholeDivide(answer1,y,0,0),3),answer1=strcal_fixnum(dynastr_strappend(strcal_simpleWholeDivide(answer1,y,1,2),DYNASTR_CHR2STR(i?x[strlen(x)-i]:0),2),1));//Do the division digit by digit
	if(release&2)//Free the first string if told to
		free(x);
	if(release&1)//Free the second string if told to
		free(y);
	if(option){//Return the remainder if the function asked for the remainder
		free(answer0);//Free the answer string
		return answer1;//Return the remainder
	}
	free(answer1);//Free the remainder string
	return strcal_fixnum(answer0,1);//Return the answer
}
char* strcal_gcd(char* x,char* y,const char release){//Assign a function which returns the greatest common divisor of 2 whole numbers as strings using the Euclidean algorithm
	if(x[0]<'1'||y[0]<'1'){//(Either the first or the second string is "0")
		if(release&2)//Free the first string if told to
			free(x);
		if(release&1)//Free the second string if told to
			free(y);
		return NULL;//Return NULL
	}
	if(!strcal_cmpstr(x,y)){//(Both the first & the second strings are equal)
		if(release&1)//Free the second string if told to
			free(y);
		return dynastr_strtmp(x,release&2);//Return a copy of the first string and free the original one if told to
	}
	x=dynastr_strtmp(x,release&2),y=dynastr_strtmp(y,release&1);
	char *tmp;//Assign a copy of both strings and free the original ones if told to, and assign a temporary string
	while(x[0]>'0'&&y[0]>'0')//Continue finding remainders of both copies until one of them becomes "0"
		tmp=strcal_divideWhole(x,y,1,0),y=strcal_divideWhole(y,x,1,3),x=tmp;
	if(strcal_cmpstr(x,y)>1){//(The second copy is not 0)
		free(x);//Free the first copy
		return y;//Return the second copy
	}
	free(y);//Free the second copy
	return x;//Return the first copy
}
char strcal_isrnum(char* n){//Assign a function same as `isnum` with recursive number support
	if(!n)//Return 0 which indicates as false if the string is NULL
		return 0;
	if(strlen(n)<2)//Check if the string represents a whole number if it contains less than 2 characters
		return strcal_isWhole(n);
	if(((!strchr(n,'('))^(n[strlen(n)-1]!=')'))||strchr(n,'(')!=strrchr(n,'(')||strchr(n,')')!=strrchr(n,')'))//Return 0 which indicates as false if the string has a bracket with no matching pair or there are more than 2 brackets
		return 0;
	if(!strchr(n,'('))//Check the number string as a terminating one if it has no brackets
		return strcal_isnum(n);
	if(!strchr(n,'.')||strlen(strchr(n,'('))>strlen(strchr(n,'.')))//Return 0 which indicates as false if the bracket position is invalid
		return 0;
	char *n0=dynastr_strnrtmp(n,strlen(strchr(n,'('))-1,0);//Assign a string which only stores the recursive part of the number string
	n0=dynastr_strntmp(n0,strlen(n0)-1,1);//Remove the extra ')'
	if(!strcal_isWhole(n0)){//(The recursive part is invalid)
		free(n0);//Free the string
		return 0;//Return 0 which indicates as false
	}
	free(n0),n0=dynastr_rmchr(dynastr_rmchr(n,'(',0),')',1);//Free the string and assign it with the number string without brackets
	if(strcal_isnum(n0)){//(The number string is valid itself)
		free(n0);//Free the string
		return 1;//Return 1 which indicates as true
	}
	free(n0);//Free the string
	return 0;//Return 0 which indicates as false if the number string is invalid itself
}
char* strcal_fixrnum(char* n,const char release){//Assign a function same as `fixnum` with recursive number support
	if(!strchr(n,'('))//Check the number string as a terminating one if it contains no brackets
		return strcal_fixnum(n,release);
	char sign=n[0]=='-'?'-':0,*n0=dynastr_strnrtmp(n,strlen(strchr(n,'('))-1,0),*n1=dynastr_strntmp(n,strlen(n)-strlen(n0)-1,release);//Assign the sign indicator, the recursive part & the terminating part
	n0=dynastr_strntmp(n0,strlen(n0)-1,1),n1=strcal_absstr(n1,1);//Remove the extra ')' from the recursive part and remove the sign from the terminating part if it exists
	if(n1[0]=='.')
		n1=dynastr_strappend("0",n1,1);
	while(strlen(n1)-(strchr(n1,'.')?strlen(strchr(n1,'.')):0)>1&&n1[0]=='0')//Remove the zeros from the left of the terminating part
		n1=dynastr_strnrtmp(n1,strlen(n1)-1,1);
	{//Check if the recursive part only contains '0' or '9' or none in a temporary scope
		char isZero=1,isNine=1;//Assign the boolean variables
		for(size_t i=strlen(n0);(isZero||isNine)&&i--;isZero*=n0[i]=='0',isNine*=n0[i]=='9');//Check the digits
		if(isZero){//(The recursive part only contains '0')
			free(n0);//Free the recursive part
			return strcal_fixnum(dynastr_strappend(DYNASTR_CHR2STR(sign),n1[strlen(n1)-1]=='.'?dynastr_strntmp(n1,strlen(n1)-1,1):n1,1),1);//Standardize the terminating part and return it
		}
		if(isNine){//(The recursive part only contains '9')
			free(n0);//Free the recursive part
			size_t point=strlen(strchr(n1,'.'))-1;//Assign a floating point variable (Not to be mistaken with the data type)
			return dynastr_strappend(DYNASTR_CHR2STR(sign),strcal_returnPoint(strcal_addWhole(strcal_fixnum(dynastr_rmchr(n1,'.',1),1),"1",2),point,1),1);//Return the actual answer
		}
	}
	for(char modify=1,*n2,*n3;modify&&strlen(n0)>1;)//Shorten the repeating part
		for(size_t len=strlen(n0)/2;len;len--){
			if(strlen(n0)%len)
				continue;
			n2=dynastr_strntmp(n0,len,0),n3=dynastr_strnrtmp(n0,len,0),modify=!strcal_cmpstr(n2,n3);
			for(size_t i=strlen(n0)/len-1;modify&&--i;free(n3),n3=dynastr_strnrtmp(dynastr_strntmp(n0,len*i,0),len,1),modify=!strcal_cmpstr(n2,n3));
			free(n2),free(n3);
			if(modify){
				n0=dynastr_strntmp(n0,len,1);
				break;
			}
		}
	while(n0[strlen(n0)-1]==n1[strlen(n1)-1])//Shorten the number string by checking the last index of both the terminating part and the repeating part
		n0=dynastr_mltstr(dynastr_strappend(DYNASTR_CHR2STR(n0[strlen(n0)-1]),dynastr_strntmp(n0,strlen(n0)-1,0),1),n0,0,3),n1=dynastr_strntmp(n1,strlen(n1)-1,1);	
	return dynastr_strappend(DYNASTR_CHR2STR(sign),dynastr_strappend(dynastr_strappend(dynastr_strappend(n1,"(",2),n0,3),")",2),1);//Return the result
}
char* strcal_calculate(char* x,char* y,const char operation,const char release){//Assign the main function which calculates strings by the main programming operators as if they were numbers
	x=dynastr_strtmp(x,release&2),y=dynastr_strtmp(y,release&1);
	char *answer=dynastr_strtmp(operation=='*'?"0":operation=='/'?(x[0]=='-')^(y[0]=='-')?"-":"":0,0);//Assign a copy of both strings and free them if told to, and the answer
	const size_t divide=operation=='+'||operation=='-'||operation=='*'||operation=='%'?!strchr(x,'.')&&!strchr(y,'.')?0:strchr(x,'.')&&!strchr(y,'.')?strlen(strchr(x,'.'))-1:!strchr(x,'.')&&strchr(y,'.')?strlen(strchr(y,'.'))-1:operation=='*'?strlen(strchr(x,'.'))+strlen(strchr(y,'.'))-2:strlen(strchr(x,'.'))>strlen(strchr(y,'.'))?strlen(strchr(x,'.'))-1:strlen(strchr(y,'.'))-1:0;//Assign the number used for division (useless if `operation` (The operator) is '/')
	switch(operation){//Check the operator
		case '+'://Do the addition
			strcal_removeDecimals(&x,&y);//Remove the floating point from both strings
			if(x[0]=='-'&&y[0]!='-')//(The first string is negative, and the second string isn't)
				answer=strcal_subtractWhole(y,strcal_absstr(x,1),3);//Subtract the strings by their absolute value
			else if(x[0]!='-'&&y[0]=='-')//(The first string is negative, and the second string isn't)
				answer=strcal_subtractWhole(x,strcal_absstr(y,1),3);//Subtract the strings by their absolute value
			else//(Both strings are either negative or non-negative)
				answer=dynastr_strappend(x[0]=='-'?"-":"",strcal_addWhole(strcal_absstr(x,0),strcal_absstr(y,1),3),1),free(x);//Do the addition with the strings' absolute values, and put the sign if both are negative
			return strcal_returnPoint(answer,divide,1);//Return the result with the floating point back
		case '-'://Do the subtraction
			strcal_removeDecimals(&x,&y);//Remove the floating point from both strings
			if((x[0]=='-')^(y[0]=='-'))//(Only one of the strings is negative)
				answer=dynastr_strappend(x[0]=='-'?"-":"",strcal_addWhole(strcal_absstr(x,0),strcal_absstr(y,1),3),1),free(x);//Do the addition with the strings' absolute values plus the '-' if the first string is negative
			else//(Both strings are either negative or non-negative)
				answer=dynastr_strappend(x[0]=='-'?"-":"",strcal_subtractWhole(strcal_absstr(x,0),strcal_absstr(y,1),3),1),free(x),answer=answer[1]=='-'?dynastr_strnrtmp(answer,strlen(answer)-2,1):answer;//Subtract the strings by their absolute value, and if the answer has 2 '-', remove both of them
			return strcal_returnPoint(answer,divide,1);//Return the result with the floating point back
		case '*'://Do the multiplication
			if((x[0]=='0'&&strlen(x)<2)||(y[0]=='0'&&strlen(y)<2)){//(One of the strings is "0")
				free(x),free(y),free(answer);//Free every string
				return dynastr_strtmp("0",0);//Return a copy of "0"
			}
			if((x[0]=='1'&&strlen(x)<2)||(y[0]=='1'&&strlen(y)<2)){//(One of the strings is "1")
				free(answer);//Free the answer string
				if(x[0]=='1'&&strlen(x)<2){//(The first string is "1" (This doesn't say the other one isn't))
					free(x);//Free the first string
					return dynastr_strtmp(y,1);//Return a copy of the second string and free the original one
				}//(The first string isn't "1" but the second string is)
				free(y);//Free the second string
				return dynastr_strtmp(x,1);//Return a copy of the first string and free the original one
			}
			char *answer0=dynastr_strtmp("",0),add0=0,add1,sign=(x[0]=='-')^(y[0]=='-')?'-':0;//Assign the sub-answer, the first addition variable, a the second addition variable & the sign character
			x=strcal_fixnum(dynastr_rmchr(strcal_absstr(x,1),'.',1),1),y=strcal_fixnum(dynastr_rmchr(strcal_absstr(y,1),'.',1),1);//Turn the number strings into whole number strings
			for(size_t i=strlen(x);i--;answer=strcal_addWhole(answer,dynastr_strappend(add0?DYNASTR_CHR2STR(add0+'0'):"",answer0,1),3),add0=0,answer0=dynastr_mltstr("","0",strlen(x)-i,0))//Do the multiplication digit by digit
				for(size_t j=strlen(y);j--;add1=(x[i]-'0')*(y[j]-'0'),answer0=dynastr_strappend(DYNASTR_CHR2STR((add0+add1)%10+'0'),answer0,1),add0=(add0+add1)/10);
			free(x),free(y),free(answer0);//Free both copies and the sub-answer
			return strcal_returnPoint(dynastr_strappend(dynastr_mltstr(DYNASTR_CHR2STR(sign),"0",divide,0),answer,3),divide,1);//Return the result with the floating point & the sign back
		case '%'://Find the remainder of a division
			if(y[0]<'1'&&strlen(y)<2)//(The second string is "0")
				break;//Break out of the switch-case statement
			strcal_removeDecimals(&x,&y),answer=strcal_returnPoint(dynastr_strappend(y[0]=='-'?"-":"",(x[0]=='-')^(y[0]=='-')?strcal_subtractWhole(strcal_absstr(y,0),strcal_divideWhole(strcal_absstr(x,0),strcal_absstr(y,0),1,3),3):strcal_divideWhole(strcal_absstr(x,0),strcal_absstr(y,0),1,3),1),divide,1),free(x),free(y);//Turn the number strings into whole number strings, and find the answer with the floating point back
			return answer;//Return the result
		case '/'://Do the division
			if(y[0]<'1'&&strlen(y)<2)//(The second string is "0")
				break;//Break out of the switch-case statement
			if(x[0]<'1'&&strlen(x)<2){//(The first string is "0")
				free(x),free(y),free(answer);//Free every array allocated in the heap
				return dynastr_strtmp("0",0);//Return a copy of "0"
			}
			if(!strcal_cmpstr(x,y)){//(Both strings are equal)
				free(x),free(y),free(answer);//Free every array allocated in the heap
				return dynastr_strtmp("1",0);//Return a copy of "1"
			}
			strcal_removeDecimals(&x,&y),x=strcal_absstr(x,1),y=strcal_absstr(y,1);//Remove the floating point from both strings, and turn them into their absolute value
			{//(For local usage)
				char *divide0=strcal_gcd(x,y,0);//Assign the greatest common divisor of both strings
				x=strcal_divideWhole(x,divide0,0,2),y=strcal_divideWhole(y,divide0,0,3);//Simplify the division by dividing both strings by their greatest common divisor
			}
			answer=dynastr_strappend(answer,strcal_divideWhole(x,y,0,0),3),x=strcal_divideWhole(x,y,1,2);//Append the whole division answer into the answer string and store its remainder in the first string
			if(x[0]>'0'){//(The remainder isn't "0")
				answer=dynastr_strappend(answer,".",2);//Add the '.' to the answer string
				char *tmp=dynastr_strtmp(y,0);//Create a copy of the second string (for the terminating decimal part)
				for(;tmp[strlen(tmp)-1]<'1';tmp=dynastr_strntmp(tmp,strlen(tmp)-1,1),x=dynastr_strappend(x,"0",2),answer=dynastr_strappend(answer,strcal_simpleWholeDivide(x,y,0,0),3),x=strcal_simpleWholeDivide(x,y,1,2))//Continue the division digit by digit and divide the copy by 10 until it's not divisibla by 10
					if(x[0]<'1'){//(In case that the remainder becomes 0)
						free(tmp);//Free the copy
						goto finish;//Break out of the condition
					}
				if(tmp[strlen(tmp)-1]=='5'){//(The copy is still divisible by 5)
					for(;tmp[strlen(tmp)-1]=='5';tmp=strcal_divideWhole(tmp,"5",0,2),x=dynastr_strappend(x,"0",2),answer=dynastr_strappend(answer,strcal_simpleWholeDivide(x,y,0,0),3),x=strcal_simpleWholeDivide(x,y,1,2))//Continue the division digit by digit and divide the copy by 5 until it's not divisibla by 5
						if(x[0]<'1'){//(In case that the remainder becomes 0)
							free(tmp);//Free the copy
							goto finish;//Break out of the condition
						}
				}else//(The division isn't divisible by 5)
					for(;(tmp[strlen(tmp)-1]-'0')%2<1;tmp=strcal_divideWhole(tmp,"2",0,2),x=dynastr_strappend(x,"0",2),answer=dynastr_strappend(answer,strcal_simpleWholeDivide(x,y,0,0),3),x=strcal_simpleWholeDivide(x,y,1,2))//Continue the division digit by digit and divide the copy by 2 until it's not divisibla by 2
						if(x[0]<'1'){//(In case that the remainder becomes 0)
							free(tmp);//Free the copy
							goto finish;//Break out of the condition
						}
				if(tmp[0]=='1'&&strlen(tmp)<2){//(The answer has no repeating decimals)
					free(tmp);//Free the copy
					goto finish;//Break out of the condition
				}
				for(free(tmp),tmp=dynastr_strtmp(x,0),x=dynastr_strappend(x,"0",2),answer=dynastr_strappend(answer,dynastr_strappend("(",strcal_simpleWholeDivide(x,y,0,0),1),3),x=strcal_simpleWholeDivide(x,y,1,2);strcal_cmpstr(x,tmp);x=dynastr_strappend(x,"0",2),answer=dynastr_strappend(answer,strcal_simpleWholeDivide(x,y,0,0),3),x=strcal_simpleWholeDivide(x,y,1,2))//Continue the division digit by digit until the end of the repeating decimals has been found
					if(x[0]<'1'){//(In case that the remainder becomes 0)
						free(tmp),answer=dynastr_rmchr(answer,'(',1);//Free the copy, and remove the '(' from the answer string (because it's a terminating decimal)
						goto finish;//Break out of the condition
					}
				free(tmp),tmp=strcal_fixnum(strchr(answer,'(')+1,0),answer=tmp[0]>'0'?dynastr_strappend(answer,")",2):strcal_fixnum(dynastr_rmchr(answer,'(',1),1),free(tmp);//Free the copy, and finalize the answer string
			}
			finish:
			free(x),free(y);//Free both strings
			return strcal_fixrnum(answer,1);//Return the standard form of the answer
	}
	free(x),free(y),free(answer);//Free every array which was allocated in the heap
	return 0;//Return NULL (because the division was dividing by 0 which is undefined)
}
void strcal_rnum2frac(char* n,char** dividend,char** divisor,const char release){//Assign a function which converts number strings to fraction
	if(!strchr(n,'('))//(The number string isn't recursive)
		*divisor=dynastr_mltstr("1","0",strchr(n,'.')?strlen(strchr(n,'.'))-1:0,0),*dividend=strcal_fixnum(dynastr_rmchr(n,'.',release),1);
	else{//(The number string is recursive)
		char *n0=dynastr_strnrtmp(n,strlen(strchr(n,'('))-1,0),sign=n[0]=='-'?'-':0;
		*dividend=dynastr_strntmp(n,strlen(n)-strlen(n0)-1,release),n0=dynastr_strntmp(n0,strlen(n0)-1,1),*divisor=dynastr_mltstr(dynastr_mltstr("","9",strlen(n0),0),"0",strlen(strchr(*dividend,'.'))-1,2);
		if(strlen(strchr(*dividend,'.'))<2)
			*dividend=dynastr_strntmp(*dividend,strlen(*dividend)-1,1);
		*dividend=dynastr_strappend(DYNASTR_CHR2STR(sign),strcal_calculate(strcal_calculate(strcal_absstr(strcal_fixnum(*dividend,1),1),*divisor,'*',2),strcal_fixnum(n0,1),'+',3),1);
	}
	if(*dividend[0]!='0'){
		char *divide=strcal_gcd(*dividend,*divisor,0);
		*dividend=strcal_divideWhole(*dividend,divide,0,2),*divisor=strcal_divideWhole(*divisor,divide,0,3);
	}
	return;
}
char* strcal_rcalculate(char* x,char* y,const char operation,const char release){//Assign a function same as `calculate` with recursive number support
	if(operation!='+'&&operation!='-'&&operation!='*'&&operation!='/'&&operation!='%')//Return `NULL` if the operator is invalid
		return 0;
	if(((x[0]<'1'&&strlen(x)<2)||(y[0]<'1'&&strlen(y)<2))&&(operation=='+'||operation=='-')){//(At least one of the number strings is "0" and the operator is either '+' or '-')
		if(y[0]=='0'&&strlen(y)<2){//(The second number string is "0")
			if(release&1)//Free the second number string if told to
				free(y);
			return dynastr_strtmp(x,release&2);//Return the first number string and free i	t afterwards if told to
		}//(The second number string is "0")
		if(release&2)//Free the first number string if told to
			free(x);
		return dynastr_mltstr(dynastr_strappend(operation=='-'&&y[0]!='-'?"-":"",strcal_absstr(y,0),1),y,0,2+(release&1));//Modify the second number string and return it
	}
	if(y[0]<'1'&&strlen(y)<2&&(operation=='/'||operation=='%')){//(The second number string is "0" and the operator is either '/' or '%')
		if(release&2)//Free the first number string if told to
			free(x);
		if(release&1)//Free the second number string if told to
			free(y);
		return 0;//Return NULL
	}
	if(y[0]=='1'&&strlen(y)<2&&(operation=='*'||operation=='/')){//(The second number string is "1" and the operator is either '*' or '/')
		if(release&1)//Free the second number string if told to
			free(y);
		return dynastr_strtmp(x,release&2);//Return the first number string and free it afterwards if told to
	}
	if(x[0]=='1'&&strlen(x)<2&&operation=='*'){//(The first number string is "1" and the operator is '*')
		if(release&2)//Free the first number string if told to
			free(x);
		return dynastr_strtmp(y,release&1);//Return the second number string and free it afterwards if told to
	}
	if(!strcal_cmpstr(x,y)&&(operation=='/'||operation=='%')){//(Both number strings are equal and the operator is either '/' or '%')
		if(release&2)//Free the first string if told to
			free(x);
		if(release&1)//Free the second string if told to
			free(y);
		return dynastr_strtmp(operation=='/'?"1":"0",0);//Return an answer based on the operator
	}
	if(!strchr(x,'(')&&!strchr(y,'('))//Calculate as terminating numbers if none of the number strings have brackets
		return strcal_calculate(x,y,operation,release);
	char *x0,*y0,*x1,*y1;//Assign the first & second dividend & divisor
	strcal_rnum2frac(x,&x0,&x1,release&2),strcal_rnum2frac(y,&y0,&y1,release&2);//Convert both number strings to parts of fractions and then start the calculation
	if(operation!='*'&&operation!='/'){
		char *lcm=strcal_divideWhole(strcal_calculate(x1,y1,'*',0),strcal_gcd(x1,y1,0),0,3);
		return strcal_calculate(strcal_calculate(strcal_calculate(x0,strcal_divideWhole(lcm,x1,0,1),'*',3),strcal_calculate(y0,strcal_divideWhole(lcm,y1,0,1),'*',3),operation,3),lcm,'/',3);
	}
	if(operation=='*')
		return strcal_calculate(strcal_calculate(x0,y0,'*',3),strcal_calculate(x1,y1,'*',3),'/',3);
	return strcal_calculate(strcal_calculate(x0,y1,'*',3),strcal_calculate(x1,y0,'*',3),'/',3);
}
#endif
