# The `cstrcal.h` Reference
In this reference, it is assumed that you've already read the [documentation](https://github.com/Amirreza-Ipchi-Haq/strcal/blob/main/Guide/C/Documentation.md). If not, it is suggested to read it before reading the reference.
## List of macros & functions
### Macros
|Macro|Description|
|-|-|
|[`CHR2STR(c)`](https://github.com/Amirreza-Ipchi-Haq/strcal/blob/main/Guide/C/Reference/CHR2STR.md)|Converts a character to a static character array which is a string.|
|[`MOD10(n)`](https://github.com/Amirreza-Ipchi-Haq/strcal/blob/main/Guide/C/Reference/MOD10.md)|Returns `n` modulus 10 in char format.|
### Functions
|Function|Description|
|-|-|
|[`char* strtmp(char* s,const char release)`](https://github.com/Amirreza-Ipchi-Haq/strcal/blob/main/Guide/C/Reference/strtmp.md)|Creates a copy of `s` which will be allocated in the heap.|
|[`char* strntmp(char* s,size_t len,const char release)`](https://github.com/Amirreza-Ipchi-Haq/strcal/blob/main/Guide/C/Reference/strntmp.md)|Creates a copy of `s` which will be allocated in the heap with a character limit of `len` from the left.|
|[`char* strnrtmp(char* s,size_t len,const char release)`](https://github.com/Amirreza-Ipchi-Haq/strcal/blob/main/Guide/C/Reference/strnrtmp.md)|Creates a copy of `s` which will be allocated in the heap with a character limit of `len` from the right.|
|[`char* strappend(char* s0,char* s1,const char release)`](https://github.com/Amirreza-Ipchi-Haq/strcal/blob/main/Guide/C/Reference/strappend.md)|Appends `s1` to `s0` and returns the result allocated in the heap.|
|[`char isWhole(const char* n)`](https://github.com/Amirreza-Ipchi-Haq/strcal/blob/main/Guide/C/Reference/isWhole.md)|Checks if `n` represents a whole number.|
