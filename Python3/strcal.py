#!/usr/bin/python3
"""This module/library calculates operations on numbers stored as strings as if they were numbers
and usually returns a string which is the answer. It's useful for calculating numbers out of
range for default variable types (for example, adding two numbers with 1000 digits). This
module/library supports any terminating number (Integers & numbers with terminating decimals)
as an input and any rational number as a decimal as an output. The only limit is the maximum
number of indexes that a character array can have. Also, since it works with numbers stored as
strings, it doesn't have Floating-Point Arthimetic problems, such as 0.1+0.2 resulting
0.30000000000000004."""
def absstr(n):
	"""Creates the absolute form of a number stored as a string and returns it as a string

Note: It just removes the first '-' from any string's beginning if there's any. If there are more '-'s in the string, they're simply ignored.

Args:
	n(str): The number string to be converted

Returns:
	str: The string form of the absolute form of the argument given

Examples:
	>>> absstr('2')
	'2'

	>>> absstr('-1.6')
	'1.6'

	>>> absstr('---')
	'--'"""
	if n[0]=='-':#Remove the first '-' from the string beginning if it exists
		return n[1:]
	return n#Return the result
def isnum(n):
	"""Checks whenever a string represents a number or not

Note: A string is a number if it only contains digits, maybe only one minus sign at the beginning and
maybe only one point anywhere other than beginning or the end (without the minus sign).

Args:
	n(str): The number string to be checked

Returns:
	bool: True if it represents a number, False otherwise

Examples:
	>>> isnum('-04.3')
	True

	>>> isnum('ABC')
	False"""
	if type(n)!=str or(len(n)<2 and not n.isdigit()):#Return False if it's not a string, or the string contains less than 2 characters and isn't a whole number
		return False
	n=absstr(n)#Erase the first '-' from the string beginning if it exists
	if'-'in n:#Return false if there are more '-'s
		return False
	if'.'in n:#(There's at least one '.' in the string)
		if n.endswith('.')or n.find('.')!=n.rfind('.'):#Return false if the '.' is at the beginning/ending, or there are more than one
			return False
		n=n.replace('.','')#Remove the '.' from the string
	return n.isdigit()#Check if the modified string only contains digits
def fixnum(n):
	"""Turns a number in form of a string into its standard form

Note: The given string must represent a number in its standard form.

Args:
	n(str): The number string to be changed

Returns:
	str: The first argument given in its standard form

Examples:
	>>> fixnum('-2.5')
	'-2.5'

	>>> fixnum('-000000.00000000')
	'0'"""
	if len(n)<2:#Return the same string if the length is 1 (because it can only store the digit)
		return n
	sign='-'if n[0]=='-'else''#Store the sign
	n=absstr(n)#Turn the number string into its absolute form
	if n[0]=='.':
		n='0'+n
	while(n.find('.')if'.'in n else len(n))>1 and n[0]=='0':#Remove the zeros at the left
		n=n[1:]
	if'.'in n:#(There's a floating point in the number string)
		while n.endswith('0')or n.endswith('.'):#Remove the useless decimals at the right
			if n.endswith('.'):#Stop if all decimals were 0
				n=n[:len(n)-1]
				break
			n=n[:len(n)-1]#Remove the 0 from the right
	return'0'if n=='0'else sign+n#Return '0' if the result is '0', or the result with the sign back
def returnPoint(n,posFromRight):
	"""Puts a floating point in a whole number string at a given position

Note: The given string must represent a whole number in its standard form.

Args:
	n(str): The whole number string to put the floating point back in

	posFromRight(int): The position to put the floating point in the given whole number
	string from the right

Returns:
	str: The whole number string passed as an argument with a floating point at a given
	position if the given position is other than 0, or the same given whole number string otherwise

Examples:
	>>> returnPoint('-45',1)
	'-4.5'

	>>> returnPoint('2',1)
	'0.2'

	>>> returnPoint('64',0)
	'64'"""
	if not posFromRight:#Return the same string if the given position from right was 0
		return n
	return fixnum((n[:len(n)-posFromRight]if len(n)>posFromRight or n[0]=='-'else'0')+'.'+('0'*(len(n)-posFromRight)if len(n)<posFromRight else '')+n[len(n)-posFromRight:])#Return the number string with the floating point added
