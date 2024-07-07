# The `char isWhole(const char* n)` Function
This function checks if the current string represents a whole number (which means it only contains digits).
## Arguments
* `char* s`: The string to be checked.
## Return value
`0` if false, `1` if true
## Example
```c
#include<stdio.h>
#include"cstrcal.h"
#define TO_BOOL(s) (isWhole(s)?"true":"false")
int main(){
	printf("%s\n%s\n",TO_BOOL("012345"),TO_BOOL("-12"));
	return 0;
}
```
In this example, we check an array of strings containing 2 indexes. Then, we print the result which would be like this:
```
true
false
```
