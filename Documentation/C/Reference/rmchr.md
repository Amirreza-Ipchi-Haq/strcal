# The `char* rmchr(char* n,char c,const char release)` Function
This function returns a copy of `n` string (Sorry for naming it like that) allocated in the heap with `c` removed from it.
## Arguments
* `char* n`: The string to be modified (Once more, sorry for the bad naming)
* `char c`: The character to be removed
* `const char release`: The argument indicating that `n` needs to be freed or not (Read the [documentation](https://github.com/Amirreza-Ipchi-Haq/strcal/blob/main/Documentation/C/Documentation.md#about-the-release-argument) for more information)
## Return Value
A copy of `n` allocated in the heap with `c` removed
## Example
```c
#include<stdio.h>
#include"cstrcal.h"
int main(){
	char *s=rmchr("Hello, World!",'l',0);
	printf("%s\n",s);
	free(s);
	return 0;
}
```
In this example, we assign the string literal `"Hello, World"` with `'l'` removed from it allocated in the heap and show the following result followed by a newline:
```
Heo, Word!
```
Finally, we free the string afterwards (because it's allocated in the heap).