def removeDecimals(x,y):
	"""Removes the floating point from 2 number strings by multiplying them in 10 together
(Useful if you want to turn floating point numbers into integers to do operations on them)

Note: The given strings must represent numbers in their standard form.

Args:
	x(str): The first number string to remove the floating point from

	y(str): The second number string to remove the floating point from

Returns:
	(str,str): A tuple containing both strings without the floating point

Examples:
	>>> removeDecimals('2','-4.4')
	('20','-44')

	>>> removeDecimals('5.5','2.47')
	('550','247')

	>>> removeDecimals('47','6')
	('47','6')"""
	if'.'in x and not'.'in y:#(The first string has decimals and the other doesn't
		y=fixnum(y+'0'*(len(x)-x.find('.')-1))#Append '0's as much as the number of decimals in the first string to the second string and remove the extra '0's
		x=fixnum(x.replace('.',''))#Remove '.' from the first string
	elif'.'in y and not'.'in x:#(The exact opposite of the scope above with the exact opposite condition)
		x=fixnum(x+'0'*(len(y)-y.find('.')-1))
		y=fixnum(y.replace('.',''))
	elif'.'in x and'.'in y:#(Both strings have decimals)
		swap=len(x)-x.find('.')<len(y)-y.find('.')#Assign a swap indicator which is true if the second string has more decimals
		if swap:#Swap both strings if the swap indicator is `True`
			x,y=y,x
		y=fixnum(y.replace('.',''))+'0'*(len(x)-x.find('.')-len(y)+y.find('.'))#Append '0's as much as the difference between the decimals in both strings to the second string without '.' and remove extra '0's
		x=fixnum(x.replace('.',''))#Remove '.' from the first string
		if swap:#Swap both strings back if they've been swapped before
			x,y=y,x
	return x,y#Return the results
def addWhole(x,y):
	"""Adds 2 whole number strings together

Note: The given strings must represent whole numbers in their standard form.

Args:
	x(str): The first whole number string to do the addition to

	y(str): The first whole number string to do the addition with

Returns:
	str: The result of the addition in form of a string

Examples:
	>>> addWhole('2','3')
	'5'"""
	if x=='0':#Return the second string if the first string is '0'
		return y
	if y=='0':#Return the first string if the second string is '0'
		return x
	answer=""#Assign the answer string
	add=False#Assign the addition variable
	if len(x)<len(y):#Swap both strings if the second string has more characters than the first one
		x,y=y,x
	for i in range(len(x))[::-1]:#Do the addition digit by digit
		if i<len(x)-len(y):
			answer=str((int(x[i])+add)%10)+answer
			add=(int(x[i])+add)>9
		else:
			answer=str((int(x[i])+int(y[i-(len(x)-len(y))])+add)%10)+answer
			add=(int(x[i])+int(y[i-(len(x)-len(y))])-2*int('0')+add)>9
	return'1'*add+answer#Return the result
def cmpstr(a,b):
	"""Compares 2 strings based on their length and then their value

Note: This comparer doesn't compare alphabetically. Instead, it compares
based on the length size (more length means bigger), and if they have the
same length, they're compared based on character encoding value (e.g. 'B'>'A').
(Useful to compare whole numbers stored as strings)

Args:
	a(str): The first string to compare.

	b(str): The second string to compare

Returns:
	int: 0 if both are equal, 1 if the first string is bigger, and 2 otherwise

Examples:
	>>> cmpstr('1','2')
	2

	>>> cmpstr('64','8')
	1

	>>> cmpstr('5','5')
	0"""
	if len(a)!=len(b):#Return the bigger string if lengths differ
		return 1+(len(a)<len(b))
	for i in range(len(a)):#Check every character
		if a[i]!=b[i]:#Return the bigger string if the current index' characters differ
			return 1+(ord(a[i])<ord(b[i]))
	return 0#Return 0 if both strings are equal
