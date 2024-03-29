/*
 * tmp.c
 *
 *  Created on: 11.04.2013
 *      Author: dev
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <fcntl.h>
#include <ctype.h>
#include "myatoi.h"

#define MAXLINES 100
#define MAXLEN 100
#define UPTOLOWDIFF 32


#ifdef TEST
FILE* fd;
#define OPEN_FD() fd = fopen("input.txt","r")
#define CLOSE_FD() close(fd)
#else
#define OPEN_FD()
#define CLOSE_FD()
#endif



char *lineptr[MAXLINES];
int dflag = 0;
int fflag = 0;
int numeric = 1;
int reverse = 0;

int equalfold(char *s, char *t);
void _swap(void *v[], int i, int j);
int
directory(char *s)
{
	if (isdigit(*s) || isalpha(*s) || isspace(*s))
		return 1;
	return 0;
}

int
myStrcmp(char *s, char *t)
{
	while (*s && *t) {
		if (dflag) {
			if (!directory(s) || !directory(t)) {
				if (!directory(s))
					s++;
				if (!directory(t))
					t++;
				continue;
			}
		}
		if (*s != *t)
			break;
		s++;
		t++;
	}
	return *s - *t;
}

int
myStrcmpf(char *s, char *t)
{
	while (*s && *t) {
		if (dflag) {
			if (!directory(s) || !directory(t)) {
				if (!directory(s))
					s++;
				if (!directory(t))
					t++;
				continue;
			}
		}
		if (*s != *t && !equalfold(s, t))
			break;
		s++;
		t++;
	}
	return (tolower(*s) - tolower(*t));
}

int
_getline(char s[], int lim)
{
	int c, i;
	int test=0;
#ifdef TEST
	if(fd<=0) fd = fopen("input.txt","r");
		for (i = 0; (c =getc(fd)) != EOF && c != '\n'; ++i)
		{
			if(i>=lim-1)
			{
				return -1;
			}
			s[i] = c;
		}
		test=1;
#endif
	if(!test)
	{
		for (i = 0;(c = getchar()) != EOF && c != '\n'; ++i)
		{
			if(i>=lim-1)
			{
				printf("\n");
				printf("\n");
				printf("WARNING!! Line is greater then <lim> value.\n The program won't be correct\n\n");
				return -1;
			}
			s[i] = c;
		}
	}
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}

void
drop_error_string_format()
{
	fprintf(stderr, "Incomparable string to numerical sorting\n");
}
int
check_string_format(char *s)
{
	if (*s == '-' || *s == '+' || isdigit(*s))
		s++;
	else
		return 0;
	while (isdigit(*s))
		s++;
	if (*s)
		return 0;
	return 1;
}

int
readlines(char *lineptr[], int maxlines)
{
	int len, nlines;
	char *p, line[MAXLEN];
	OPEN_FD();
	nlines = 0;
	while ((len = _getline(line, MAXLEN)) > 1)
		if (nlines >= MAXLINES )
		{
			CLOSE_FD();
			return nlines*(-1) - 1;
		}
		else
		if(!(p=malloc(len)))
		{
			CLOSE_FD();
			return nlines*(-1) - 1;
		}
		else {
			line[len - 1] = '\0';
			strcpy(p, line);
			int ans;
			int ff=myAtoi(p,&ans);
			if(numeric)
			{
				myItoa(ans,p);
			}
			if(numeric && ff==-1)
			{
				drop_error_string_format();
				CLOSE_FD();
				free(p);
				strcpy(line,"");
				return nlines*(-1) - 1;
			}
			lineptr[nlines++] = p;
		}
	CLOSE_FD();
	return nlines;
}

int
writelines(char *lineptr[], int nlines)
{
	int i;
	if(nlines==0) return -1;
	for (i = 0; i < nlines; i++)
	{
		printf("%s\n", lineptr[i]);
	}
	return 0;
}

void
reverselines(char *lineptr[], int nlines)
{
	int i;
	for (i = 0; i < nlines / 2; i++)
		_swap((void **) lineptr, i, nlines - i - 1);
}



int
numcmp(char *s1, char *s2)
{
	long double v1, v2;
	v1 = atof(s1);
	v2 = atof(s2);
	if (v1 < v2)
		return -1;
	else if (v1 > v2)
		return 1;
	else
		return 0;
}

int
equalfold(char *s, char *t)
{
	if (*s == *t)
		return 1;
	if (abs(*s - *t) == UPTOLOWDIFF && isalpha(*s) && isalpha(*t))
		return 1;
	return 0;
}

void
destroy(void *v[], int n)
{
	int i;
	for (i = 0; i < n; i++)
		free(v[i]);
}

void
_swap(void *v[], int i, int j)
{
	void *temp;
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

void
__qsort(void *v[], int left, int right, int(*comp)(void *, void *))
{
	int i, last;
	void _swap(void *v[], int, int);
	if (left >= right)
		return;
	_swap(v, left, (left + right) / 2);
	last = left;
	for (i = left + 1; i <= right; i++)
		if ((*comp)(v[i], v[left]) < 0)
			_swap(v, ++last, i);
	_swap(v, left, last);
	__qsort(v, left, last - 1, comp);
	__qsort(v, last + 1, right, comp);
}

void
_qsort(void *v[], int left, int right, int(*comp)(void *, void *))
{
	__qsort(v, 0, right, comp);
	if (reverse)
		reverselines((void *) v, right + 1);
}

#ifndef TEST
int main(int argc, char *argv[]) {
	int nlines;
	char c;
	int k = 0;
	while (--argc > 0 && (*++argv)[k] == '-')
		while ((++argv[k]) && (c = *argv[k]))
			switch (c) {
			case 'd':
				dflag = 1;
				break;
			case 'f':
				fflag = 1;
				break;
			case 'r':
				reverse = 1;
				break;
			case 'n':
				numeric = 1;
				break;
			default:
				printf("warning: illegal option %c\n", c);
				argc = 0;
				break;
			}
	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		if (fflag) {
			_qsort((void**) lineptr, 0, nlines - 1,
					(int(*)(void*, void*)) (numeric ? numcmp : myStrcmpf));
		} else
			_qsort((void**) lineptr, 0, nlines - 1,
					(int(*)(void*, void*)) (numeric ? numcmp : myStrcmp));
		writelines(lineptr, nlines);
		destroy((void**) lineptr, nlines);
		return 0;
	} else {
		nlines*=-1;
		printf("Error occurs on line %d\n",nlines);
		nlines--;
		destroy((void**) lineptr, nlines);
		return 1;
	}
}
#endif
