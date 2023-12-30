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
	String returnPoint(String n,size_t posFromRight);
	void swapstr(String &a,String &b);
	void removeDecimals(String &x,String &y);
	String addWhole(String x,String y);
	uint8_t cmpstr(String a,String b);
	uint8_t mod10(int8_t n);
	String subtractWhole(String x,String y);
	String simpleWholeDivide(String x,String y,bool option);
	String divideWhole(String x,String y,bool option);
	String gcd(String x,String y);
	String calculate(String x,String y,char operation);
	class strnum{//Assign a class which stores a number string and does some of the operations above on it
		public://(All properties are public)
			String num;//Assign the main string
			strnum(String n="0"){//Assign the initializer (All the methods below are basically the functions above)
				num=n;//Initialize the number string
				return;
			}
			bool isWhole();
			bool strExists(String s);
			String rmstr(String s);
			String absstr();
			bool isnum();
			String fixnum();
			String returnPoint(size_t posFromRight);
			void swapstr(String &s);
			uint8_t cmpstr(String s);
			String gcd(String n);
			String calculate(String n,char operation);
	};
}
#endif
