# The `char* fixnum(char* n,const char release)` Function
This function takes a string represented as a number (limited to terminating decimals), standardizes it and returns the result allocated in the heap.
## Arguments
* `char* n`: The string representing a number to be standardized
* `const char release`: The argument indicating that `n` needs to be freed or not (Read the [documentation](https://github.com/Amirreza-Ipchi-Haq/strcal/blob/main/Documentation/C/Documentation.md#about-the-release-argument) for more information)
## Return Value
Standardized version of `n` allocated in the heap.
## Example
```c
#include<stdio.h>
#include"cstrcal.h"
int main(){
	char *s=fixnum("000012.3450000000",0);
	printf("%s\n",s);
	free(s);
	return 0;
}
```
In this example, we create a string which is the standardized version of the string `"000012.3450000000"` and print it followed by a newline. The output would be:
```
12.345
```
Finally, we free the string afterwards (because it's allocated in the heap).
