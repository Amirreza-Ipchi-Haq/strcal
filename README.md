# strcal
This library which is written in different languages (C, C++ (both standard and for Arduino) & Python3), calculates 2 numbers stored as a string as if they were numbers and returns a string which is the answer. It's useful for calculating numbers out of range for default variable types (for example, adding two numbers with 1000 digits). This library supports any terminating number (Integers & numbers with terminating decimals) as an input and any rational number as a decimal as an output. The only limit is the maximum number of indexes that an array can have.

This library is portable. It doesn't require installing and is independent from operating system. For C/C++, you can simply include it by using `#include "strcal.h"`, and for Python3, it can be imported by `import strcal` (It must be in the same directory as the code you want to use this library in).

## The algorithm it uses
This library uses the same method which is taught at elementary school on how to calculate big numbers (just a bit more advanced to improve speed). I've implemented it in different programming languages so a computer would be able to do that easily and quick (digit by digit).

## Warning (For people who know how to use this library. You can learn it from the Wiki tab)
This library's division takes a lot of time if the answer has a lot of decimals. This library is designed to show the full answer (and for numbers with repeating decimals, it shows which decimals are repeating. For example, `calculate("10","3",'/',0)` would return `"3.(3)"`). Also, the answers for addition, subtraction, multiplication and finding remainders can be re-used in the `calculate` function, but not always for division, because it might have repeating decimals, and there is still only support for integers & terminating decimals.

## The reason I've created this library (and why it's a library and not a program)
I was calculating big numbers and saw that my small calculator wasn't able to show the full number, so I've decided to calculate it by hand when randomly this idea came into my head.

The reason this is a library (and not a program) is that I didn't know what uses it could have. I've turned it into a library so others could use it too.

## Contact
If you want me to add more features (e.g. more math operations), you can email me about it (My email is ipchia3@gmail.com. It is visible under my profile if you're signed in to GitHub).