def subtractWhole(x,y):
	"""Subtracts 2 whole number strings from each other

Note: The given strings must represent whole numbers in their standard form.

Args:
	x(str): The first whole number string to do the subtraction from

	y(str): The first whole number string to do the subtraction by

Returns:
	str: The result of the subtraction in form of a string

Examples:
	>>> subtractWhole('2','3')
	'-1'"""
	if y=='0':#Return the first string if the second string is '0'
		return x
	if x=='0':#Return the second string with a minus sign at the beginning if the first string is '0'
		return'-'+y
	if x==y:#Return '0' if both strings are equal
		return'0'
	answer=""#Assign the answer string
	sign='-'if cmpstr(x,y)>1 else''#Store the sign and set it as negative if the second string contains a bigger number
	subtract=False#Assign the subtraction
	if sign=='-':#Swap both strings if the sign is negative
		x,y=y,x
	for i in range(len(x))[::-1]:#Do the subtraction digit by digit
		if i<len(x)-len(y):
			answer=str((int(x[i])-subtract)%10)+answer
			subtract=int(x[i])-subtract<0
		else:
			answer=str((int(x[i])-int(y[i-(len(x)-len(y))])-subtract)%10)+answer
			subtract=int(x[i])-int(y[i-(len(x)-len(y))])-subtract<0
	return fixnum(sign+answer)#Return the result with the sign back
def simpleWholeDivide(x,y):
	"""Divides 2 whole number strings by each other in a simple form and
returns the whole answer & the remainder

Note0: The given strings must represent whole numbers in their standard form.

Note1: This function divides numbers in a simple but slow way, so it's useful for
dividing numbers which the answer is always below 10. (Don't use this if the answer
can be more. If so, you can use `divideWhole` instead.)

Note2: This function will throw an exception if the second argument is `"0"`.

Args:
	x(str): The first whole number string to do the division on

	y(str): The first whole number string to do the division by

Returns:
	(str,str): A tuple containing 2 numbers which represent the whole answer &
	the remainder in order from left to right as strings

Examples:
	>>> simpleWholeDivide('3','2')
	('1','1')"""
	if y=='0':#Return both values as None if the second string is '0'
		raise ZeroDivisionError("Cannot divide by 0.")
	if y=='1':#Return the first string as the answer & '0' as the remainder if the second string is '1'
		return x,'0'
	if x=='0':#Return both answer & remainder '0' if the first string is '0'
		return'0','0'
	if x==y:#Return '1' as the answer & '0' as the remainder if both strings are equal
		return'1','0'
	if cmpstr(x,y)>1:#Return '0' as the answer & the first string as the remainder if the second string is bigger than it
		return'0',x
	answer='0'#Assign the answer string with the value of '0'
	while cmpstr(x,y)<2:#Add 1 to the answer and subtract the second string from the first string until the second string is bigger than the first one
		answer=addWhole(answer,'1')#Do the addition
		x=subtractWhole(x,y)#Do the subtraction
	return answer,x#Return the whole answer & the remainder as strings
