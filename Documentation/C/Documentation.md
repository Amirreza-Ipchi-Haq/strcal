# The `cstrcal.h` Documentation
Before we begin, you should be fimiliar with dynamic memory allocation in C. If not, I suggest you to learn it, unless you would experience problems reading this.
## How to create a simple calculator program using `cstrcal.h`
In order to create a simple calculator program using this library, we can use the following code (Sorry for the bad coding habit):
```c
#include<stdio.h>
#include"cstrcal.h"
#define WHITE(c) (char)c==' '||(char)c=='\t'||(char)c=='\n'||(char)c=='\r'//Defines a macro to check if a character is a whitespace
int main(){
	char c=getchar(),*x,operation,*y;//Assigns the first number string, the operator character & the second number string
	while(1){//Repeats forever
		while(WHITE(c))//Skips the whitespace
			c=getchar();
		x=strtmp("",0);//Initializes the first number string
		while(c!='+'&&(c!='-'||!strlen(x))&&c!='*'&&c!='/'&&c!='%')//Reads the first number string
			x=strappend(x,CHR2STR(c),2),c=getchar();
		operation=c,c=getchar();//Reads the operation
		while(WHITE(c))//Skips the whitespace
			c=getchar();
		y=strtmp("",0);//Initializes the second number string
		while(c!='\n')//Reads the second number string
			y=strappend(y,CHR2STR(c),2),c=getchar();
		{//Removes the trailing whitespace from both strings in a temporary scope
			size_t i=strlen(x);
			while(i&&WHITE(x[i-1]))
				i--;
			if(i<strlen(x))
				x=strntmp(x,i,1);
			i=strlen(y);
			while(i&&WHITE(y[i-1]))
				i--;
			if(i<strlen(y))
				y=strntmp(y,i,1);
		}
		if(isrnum(x)&&isrnum(y)){//Checks both strings if they represent numbers
			x=rcalculate(fixrnum(x,1),fixrnum(y,1),operation,3);//Makes both strings standard before calculation
			if(x){
				printf("%s",x);
				free(x);
			}else//Alerts if the answer returned NULL because of dividing by 0
				printf("Cannot divide by zero!");
		}else{//Alerts if at least one string isn't a number
			if(isrnum(x))
				printf("The third input isn't a number!");
			else if(isrnum(y))
				printf("The first input isn't a number!");
			else
				printf("The first & the third inputs aren't numbers!");
			free(x);
			free(y);
		}
		printf("\n");//Prints a newline (Useful if its running in a terminal)
	}
	return 0;
}
```
If you compile and run it, you can give an input like this:
```
2+2
```
and the output would be:
```
4
```
### Explanation
You first include the standard input/output library besides `cstrcal.h`. Then we have a macro called `WHITE` which checks if a character is a whitespace (The carriage return (`'\r'`) assigned here is basically for Windows). In the main function, we have assigned 2 character pointers representing the first & the second numbers & a character variable for the operator. We then read and assign the strings & the character values from the standard input and by skipping whitespaces.
>[!NOTE]
>This program is written in way so it'll read strings at any length. You'll figure out how.

Then, we check if the given operator is valid and alert if it isn't. After that, we check if both strings represent numbers and alert if at least one of them doesn't. Then, we turn numbers stored as strings to their standard form before we do operation on them.
>[!IMPORTANT]
>The strings must be always checked if they represent numbers and then standardized before they're given to do operations on them. Unless, you might experience an undefined behaviour.

You might notice that there's an extra argument in some functions, including the second argument in the `fixnum` and the forth argument in the `calculate` function. That's the `release` argument used to tell if the given string(s) need to be freed or not. We'll talk about that later.

Most functions in this library which have a `char*` return type return a string allocated in the heap, or `NULL` if the given argumants are invalid. The `calculate` function is one of them, and retuns `NULL` if the given operator is invalid, or it's dividing by 0. Since we know that the operator is valid, the only reason it can return `NULL` is dividing by 0. If it returns a string, we print the string. Unless, we alert that we cannot divide by 0. Finally, we print a newline in case if the program is running in the command prompt/terminal (If you don't get its use, you can simply ignore its existance).
>[!TIP]
> You can also replace `isnum` with `isrnum`, `fixnum` with `fixrnum` and `calculate` with `rcalculate` in order to support recursive numbers (such as `0.(3)` which is basically `1/3`) as inputs.

## About the `release` argument
Since one of the ways to store strings in C is assigning a dynamic character array in a character pointer (which is the way strings are mostly returned in this library), there's an option which allows users to free the strings given as arguments. For string-returning functions which take only one string as an input, you can set its `release` argument to `1` in case it needs to be freed. Unless, you can pass `0` to it.
>[!IMPORTANT]
>String literals & static character arrays must not be freed because they're allocated in the stack (and not heap) and thus, they're not freeable. If you do such, you'll get a runtime error.

But what if the function needed 2 strings as an input (like `calculate`, for example)? In such case, we can do the following steps below:
1. Set the initial value of the `release` argument to `0`.
2. If the first string's needed to be freed, add `2` to it.
3. If the second strings's needed to be freed, add `1` to it.
4. Pass the current value as the `release` argument.

You might notice that the `release` argument is treated like a binary number in this case. The first bit from the left indicates if the first string needs to be freed, and the second bit does the same to the second string.
## Reference
If you want to view the list of all functions, you can use this [reference](https://github.com/Amirreza-Ipchi-Haq/strcal/blob/main/Guide/C/Reference.md).
