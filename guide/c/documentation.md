# The `cstrcal.h` Documentation
Before we begin, you should be fimiliar with dynamic memory allocation in C. If not, I suggest you to learn it, unless you would experience problems reading this.
## How to create a simple calculator program using `cstrcal.h`
In order to create a simple calculator program using this library, we can use the following code (Sorry for the bad coding habit):
```c
#include<stdio.h>
#include"cstrcal.h"
char isWhitespace(char c){//Checks for whitespace
	switch(c){
		case ' ':
		case '\t':
		case '\n':
		case '\r'://For Windows only (because of CRLF ending)
			return 1;//Returns true
	}
	return 0;//Returns false
}
char* getstring(){//Reads from stdin and returns a string
	char *s=malloc(sizeof(char)),c=getchar();
	s[0]=0;
	while(isWhitespace(c))
		c=getchar();
	for(size_t i=0;!isWhitespace(c);c=getchar())
		s=realloc(s,sizeof(s)+sizeof(char)),s[i]=c,s[++i]=0;
	return s;
}
int main(){
	char *x,operation,*y;
	x=getstring();
	operation=getchar();
	while(isWhitespace(operation))//Skips the whitespace
		operation=getchar();
	y=getstring();
	if(operation!='+'&&operation!='-'&&operation!='*'&&operation!='/'&&operation!='%')//Alerts if an invalid operator is given
		printf("Not a valid operator!");
	else if(isnum(x)&&isnum(y)){//Checks both strings if they represent numbers
		x=calculate(fixnum(x,1),fixnum(y,1),operation,3);//Makes both strings standard before calculation
		if(x){
			printf("%s",x);
			free(x);
		}else//Alerts if the answer returned NULL because of dividing by 0
			printf("Cannot divide by zero!");
	}else//Alerts if at least one string isn't a number
		if(isnum(x))
			printf("The third input isn't a number!");
		else if(isnum(y))
			printf("The first input isn't a number!");
		else
			printf("The first & the third inputs aren't numbers");
	printf("\n");//Prints a newline (Useful if its running in a terminal)
	return 0;
}
```
If you compile and run it, you can give an input like this:
```
2 + 2
```
(The first & the second numbers & the operator must have at least one whitespace between them) and the output would be:
```
4
```
### Explanation
You first include the standard input/output library besides `cstrcal.h`. Then we have two functions called `isWhitespace` & `getstring`. `getstring` simply reads a string from the input stream (just like `gets` in `stdio.h` but without character limit or buffer overflow) using `isWhitespace` to skip the whitespaces.
>[!NOTE]
>If you want to use the `getstring` function in your code, besides defining `isWhitespace`, you should also `#include<stdlib.h>` (because it uses that library (The example doesn't provide it because `cstrcal.h` already includes that)). Also, when a character pointer is assigned with this function, it should be freed at the end.

In the main function, we have assigned 2 character pointers representing the first & the second numbers & a character variable for the operator. We then read and assign the strings & the character values from the standard input and by skipping whitespaces. Then, we check if the given operator is valid and alert if it isn't. After that, we check if both strings represent numbers and alert if at least one of them doesn't. Then, we turn numbers stored as strings to their standard form before we do operation on them.
>[!IMPORTANT]
>The strings must be always checked if they represent numbers and then standardized before they're given to do operations on them. Unless, you might experience an undefined behaviour.

You might notice that there's a second argument in the `fixnum` and a forth argument in the `calculate` function. That's the `release` argument used to tell if the given string(s) need to be freed or not. We'll talk about that later.

Most functions in this library which have a `char*` return type return a string allocated in the heap, or `NULL` if the given argumants are invalid. The `calculate` function is one of them, and retuns `NULL` if the given operator is invalid, or it's dividing by 0. Since we've checked the given operator, the only reason it can return `NULL` is dividing by 0. If it returns a string, we print the string. Unless, we alert that we cannot divide by 0. Finally, we print a newline in case if the program is running in the command prompt/terminal (If you don't get its use, you can simply ignore its existance).
## About the `release` argument
Since one of the ways to store strings in C is assigning a dynamic character array in a character pointer (which is the way strings are mostly returned in this library), there's an option which allows users to free the strings given as arguments. For string-returning functions which take only one string as an input, you can set its `release` argument to `1` in case it needs to be freed. Unless, you can pass `0` to it.
>[!IMPORTANT]
>String literals & static character arrays must not be freed because they're allocated in the stack (and not heap) and thus, they're not freeable. If you do such, you'll get a runtime error.

But what if the function needed 2 strings as an input (like `calculate`, for example)? In such case, we can do the following steps below:
1. Set the initial value of the `release` argument to `0`.
2. If the first string's needed to be freed, you can add `2` to it.
3. If the second strings's needed to be freed, you can add `1` to it.
4. Pass the current value as an argument.

You might notice that the `release` argument is treated like a binary number in this case. The first bit from the left indicates if the first string needs to be freed, and the second bit does the same to the second string.
## Reference
If you want to view the list of all functions, you can use this [reference](https://github.com/Amirreza-Ipchi-Haq/strcal/blob/main/guide/c/reference.md).
