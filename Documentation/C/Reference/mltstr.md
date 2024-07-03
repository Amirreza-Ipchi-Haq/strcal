# The `char* mltstr(char* s0,char* s1,size_t n,const char release)` Function
This function multiplies `s1` in `n`, appends it to `s0` and returns the result.
## Arguments
* `char* s0`: The string to be appended to
* `char* s1`: The string to be multiplied
* `size_t n`: The multiplication value
* `const char release`: The argument indicating that `s0` and/or `s1` need to be freed or not (Read the [documentation](https://github.com/Amirreza-Ipchi-Haq/strcal/blob/main/Documentation/C/Documentation.md#about-the-release-argument) for more information)
## Return Value
The result of `s0+s1*n`
## Example
```c
#include<stdio.h>
#include"cstrcal.h"
int main(){
	char *s=mltstr("1","0",9,0);
	printf("%s\n",s);
	free(s);
	return 0;
}
```
In this example we define `s` with `"1"` & `"000000000"` (which is `"0"` repeated 9 times) merged together and print the result. The output would be
```
1000000000
```
followed by a newline. Finally, we free the string since it's allocated in the heap.
## Pro-tip
This function can be also used when you want to free a string used by another function immediately.
### Example
```c
#include<stdio.h>
#include"cstrcal.h"
int main(){
	char *(s[2])={strtmp("1",0),strtmp("2",0)};
	char *s0=mltstr(mltstr(strappend(strappend(s[0],s[1],0),strappend(s[1],s[0],0),3),s[0],0,3),s[1],0,3);
	printf("%s\n",s0);
	free(s0);
	return 0;
}
```
Output:
```
1221
```
