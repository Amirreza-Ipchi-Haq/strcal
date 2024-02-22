# strcal
This module/library which is written in different languages (C, C++ (both standard and for Arduino) & Python3), calculates operations on numbers stored as strings as if they were numbers and usually returns a string which is the answer. It's useful for calculating numbers out of range for default variable types (for example, adding two numbers with 1000 digits). This module/library supports any rational number as inputs and outputs. The only limit is the maximum number of indexes that a character array can have. Also, since it works with numbers stored as strings, it doesn't have [Floating-Point Arthimetic](https://en.wikipedia.org/wiki/Floating-point_arithmetic) problems, such as `0.1+0.2` resulting `0.30000000000000004`.

Besides all, not just it has some number string arthimetic functions, but also some other functions to do operations on strings (such as `strtmp` which returns a copy of a string and makes you able to free the original one afterwards).
## Installation
### For non-Arduino-C++ users
This module/library is portable. It doesn't require installing and is independent from any operating system. For C/C++, you can simply include it by using `#include "strcal.h"`, and for Python3, it can be imported by using `import strcal` (It must be in the same directory as the code you want to use this library in).
### For Arduino C++ users
To install this library for Arduino IDE, you can do the following steps:
* Download the repository (either from the code section as a `.zip` file, or using a Git software such as Git or Github CLI)
* Extract the files from the zip file if you downloaded the repository as `.zip`
* Go to the `CPlusPlus_ForArduino` directory in the downloaded repository files
* Copy the `strcal` directory to the IDE's library directory in the IDE's sketchbook directory (For Windows, it's in `%UserProfile%\Documents\Arduino\libraries`, for macOS, it's in `~/Documents/Arduino` and for GNU+Linux, it's in `~/Arduino` (I cannot list all operating systems available, such as FreeBSD. You can find it yourself)).

Now you can use the library by using `#include<strcal.h>`
## The algorithm it users
This module/library uses the same method which is taught at elementary school on how to calculate big numbers (just a bit more advanced to improve speed). I've implemented it in different programming languages so a computer would be able to do that easily and quick (digit by digit). (If you ask me, I'd say that it processes more like a human brain than an actual computer)
## The reason I've created this library (and why it's a library and not a program)
I was calculating big numbers and saw that my small calculator wasn't able to show the full number, so I've decided to calculate it by hand when randomly this idea came into my head.

The reason this is a library (and not a program) is that I didn't know what uses it could have. I've turned it into a library so others could use it too.
## Documentation
If you want to learn how to use this library, these links can be helpful:
|Language|Documentation Link|Reference Link|
|-|-|-|
|C|[Link](https://github.com/Amirreza-Ipchi-Haq/strcal/blob/main/Documentation/C/Documentation.md)|[Link](https://github.com/Amirreza-Ipchi-Haq/strcal/blob/main/Documentation/C/Reference.md)|
|C++|[Link](https://github.com/Amirreza-Ipchi-Haq/strcal/blob/main/Documentation/CPP/Documentation.md)|[Link](https://github.com/Amirreza-Ipchi-Haq/strcal/blob/main/Documentation/CPP/Reference.md)|
|C++ for Arduino|[Link](https://github.com/Amirreza-Ipchi-Haq/strcal/blob/main/Documentation/CPP_ForArduino/Documentation.md)|[Link](https://github.com/Amirreza-Ipchi-Haq/strcal/blob/main/Documentation/CPP_ForArduino/Reference.md)|
|Python3|[Link](https://github.com/Amirreza-Ipchi-Haq/strcal/blob/main/Documentation/Python3/Documentation.md)|[Link](https://github.com/Amirreza-Ipchi-Haq/strcal/blob/main/Documentation/Python3/Reference.md)|

## Contact
If you want to give your feedback about this module/library (e.g. You've found bugs, or you want more features), you can [email me](mailto:ipchia3@gmail.com) about it (My email address is visible under my profile if you're signed in to GitHub).
