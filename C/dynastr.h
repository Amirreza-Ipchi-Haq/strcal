#ifndef _DYNASTR_H_
#define _DYNASTR_H_
#include<stdlib.h>
#include<string.h>
#define DYNASTR_CHR2STR(c) (char[2]){c,0}//Assign a character-to-string function
char* dynastr_strtmp(char* s,const char release){//Assign a function which creates a temporary string (Same as `strdup` with memory management included)
	if(!s)//(The string is NULL)
		return NULL;//Return NULL
	char *s0=malloc((strlen(s)+1)*sizeof(char));//Allocate memory as much as the length of the string (until NUL) plus one more byte for NUL
	strcpy(s0,s);//Copy string content to the new string
	if(release)//Free the old string if told to
		free(s);
	return s0;//Return a pointer to the array allocated in the heap
}
char* dynastr_strntmp(char* s,size_t len,const char release){//(Same as the function above with a character limit from the left)
	if(!s)//(The string is NULL)
		return NULL;//Return NULL
	if(!len){//(The number of characters to be copied is 0)
		if(release)//Free the string if told to
			free(s);
		return dynastr_strtmp("",0);//Return a copy of an empty string
	}
	if(len>=strlen(s))//(The number of characters to be printed is more than the length os the string)
		return dynastr_strtmp(s,release);//Return a copy of the string and free the original one if told to
	char s0[len+1];//Create a character array as much as the length limit plus one more index for NUL
	s0[len]=0;//Set the last index as NUL
	while(len--)//Copy the original string content to the array until the length limit
		s0[len]=s[len];
	if(release)//Free the original string if told to
		free(s);
	return dynastr_strtmp(s0,0);//Return a copy of the character array
}
char* dynastr_strnrtmp(char* s,size_t len,const char release){//(Same as the function above with the limit starting from the right)
	if(!s)//(The string is NULL)
		return NULL;//Return NULL
	if(!len){//(The number of characters to be copied is 0)
		if(release)//Free the string if told to
			free(s);
		return dynastr_strtmp("",0);//Return a copy of an empty string
	}
	if(len>=strlen(s))//(The number of characters to be printed is more than the length os the string)
		return dynastr_strtmp(s,release);//Return a copy of the string and free the original one if told to
	char s0[len+1];//Create a character array as much as the length limit plus one more index for NUL
	s0[len]=0;//Set the last index as NUL
	for(size_t i=strlen(s);len--;s0[len]=s[--i]);//Copy the original string content to the array from the right until the length limit
	if(release)//Free the original string if told to
		free(s);
	return dynastr_strtmp(s0,0);//Return a copy of the character array
}
char* dynastr_strappend(char* s0,char* s1,const char release){//Assign a function which sticks 2 strings together and returns the result
	char s[strlen(s0)+strlen(s1)+1];//Create a char array as much as the sum of both string's length until NUL plus one more index for NUL
	strcat(strcpy(s,s0),s1);//Copy both string content into the character array
	if(release&2)//Free the first string if told to
		free(s0);
	if(release&1)//Free the second string if told to
		free(s1);
	return dynastr_strtmp(s,0);//Return a copy of the character array
}
char* dynastr_mltstr(char* s0,char* s1,size_t n,const char release){//Assign a function which "multiplies" the second string and appends it to the first one
	s0=dynastr_strtmp(s0,release&2);//Create a copy of the first string an free the first string if told to
	while(n--)//Append the second string to the copy `n` times which `n` is initialized while calling the function
		s0=dynastr_strappend(s0,s1,2);
	if(release&1)//Free the second string if told to
		free(s1);
	return s0;//Return the copy
}
char* dynastr_rmchr(char* n,char c,const char release){//Assign a function which removes a character completely from a string
	n=dynastr_strtmp(n,release);//Create a copy of the string and free the original one if told to
	while(strchr(n,c))//Remove the assigned character from the string until it doesn't exist in it
		n=dynastr_mltstr(dynastr_strappend(dynastr_strntmp(n,strlen(n)-strlen(strchr(n,c)),0),strchr(n,c)+1,2),n,0,3);
	return n;//Return the result
}
void dynastr_swapstr(char** a,char** b){//Assign a function which swaps 2 strings allocated in the heap
	char *tmp=*a;//Create a copy of the first string
	*a=*b,*b=tmp;//Swap values and free the copy after it
	return;
}
#endif
