# The `char* strappend(char* s0,char* s1,const char release)` Function
This function appends the second string to the first string and returns the result.
## Arguments
* `char* s0`: The string to be appended to
* `char* s1`: The string to be appended from
* `const char release`: The argument indicating that `s0` and/or `s1` need to be freed or not (Read the [documentation](https://github.com/Amirreza-Ipchi-Haq/strcal/blob/main/Documentation/C/Documentation.md#about-the-release-argument) for more information)
## Return Value
The result of `s0+s1`.
## Example
```c
#include<stdio.h>
#include"cstrcal.h"
int main(){
	char *s=strappend("First String","Second String",0);
	printf("%s\n",s);
	free(s);
	return 0;
}
```
In this example we define `s` with `"First String"` & `"Second String"` merged together and print the result. The output would be
```
First StringSecond String
```
followed by a newline. Finally, we free the string since it's allocated in the heap.
