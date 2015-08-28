/*unsorted uniq with with a dynamically allocated array*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Line
{
	char* str;
	struct Line* next;
};

struct Line* input;

int searchline(char* str);

int main(int argc, char** argv)
{
	char s[256]; /*Maximum line length*/
	struct Line* tmp;

	input=NULL;

	while(fgets(s, 256, stdin)!=NULL)
		if(!searchline(s))
		{
			tmp=(struct Line*)malloc(sizeof(struct Line*));
			tmp->str=(char*)malloc(sizeof(char)*strlen(s));
			strcpy(tmp->str, s);
			tmp->next=input;
			input=tmp;
			printf(s);
		}

	return 0;
}

int searchline(char* str)
{
	struct Line* it;
	for(it=input; it!=NULL; it=it->next)
		if(!strcmp(it->str, str))
			return 1;
	return 0;
}
