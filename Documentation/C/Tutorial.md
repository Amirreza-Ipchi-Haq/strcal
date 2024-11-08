# The `cstrcal.h` Tutorial
Before we begin, you should be fimiliar with dynamic memory allocation in C. If not, I suggest you to learn it, unless you would experience problems reading this.

Also, you have to be fimiliar with [dynastr reference](https://github.com/Amirreza-Ipchi-Haq/dynastr/blob/main/Reference.md) to be able to use this library ([dynastr](https://github.com/Amirreza-Ipchi-Haq/dynastr) is `cstrcal.h`'s dependency).
## How to create a simple calculator program using `cstrcal.h`
In order to create a simple calculator program using this library, we can use the following code (Sorry for the bad coding habit):
```c
#include<stdio.h>
#include"cstrcal.h"
#define WHITE(c) (c==' '||c=='\t'||c=='\n'||c=='\r')//Defines a macro to check if a character is a whitespace
int main(){
	char c=getchar(),*x,operation,*y;//Assigns the first number string, the operator character & the second number string
	while(1){//Repeats forever
		while(WHITE(c))//Skips the whitespace
			c=getchar();
		x=dynastr_strtmp("",0);//Initializes the first number string
		while(c!='+'&&(c!='-'||!strlen(x))&&c!='*'&&c!='/'&&c!='%')//Reads the first number string
			x=dynastr_strappend(x,DYNASTR_CHR2STR(c),2),c=getchar();
		operation=c,c=getchar();//Reads the operator
		while(WHITE(c))//Skips the whitespace
			c=getchar();
		y=dynastr_strtmp("",0);//Initializes the second number string
		while(c!='\n')//Reads the second number string
			y=dynastr_strappend(y,DYNASTR_CHR2STR(c),2),c=getchar();
		{//Removes the trailing whitespace from both strings in a temporary scope
			size_t i=strlen(x);
			while(i&&WHITE(x[i-1]))
				i--;
			if(i<strlen(x))
				x=dynastr_strntmp(x,i,1);
			i=strlen(y);
			while(i&&WHITE(y[i-1]))
				i--;
			if(i<strlen(y))
				y=dynastr_strntmp(y,i,1);
		}
		if(strcal_isnum(x)&&strcal_isnum(y)){//Checks both strings if they represent numbers
			x=strcal_calculate(strcal_fixnum(x,1),strcal_fixnum(y,1),operation,3);//Makes both strings standard before calculation
			if(x){
				printf("%s",x);
				free(x);
			}else//Alerts if the answer returned NULL because of dividing by 0
				printf("Cannot divide by zero!");
		}else{//Alerts if at least one string isn't a number
			if(strcal_isnum(x))
				printf("The second operand isn't a number!");
			else if(strcal_isnum(y))
				printf("The first operand isn't a number!");
			else
				printf("The first & the second operands aren't numbers!");
			free(x);
			free(y);
		}
		printf("\n");//Prints a newline
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

Then, we check if both strings represent numbers and alert if at least one of them doesn't. After that, we turn numbers stored as strings to their standard form before we do operation on them.
>[!IMPORTANT]
>The strings must be always checked if they represent numbers and then standardized before they're given to do operations on them. Unless, you might experience an undefined behaviour.

You might notice that there's an extra argument in some functions, including the second argument in the `fixnum` and the forth argument in the `calculate` function. That's the `release` argument used to tell if the given string(s) need to be freed or not. You can read about it [here](https://github.com/Amirreza-Ipchi-Haq/dynastr/blob/main/Reference.md#note).

Most functions in this library which have a `char*` return type return a string allocated in the heap, or `NULL` if the given argumants are invalid. The `calculate` function is one of them, and retuns `NULL` if the given operator is invalid, or it's dividing by 0. Since we know that the operator is valid, the only reason it can return `NULL` is dividing by 0. If it returns a string, we print the string. Unless, we alert that we cannot divide by 0. Finally, we print a newline.
>[!TIP]
> You can also replace `strcal_isnum` with `strcal_isrnum`, `strcal_fixnum` with `strcal_fixrnum` and `strcal_calculate` with `strcal_rcalculate` in order to support recursive numbers (such as `0.(3)` which is basically `1/3`) as inputs.
## Reference
If you want to view the list of all functions, you can use this [reference](https://github.com/Amirreza-Ipchi-Haq/strcal/blob/main/Documentation/C/Reference.md).
