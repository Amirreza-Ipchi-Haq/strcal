# The `char isnum(char* n)` Function
This fuction checks if a string represents a number with terminiatng decimals or not.
## Arguments
* `char* n`: The string to be checked.
## Return value
`0` if false, `1` if true
## Example
```c
#include<stdio.h>
#include"cstrcal.h"
#define TO_BOOL(s) (isNum(s)?"true":"false")
int main(){
	printf("%s\n%s\n",TO_BOOL("-00.123450"),TO_BOOL("-.12"));
	return 0;
}
```
In this example, we check 2 strings. Then, we print the result which would be like this:
```
true
false
```