def divideWhole(x,y):
	"""Divides 2 whole number strings by each other in a faster way (compared to
`simpleWholeDivide`) and returns the whole answer & the remainder

Note0: The given strings must represent whole numbers in their standard form.

Note1: This function will throw an exception if the second argument is `"0"`.

Args:
	x(str): The first whole number string to do the division on

	y(str): The first whole number string to do the division by

Returns:
	(str,str): A tuple containing 2 numbers which represent the whole answer &
	the remainder in order from left to right as strings

Examples:
	>>> divideWhole('3','2')
	('1','1')"""
	if y=='0':#Return both values as None if the second string is '0'
		raise ZeroDivisionError("Cannot divide by 0.")
	if y=='1':#Return the first string as the answer & '0' as the remainder if the second string is '1'
		return x,'0'
	if x=='0':#Return both answer & remainder '0' if the first string is '0'
		return'0','0'
	if x==y:#Return '1' as the answer & '0' as the remainder if both strings are equal
		return'1','0'
	if cmpstr(x,y)>1:#Return '0' as the answer & the first string as the remainder if the second string is bigger than it
		return'0',x
	answer0=''#Assign the answer string
	answer1=x[0]#Assign the remainder string
	for i in [*x[1:]]+['']:#Do the division digit by digit
		answer0+=simpleWholeDivide(answer1,y)[0]
		answer1=fixnum(simpleWholeDivide(answer1,y)[1]+i)
	return fixnum(answer0),answer1#Return the whole answer & the remainder in strings
def gcd(x,y):
	"""Finds the greatest common divisor (GCD) between 2 whole number strings
using the Euclidean algorithm

Note0: The given strings must represent whole numbers in their standard form.

Note1: This function will throw an exception if the at least one of the arguments is `"0"`.

Args:
	x(str): The first whole number string to find the GCD from

	y(str): The first whole number string to find the GCD from

Returns:
	str: The greatest common divisor of both whole number strings in form
	of a string

Examples:
	>>> gcd('6','9')
	'3'

	>>> gcd('0','4')
	None"""
	if x=='0'or y=='0':#Return `None` if at least on of the strings is '0'
		raise ValueError("Both numbers to calculate the greatest common divisor from must be natural numbers.")
	if x==y:#Return the first string if both strings are equal
		return x
	while x!='0'and y!='0':#Find remainders of both strings as numbers until one of them is '0'
		x,y=divideWhole(x,y)[1],divideWhole(y,x)[1]
	return y if x=='0'else x#Return the string which isn't '0'
def isrnum(n):
	"""Does the same as `isnum(n)` with recursive number support

Note: The recursive decimals are seperated with brackets (For example 3.(3)).

Args:
	n(str): The string to be checked (Can also be other data types, which will return `False` in that case)

Returns:
	bool: `True` if the string represents a number, `False` if not

Examples:
	>>> isrnum('123')
	True

	>>> isrnum('3.(3)')
	True

	>>> isrnum('ABC')
	False

	>>> isrnum(123)
	False"""
	if type(n)!=str:#Return false if the parameter isn't a string
		return False
	if len(n)<2:#Check if the string represents a whole number if it contains less than 2 characters
		return n.isdigit()
	if(('('not in n)^(n[-1]!=')'))or n.find('(')!=n.rfind('(')or n.find(')')!=n.rfind(')'):#Return false if the number of brackets are invalid
		return False
	if'('not in n:#Check if the string represents a whole number
		return isnum(n)
	if'.'not in n or n.find('.')>n.find(')'):#Return false if the recursive decimal number string is invalid
		return False
	if not n[n.find('(')+1:n.find(')')].isdigit():#Return false if the recursive part is invalid
		return False
	return isnum(n.replace('(','').replace(')',''))#Check the complete number without the brackets
