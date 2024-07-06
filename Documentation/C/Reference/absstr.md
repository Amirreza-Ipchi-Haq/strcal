# The `char* absstr(char* n,const char release)` Function
This function removes the first `'-'` from `n` from the beginning if there's any and returns the result allocated in the heap.
## Arguments
* `char* n`: The string to remove the first `'-'` from
* `const char release`: The argument indicating that `n` needs to be freed or not (Read the [documentation](https://github.com/Amirreza-Ipchi-Haq/strcal/blob/main/Documentation/C/Documentation.md#about-the-release-argument) for more information)
## Return Value
`n` without the first `'-'`
## Example
```c
#include<stdio.h>
#include"cstrcal.h"
int main(){
	char *s=absstr("--string--",0);
	printf("%s\n",s);
	free(s);
	return 0;
}
```
In this example, we define `"--string--"` without the first `'-'` and print it followed by a newline. The output would be:
```
-string--
```
Finally, we free the string afterwards (because it's allocated in the heap).
