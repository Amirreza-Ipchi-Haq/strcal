# The `cstrcal.h` Reference
In this reference, it is assumed that you've already read the [documentation](https://github.com/Amirreza-Ipchi-Haq/strcal/blob/main/Guide/C/Documentation.md). If not, it is suggested to read it before reading the reference.
## List of macros & functions
### Macros
|Macro|Description|
|-|-|
|[`CHR2STR(c)`](https://github.com/Amirreza-Ipchi-Haq/strcal/blob/main/Guide/C/Reference/CHR2STR.md)|Converts a character to a static character array which is a string.|
|[`MOD10(n)`](https://github.com/Amirreza-Ipchi-Haq/strcal/blob/main/Guide/C/Reference/MOD10.md)|Returns `n` modulus 10 in char type.|
### Functions
|Function|Description|
|-|-|
|[`char* strtmp(char* s,const char release)`](https://github.com/Amirreza-Ipchi-Haq/strcal/blob/main/Guide/C/Reference/strtmp.md)|Creates a copy of a string which will be allocated in the heap.|
|[`char* strntmp(char* s,size_t len,const char release)`](https://github.com/Amirreza-Ipchi-Haq/strcal/blob/main/Guide/C/Reference/strntmp.md)|Creates a copy of a string which will be allocated in the heap with a character limit of `len` from the left.|
|[`char* strnrtmp(char* s,size_t len,const char release)`](https://github.com/Amirreza-Ipchi-Haq/strcal/blob/main/Guide/C/Reference/strnrtmp.md)|Creates a copy of a string which will be allocated in the heap with a character limit of `len` from the right.|
|[`char* strappend(char* s0,char* s1,const char release)`](https://github.com/Amirreza-Ipchi-Haq/strcal/blob/main/Guide/C/Reference/strappend.md)|Appends `s1` to `s0` and returns the result allocated in the heap.|
|[`char isWhole(const char* n)`](https://github.com/Amirreza-Ipchi-Haq/strcal/blob/main/Guide/C/Reference/isWhole.md)|Checks if a string represents a whole number.|
|[`char* mltstr(char* s0,char* s1,size_t n,const char release)`](https://github.com/Amirreza-Ipchi-Haq/strcal/blob/main/Guide/C/Reference/mltstr.md)|Returns the result of multiplying `s1` in `n` and appending it to `s0`.|
|[`char* rmchr(char* n,char c,const char release)`](https://github.com/Amirreza-Ipchi-Haq/strcal/blob/main/Guide/C/Reference/rmchr.md)|Returns a copy of a string with `c` removed.|
|[`char* absstr(char* n,const char release)`](https://github.com/Amirreza-Ipchi-Haq/strcal/blob/main/Guide/C/Reference/absstr.md)|Returns a copy of a string with the first `'-'` removed from the left if it exists.|
|[`char isnum(char* n)`](https://github.com/Amirreza-Ipchi-Haq/strcal/blob/main/Guide/C/Reference/isnum.md)|Checks if a string represents a number (standard or non-standard).|
|[`char* fixnum(char* n,const char release)`](https://github.com/Amirreza-Ipchi-Haq/strcal/blob/main/Guide/C/Reference/fixnum.md)|Standardizes a number stored as a string.|
|[`void swapstr(char** a,char** b)`](https://github.com/Amirreza-Ipchi-Haq/strcal/blob/main/Guide/C/Reference/swapstr.md)|Swaps 2 strings allocated in the heap.|
|[`char* returnPoint(char* n,const size_t posFromRight,const char release)`](https://github.com/Amirreza-Ipchi-Haq/strcal/blob/main/Guide/C/Reference/swapstr.md)|Puts a `'.'` in a string based on `posFromRight`.|