def fixrnum(n):
	"""Does the same as `fixnum(n)` with recursive number support

Note: The recursive decimals are seperated with brackets (For example 3.(3)).

Args:
	n(str): The string to be standardized

Returns:
	str: The standardized version of the given number string (or the same thing if it's already standard)

Examples:
	>>> fixrnum('123')
	'123'

	>>> fixnum('-000000000000000.000000000000000(00000000000000000)')
	'0'"""
	if'('not in n:#Check the number string as a terminating one if there are no brackets
		return fixnum(n)
	sign=n[0]=='-'#Assign the sign indicator
	n0=n[n.find('(')+1:n.find(')')]#Assign a string which stores the recursive part
	n=absstr(n[:len(n)-len(n0)-2])#Set the number string to only the terminating part
	while(n.find('.')if'.'in n else len(n))>1 and n[0]=='0':#Remove the '0's at the left of the terminating part
		n=n[1:]
	if fixnum(n0)=='0':#(The recursive part only contains '0's)
		if n[-1]=='.':#Remove the point if it's at the right
			n=n[:len(n)-1]
		return fixnum('-'*sign+n)#Return only the terminating part
	if len(n0)>1:#(The recursive part might be able to be shortend)
		modify=True#Assign a break condition
		while modify and len(n0)>1:#Shorten the recursive part
			length=len(n0)//2
			while length:
				if len(n0)%length:
					length-=1
					continue
				modify=n0[:length]==n0[len(n0)-length:]
				i=len(n0)//length-1
				while modify and i:
					modify=n0[:length]==n0[length*i-1:length*(i+1)-1]
					i-=1
				if modify:
					n0=n0[:length]
					break
				length-=1
		del modify,length,i#Delete extra objects from this scope
	while n[-1]==n0[-1]:#Shorten the number string
		n0=n0[-1]+n0[:len(n0)-1]
		n=n[:len(n)-1]
	if n0=='9':#Return 1 more of the terminating part only if the recursive part is only '9'
		return '-'*sign+returnPoint(addWhole(fixnum(n.replace('.','')),'1'),len(n)-n.find('.')-1)
	return '-'*sign+n+'('+n0+')'#Return the result
