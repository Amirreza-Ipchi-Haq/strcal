#ifndef STRCAL_H
#define STRCAL_H
#include"Arduino.h"
namespace strcal{
	bool isWhole(String n);
	String mltstr(String s,String s0,size_t n);
	bool strExists(String s,String s0);
	String rmstr(String s,String s0);
	String absstr(String n);
	bool isnum(String n);
	String fixnum(String n);
	String returnPoint(String n,const size_t posFromRight);
	void swapstr(String &a,String &b);
	void removeDecimals(String &x,String &y);
	String addWhole(String x,String y);
	uint8_t cmpstr(String a,String b);
	uint8_t mod10(const int8_t n);
	String subtractWhole(String x,String y);
	String simpleWholeDivide(String x,String y,const bool option);
	String divideWhole(String x,String y,const bool option);
	String gcd(String x,String y);
	String calculate(String x,String y,const char operation);
	bool isrnum(String n);
	String fixrnum(String n);
	void rnum2frac(String n,String &dividend,String &divisor);
	String rcalculate(String x,String y,const char operation);
}
#endif
