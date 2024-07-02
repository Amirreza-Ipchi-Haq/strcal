# The `cstrcal.h` Reference
In this reference, it is assumed that you've already read the [documentation](https://github.com/Amirreza-Ipchi-Haq/strcal/blob/main/Documentation/C/Documentation.md). If not, it is suggested to read it before reading the reference.
## List of macros & functions
### Macros
|Macro|Description|
|-|-|
|[`CHR2STR(c)`](https://github.com/Amirreza-Ipchi-Haq/strcal/blob/main/Documentation/C/Reference/CHR2STR.md)|Converts a character to a static character array which is a string.|
|[`MOD10(n)`](https://github.com/Amirreza-Ipchi-Haq/strcal/blob/main/Documentation/C/Reference/MOD10.md)|Returns `n` modulus 10 in char type (For private use only).|
### Functions
|Function|Description|
|-|-|
|[`char* strtmp(char* s,const char release)`](https://github.com/Amirreza-Ipchi-Haq/strcal/blob/main/Documentation/C/Reference/strtmp.md)|Creates a copy of a string which will be allocated in the heap.|
|[`char* strntmp(char* s,size_t len,const char release)`](https://github.com/Amirreza-Ipchi-Haq/strcal/blob/main/Documentation/C/Reference/strntmp.md)|Creates a copy of a string which will be allocated in the heap with a character limit of `len` from the left.|
|[`char* strnrtmp(char* s,size_t len,const char release)`](https://github.com/Amirreza-Ipchi-Haq/strcal/blob/main/Documentation/C/Reference/strnrtmp.md)|Creates a copy of a string which will be allocated in the heap with a character limit of `len` from the right.|
|[`char* strappend(char* s0,char* s1,const char release)`](https://github.com/Amirreza-Ipchi-Haq/strcal/blob/main/Documentation/C/Reference/strappend.md)|Appends `s1` to `s0` and returns the result allocated in the heap.|
|[`char isWhole(const char* n)`](https://github.com/Amirreza-Ipchi-Haq/strcal/blob/main/Documentation/C/Reference/isWhole.md)|Checks if a string represents a whole number.|
|[`char* mltstr(char* s0,char* s1,size_t n,const char release)`](https://github.com/Amirreza-Ipchi-Haq/strcal/blob/main/Documentation/C/Reference/mltstr.md)|Returns the result of multiplying `s1` in `n` and appending it to `s0`.|
|[`char* rmchr(char* n,char c,const char release)`](https://github.com/Amirreza-Ipchi-Haq/strcal/blob/main/Documentation/C/Reference/rmchr.md)|Returns a copy of a string with `c` removed.|
|[`char* absstr(char* n,const char release)`](https://github.com/Amirreza-Ipchi-Haq/strcal/blob/main/Documentation/C/Reference/absstr.md)|Returns a copy of a string with the first `'-'` removed from the left if it exists.|
|[`char isnum(char* n)`](https://github.com/Amirreza-Ipchi-Haq/strcal/blob/main/Documentation/C/Reference/isnum.md)|Checks if a string represents a number (standard or non-standard) (Limited to terminating decimals).|
|[`char* fixnum(char* n,const char release)`](https://github.com/Amirreza-Ipchi-Haq/strcal/blob/main/Documentation/C/Reference/fixnum.md)|Standardizes a number stored as a string (Limited to terminating decimals).|
|[`void swapstr(char** a,char** b)`](https://github.com/Amirreza-Ipchi-Haq/strcal/blob/main/Documentation/C/Reference/swapstr.md)|Swaps 2 strings allocated in the heap.|
|[`char* returnPoint(char* n,const size_t posFromRight,const char release)`](https://github.com/Amirreza-Ipchi-Haq/strcal/blob/main/Documentation/C/Reference/returnPoint.md)|Puts a `'.'` in a string based on `posFromRight`.|
|[`void removeDecimals(char** x,char** y)`](https://github.com/Amirreza-Ipchi-Haq/strcal/blob/main/Documentation/C/Reference/removeDecimals.md)|Removes the point from 2 number strings allocated in the heap if they exist by multiplying both numbers in 10.|
|[`char* addWhole(char* x,char* y,const char release)`](https://github.com/Amirreza-Ipchi-Haq/strcal/blob/main/Documentation/C/Reference/addWhole.md)|Does addition to 2 whole numbers stored as strings.|
|[`char cmpstr(char* a,char *b)`](https://github.com/Amirreza-Ipchi-Haq/strcal/blob/main/Documentation/C/Reference/cmpstr.md)|Compares 2 strings based on encoding value & the length (Useful to compare 2 whole numbers stored as strings).|
|[`char* subtractWhole(char* x,char* y,const char release)`](https://github.com/Amirreza-Ipchi-Haq/strcal/blob/main/Documentation/C/Reference/subtractWhole.md)|Does subtraction to 2 whole numbers stored as strings.|
|[`char* simpleWholeDivide(char* x,char* y,const char option,const char release)`](https://github.com/Amirreza-Ipchi-Haq/strcal/blob/main/Documentation/C/Reference/simpleWholeDivide.md)|Does division on 2 whole numbers stored as strings in a simple way.|
|[`divideWhole(char* x,char* y,const char option,const char release)`](https://github.com/Amirreza-Ipchi-Haq/strcal/blob/main/Documentation/C/Reference/divideWhole.md)|Does division on 2 whole numbers stored as strings in a faster way.|
|[`char* gcd(char* x,char* y,const char release)`](https://github.com/Amirreza-Ipchi-Haq/strcal/blob/main/Documentation/C/Reference/gcd.md)|Finds the greatest common divisor from 2 whole numbers stored as strings.|
|[`char isrnum(char* n)`](https://github.com/Amirreza-Ipchi-Haq/strcal/blob/main/Documentation/C/Reference/isrnum.md)|Checks if a string represents a number (standard or non-standard) (Supports recursive decimals).|
|[`char* fixrnum(char* n,const char release)`](https://github.com/Amirreza-Ipchi-Haq/strcal/blob/main/Documentation/C/Reference/fixrnum.md)|Standardizes a number stored as a string (Supports recursive decimals).|
|[`char* calculate(char* x,char* y,const char operation,const char release)`](https://github.com/Amirreza-Ipchi-Haq/strcal/blob/main/Documentation/C/Reference/calculate.md)|Does operation on 2 numbers stored as strings (Limited to terminating decimals).|
|[`void rnum2frac(char* n,char** dividend,char** divisor,const char release)`](https://github.com/Amirreza-Ipchi-Haq/strcal/blob/main/Documentation/C/Reference/rnum2frac.md)|Converts any rational number stored as a string into a fraction with an integer dividend & a natural divisor.|
|[`char* rcalculate(char* x,char* y,const char operation,const char release)`](https://github.com/Amirreza-Ipchi-Haq/strcal/blob/main/Documentation/C/Reference/rcalculate.md)|Does operation on 2 numbers stored as strings (Supports recursive decimals).|