def calculate(x,y,operation):
	"""Does operation on number strings with the given operator (which is limited
to the same operators as `+`, `-`, `*`, `/`, `%`)

Note0: The given strings must represent numbers in their standard form, and the
operator must either be '+', '-', '*', '/' or '%'.

Note1: The `%` operator does exactly what Python does with numbers using this operator
(Not to be confused with other languages).

Note2: Since this function is designed to return the full number, the division might
take more time than the other operations. Also, if the answer from a division is passed
as an argument in `isnum`, it might return `False` (Depends on if the answer has repeating
decimals or not).

Note3: This function will throw an exception if either it's dividing by 0, or the operator is invalid.

Args:
	x(str): The first number string in the operation

	y(str): The second number string in the operation

	operation(str): The operator character

Returns:
	str: The answer in form of a string

Examples:
	>>> calculate('2','2','+')
	'4'

	>>> calculate('10','3','/')
	'3.(3)'

	>>> calculate('5','1.2','%')
	'0.2'"""
	if operation=='*'or operation=='/':#Pre-assign the answer string if the operator is either '*' or '%'
		answer='0'if operation=='*'else'-'if operation=='/'and(x[0]=='-')^(y[0]=='-')else''
	divide=(0 if not'.'in x and not'.'in y else len(x)-x.find('.')-1 if'.'in x and not'.'in y else len(y)-y.find('.')-1 if not'.'in x and'.'in y else len(x)+len(y)-x.find('.')-y.find('.')-2 if operation=='*'else len(x)-x.find('.')-1 if len(x)-x.find('.')>len(y)-y.find('.')else len(y)-y.find('.')-1)if operation=='+'or operation=='-'or operation=='*'or operation=='%'else None#Assign the division value
	if operation=='+':#Do addition if the operator is '+'
		x,y=removeDecimals(x,y)#Remove the point from both strings by multiplying them in 10
		if x[0]=='-'and y[0]!='-':#Subtract the absolute value of the first string from the second string if the first string is negative and the second one isn't
			answer=subtractWhole(y,absstr(x))
		elif x[0]!='-'and y[0]=='-':#Do the exact opposite of the syntax above with the exact opposite condition
			answer=subtractWhole(x,absstr(y))
		else:#Do addition if both strings are either negative or non-negative
			answer=('-'if x[0]=='-'else'')+addWhole(absstr(x),absstr(y))
		return returnPoint(answer,divide)#Return the answer with the point back
	if operation=='-':#Do subtraction if the operator is '-'
		x,y=removeDecimals(x,y)#Remove the floating point from both strings by multiplying them in 10
		if(x[0]=='-')^(y[0]=='-'):#Do addition with both strings' absolute value if only one of them is negative
			answer=('-'if x[0]=='-'else'')+addWhole(absstr(x),absstr(y))
		else:#Subtract the second string from the first string (both in their absolute form) if both strings are either negative or non-negative
			answer=('-'if x[0]=='-'else'')+subtractWhole(absstr(x),absstr(y))#Do the subtraction with the correct sign at the left
			answer=answer[2*(answer[:2]=="--"):]#Remove the "--" at the beginning of the answer string if it exists
		return returnPoint(answer,divide)#Return the result with the point back
	if operation=='*':#Do multiplication if the operator is '*'
		if x=='0'or y=='0':#Return '0' if at least one of the strings is '0'
			return '0'
		if x=='1'or y=='1':#(At least one of the strings is '1')
			return y if x=='1'else x#Return one of the strings if the other is '1'
		answer0=''#Assign the sub-answer string
		add=0#Assign the first addition variable
		sign='-'if(x[0]=='-')^(y[0]=='-')else''#Store the answer's sign
		x=fixnum(absstr(x).replace('.',''))#Remove the floating point from the absolute value of the first string and store it
		y=fixnum(absstr(y).replace('.',''))#Do the same thing above to the second string
		for i in range(len(x))[::-1]:#Do the multiplication digit by digit
			for j in y[::-1]:
				add0=int(x[i])*int(j)
				answer0=str((add+add0)%10)+answer0
				add=(add+add0)//10
			answer=addWhole(answer,(str(add)if add else'')+answer0)
			add=0
			answer0='0'*(len(x)-i)
		return returnPoint(sign+'0'*divide+answer,divide)#Return the result with the sign & the point back
	if operation=='%':#Find the modulo if the operator is '%'
		if y=='0':#Return `None` if the second string is '0'
			raise ZeroDivisionError("Cannot divide by 0.")
		x,y=removeDecimals(x,y)#Remove the point from both strings by multiplying them in 10
		return returnPoint(('-'if y[0]=='-'else'')+(subtractWhole(absstr(y),divideWhole(absstr(x),absstr(y))[1])if(x[0]=='-')^(y[0]=='-')else divideWhole(absstr(x),absstr(y))[1]),divide)#Return the remainder
	if operation=='/':#Do division if the operator is '/'
		if y=='0':#Return `None` if the second string is '0'
			raise ZeroDivisionError("Cannot divide by 0.")
		if x=='0':#Return '0' if the first string is '0'
			return'0'
		if x==y:#Return '1' if both strings are equal
			return'1'
		x,y=removeDecimals(absstr(x),absstr(y))#Remove the point from both strings by multiplying them in 10
		x,y=divideWhole(x,gcd(x,y))[0],divideWhole(y,gcd(x,y))[0]#Simplify the division by removing common factors
		answer+=divideWhole(x,y)[0]#Append the whole division answer in the answer string
		x=divideWhole(x,y)[1]#Find the remainder of the division
		if x!='0':#(The remainder isn't '0')
			answer+='.'#Append '.' to the answer string
			tmp=y#Assign a temporary string with the contents of the second string
			while tmp[-1]<'1':#Continue the division digit by digit until the temporary string isn't divisible by 10
				tmp=tmp[:len(tmp)-1]#Remove the '0' at the end
				x+='0'#Append '0' to the remainder string
				answer+=simpleWholeDivide(x,y)[0]#Find the whole answer of the new division as a string and append it to the answer string
				x=simpleWholeDivide(x,y)[1]#Store the new remainder
				if x=='0':#Return the current answer string in case that the remainder is '0'
					return fixnum(answer)
			if tmp[-1]=='5':#(The temporary string is still divisible by 5)
				while tmp[-1]=='5':#Continue the division digit by digit and divide the temporary string by 5 until it's not divisible by that number
					tmp=divideWhole(tmp,'5')[0]#Divide the temporary string in 5
					x+='0'#Append '0' to the remainder string
					answer+=simpleWholeDivide(x,y)[0]#Find the whole answer of the new division as a string and append it to the answer string
					x=simpleWholeDivide(x,y)[1]#Store the new remainder
					if x=='0':#Return the current answer string in case that the remainder is '0'
						return fixnum(answer)
			else:#(The temporary string isn't divisible by '5')
				while int(tmp[-1])%2<1:#Continue the division digit by digit and divide the temporary string by 2 until it's not divisible by that number
					tmp=divideWhole(tmp,'2')[0]#Divide the temporary string in 2
					x+='0'#Append '0' to the remainder string
					answer+=simpleWholeDivide(x,y)[0]#Find the whole answer of the new division as a string and append it to the answer string
					x=simpleWholeDivide(x,y)[1]#Store the new remainder
					if x=='0':#Return the current answer string in case that the remainder is '0'
						return fixnum(answer)
			if tmp=='1':#Return the current answer string if the temporary string is '1'
				return fixnum(answer)
			tmp=x#Set the temporary string to the current remainder string (Do a digit by digit division one more time in the next following lines)
			x+='0'#Append '0' to the remainder string
			answer+='('+simpleWholeDivide(x,y)[0]#Append '(' to the answer string and then, append the whole answer of the new division
			x=simpleWholeDivide(x,y)[1]#Store the new remainder
			while x!=tmp:#Continue dividing digit by digit until the temporary string is equal to the current remainder
				x+='0'#Append '0' to the remaainder string
				answer+=simpleWholeDivide(x,y)[0]#Find the whole answer of the new division as a string and append it to the answer string
				x=simpleWholeDivide(x,y)[1]#Store the new remainder
				if x=='0':#Return the current answer string without '(' in case that the remainder is '0'
					return fixrnum(answer.replace('(',''))
			return fixrnum(answer.replace('(',''))if fixnum(answer[answer.find('('):])=='0'else fixrnum(answer+')')#Finalize the answer and return it
		return answer#Return the answer if there's no decimal in it
	raise ValueError("Invalid operator found.")
