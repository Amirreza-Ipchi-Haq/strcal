# The `char* strtmp(char* s,const char release)` Function
This function returns a duplicated string from `s` allocated in the heap. It functions like the POSIX `string.h` function `strdup`, but with the ability to free the original string afterwards.
## Example
```c
#include<stdio.h>
#include"cstrcal.h"
int main(){
	char *s=strtmp("String allocated in the heap",0);
	printf("%s\n",s);
	free(s);
	return 0;
}
```
In this example, we give the string literal `"String allocated in the heap"` to `strtmp` and store the result in the character pointer `s`. Then, we print the string followed by a newline and free the string afterwards (because it's allocated in the heap).
