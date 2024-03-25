# The `char* strnrtmp(char* s,size_t len,const char release)` Function
This function is similar to [`char* strntmp(char* s,size_t len,const char release)`](https://github.com/Amirreza-Ipchi-Haq/strcal/blob/main/Documentation/C/Reference/strntmp.md) with the difference that the character limit is from the right and not left.
## Arguments
* `char* s`: The string to be duplicated
* `size_t len`: The number of characters to be copied from the right
* `const char release`: The argument indicating that `s` needs to be freed or not (Read the [documentation](https://github.com/Amirreza-Ipchi-Haq/strcal/blob/main/Documentation/C/Documentation.md#about-the-release-argument) for more information)
## Return Value
The string with `len` characters copied from the left side of `s` allocated in the heap
## Example
```c
#include<stdio.h>
#include"cstrcal.h"
int main(){
	char *s=strnrtmp("String allocated in the heap",4,0);
	printf("%s\n",s);
	free(s);
	return 0;
}
```
In this example we assign `s` with the last 4 characters of the string literal `"String allocated in the heap"` and print the result followed by a newline. The output would be:
```
heap
```
Finally, we free the string since it's allocated in the heap.