def rnum2frac(n):
	"""Turns any rational number string into parts of a fraction stored as strings

Note: The dividend would represent an integer and the divisor a whole number

Args:
	n(str): The number string to be converted

Returns:
	(str,str): The dividend & the divisor in order

Examples:
	>>> rnum2frac('1.2')
	('6','5')

	>>> rnum2frac('3.(3)')
	('10','3')"""
	if'('not in n:#(The number string isn't recursive)
		return fixnum(n.replace('.','')),'1'+'0'*('.'in n)*(len(n)-n.find('.')-1)#Return the answer
	else:#(The number string is recursive)
		sign=n[0]=='-'#Assign the sign indicator
		n0=n[n.find('(')+1:n.find(')')]#Assign a string which stores the recursive part
		n=absstr(n[:n.find('(')])#Set the number string to only the terminating part
		n1='9'*len(n0)+'0'*(len(n)-n.find('.')-1)#Assign the divisor
		if n[-1]=='.':#Remove the '.' at the right if it exists
			n=n[:len(n)-1]
		n='-'*sign+calculate(calculate(absstr(fixnum(n)),n1,'*'),fixnum(n0),'+')
		if n!="0":
			n,n1=divideWhole(n,gcd(n,n1))[0],divideWhole(n1,gcd(n,n1))[0]
		return n,n1#Return the answer
