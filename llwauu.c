/*unsorted uniq with with a dynamically allocated array*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Line
{
	char str[256];
	struct Line* next;
};

struct Line* input=NULL;

int searchline(char* str);

int main(int argc, char** argv)
{
	char s[256]; /*Maximum line length*/
	struct Line* tmp, * end;

	end=(struct Line*)malloc(sizeof(struct Line*));
	strncpy(end->str, "", 1);
	end->next=input;

	input=end;

	while(fgets(s, 256, stdin)!=NULL)
		if(!searchline(s))
		{
			tmp=(struct Line*)malloc(sizeof(struct Line*));
			strncpy(tmp->str, s, strlen(s)+2);
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
		if(!strncmp(it->str, str, strlen(str)+1))
			return 1;
	return 0;
}