def rcalculate(x,y,operation):
	"""Does the same as `calculate(x,y,operation)` with recursive number support

Note0: The recursive decimals are seperated with brackets (For example 3.(3)).

Note1: This function will throw an exception if either it's dividing by 0, or the operator is invalid.

Args:
	x(str): The first number string in the operation

	y(str): The second number string in the operation

	operation(str): The operator character

Returns:
	str: The answer in form of a string

Examples:
	>>> calculate('2','2','+')
	'4'

	>>> calculate('10','3','/')
	'3.(3)'

	>>> calculate('5','1.2','%')
	'0.2'

	>>> calculate('0.(3)','2','*')
	'0.(6)'"""
	if operation!='+'and operation!='-'and operation!='*'and operation!='/'and operation!='%':#Return `None` if the operator is invalid
		raise ValueError("Invalid operator found.")
	if(x=='0'or y=='0')and(operation=='+'or operation=='-'):#(At least one of the strings is "0" and the operator is either '+' or '-')
		if y=='0':#Return the first string if the second string is '0'
			return x
		return'-'*(operation=='-'and y!='-')+absstr(y)#Modify the second string and return it if the first string is '0'
	if y=='0'and(operation=='/'or operation=='%'):#Return `None` if the second number string is '0' and the operator is either '/' or '%'
		raise ZeroDivisionError("Cannot divide by 0.")
	if y=='1'and(operation=='*'or operation=='/'):#Return the first number string if the second number string is '1' and the operator is either '*' or '/'
		return x
	if x=='1'and operation=='*':#Return the second number string if the first number string is '1' and the operator is '*'
		return y
	if x==y and(operation=='/'or operation=='%'):#Return either '0' or '1' if both number strings are equal and the operator is either '/' or '%'
		return '1'if operation=='/'else'0'
	if'('not in x and'('not in y:#Calculate as terminating numbers if none of the number strings have brackets
		return calculate(x,y,operation)
	x,x0=rnum2frac(x)#Convert the first number string into a fraction
	y,y0=rnum2frac(y)#Convert the second number string into a fraction and then start the calculation
	if operation!='*'and operation!='/':
		lcm=divideWhole(calculate(x0,y0,'*'),gcd(x0,y0))[0];
		return calculate(calculate(calculate(x,divideWhole(lcm,x0)[0],'*'),calculate(y,divideWhole(lcm,y0)[0],'*'),operation),lcm,'/');
	if operation=='*':
		return calculate(calculate(x,y,'*'),calculate(x0,y0,'*'),'/');
	return calculate(calculate(x,y0,'*'),calculate(x0,y,'*'),'/');
if __name__=="__main__":#Run an example if this module is running as a standalone script
	while True:#Repeat the following lines forever
		notFirst=False#Assign a boolean object
		x=''#Assign the first number string with an empty string
		operator=None#Assign the operator character with `None`
		while not operator:#Read until a valid operator is found
			operation=input().strip()#Get input from the user
			while operation:#Write the input to the first number string character by character until a valid operator is found
				if operation[0]=='+'or(operation[0]=='-'and notFirst)or operation[0]=='*'or operation[0]=='/'or operation[0]=='%':#(A valid operator is found)
					operator=operation[0]#Store the operator
					break#Break
				x+=operation[0]#Write to the first number string
				notFirst=True#Re-assign the boolean object
				operation=operation[1:]#Reduce 1 character from the left of the input string
		x.strip()#Remove leading/trailing whitespace from the first number string
		y=operation[1:].strip()#Write the rest of the input string to the second number string
		while not y:#Keep writing until a valid string is found
			y=input().strip()
		if isrnum(x)and isrnum(y):#(Both strings represent numbers)
			try:#Print the answer
				print(rcalculate(fixrnum(x),fixrnum(y),operator))
			except:
				print("Cannot divide by 0!")
		else:#Alert which string doesn't represent a number
			print("The",("first & the third input aren't numbers"if not isrnum(x)and not isrnum(y)else("first"if isrnum(y)else"third")+" input isn't a number")+'!')
