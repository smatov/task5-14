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

#define MAXLINES 100
#define MAXLEN 100
#define UPTOLOWDIFF 32

char *lineptr[];

int myStrcmp(char *s, char *t) {
	for (; *s == *t; s++, t++)
		if (*s == '\0')
			return 0;
	return *s - *t;
}

int _getline(char s[], int lim) {
	int c, i;
	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}

int readlines(char *lineptr[], int maxlines) {
	int len, nlines;
	char *p, line[MAXLEN];
	nlines = 0;
	while ((len = _getline(line, MAXLEN)) > 1)
		if (nlines >= MAXLINES || (p = malloc(len)) == NULL)
			return -1;
		else {
			line[len - 1] = '\0'; /* delete newline */
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
	return nlines;
}

void writelines(char *lineptr[], int nlines) {
	int i;
	for (i = 0; i < nlines; i++)
		printf("%s\n", lineptr[i]);
}

void reverselines(char *lineptr[], int nlines) {
	int i;
	for (i = 0; i < nlines / 2; i++)
		_swap(lineptr, i, nlines - i - 1);
}

long long hashcodef(char *s1) {
	long long v1=0;
	long long i = 1;
	while (*s1) {
		if (islower(*s1))
			v1 += ((*s1 - 32) * i) % 1000000000;
		else
			v1 += (*s1 * i) % 1000000000;
		i *= 13;
		i %= 1000000000;
		s1++;
	}
	return v1;
}

long long hashcode(char *s1) {
	long long v1=0;
	long long i = 1;
	while (*s1) {
		v1 += (*s1 * i) % 1000000000;
		i *= 13;
		i %= 1000000000;
		s1++;
	}
	return v1;
}

int numcmp(char *s1, char *s2) {
	long long v1, v2;
	int i = 1;
	v1 = hashcode(s1);
	v2 = hashcode(s2);
	if (v1 < v2)
		return -1;
	else if (v1 > v2)
		return 1;
	else
		return 0;
}

int numcmpf(char *s1, char *s2) {
	long long v1, v2;
	int i = 1;
	v1 = hashcodef(s1);
	v2 = hashcodef(s2);
	if (v1 < v2)
		return -1;
	else if (v1 > v2)
		return 1;
	else
		return 0;
}

int equalfold(char *s, char *t) {
	if (abs(s - t) == UPTOLOWDIFF && isalpha(*s) && isalpha(*t))
		return 1;
	return 0;
}

void destroy(void *v[], int n) {
	int i;
	for (i = 0; i < n; i++)
		free(v[i]);
}

void _swap(void *v[], int i, int j) {
	void *temp;
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

void _qsort(void *v[], int left, int right, int(*comp)(void *, void *)) {
	int i, last;
	void _swap(void *v[], int, int);
	if (left >= right) /* do nothing if array contains */
		return; /* fewer than two elements */
	_swap(v, left, (left + right) / 2);
	last = left;
	for (i = left + 1; i <= right; i++)
		if ((*comp)(v[i], v[left]) < 0)
			_swap(v, ++last, i);
	_swap(v, left, last);
	_qsort(v, left, last - 1, comp);
	_qsort(v, last + 1, right, comp);
}

int main(int argc, char *argv[]) {
	int nlines; /* number of input lines read */
	int numeric = 0; /* 1 if numeric sort */
	int reverse = 0; /*1 for reverse sort*/
	int k;
	int fold = 0; /*to fold upper and lower case*/
	for (k = 1; k < argc; k++) {
		if (strcmp(argv[k], "-n") == 0)
			numeric = 1;
		if (strcmp(argv[k], "-r") == 0)
			reverse = 1;
		if (strcmp(argv[k], "-f") == 0)
			fold = 1;
	}
	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		if (fold) {
			_qsort((void**) lineptr, 0, nlines - 1,
					(int(*)(void*, void*)) (numeric ? numcmpf : myStrcmp));
		} else
			_qsort((void**) lineptr, 0, nlines - 1,
					(int(*)(void*, void*)) (numeric ? numcmp : strcmp));
		if (reverse)
			reverselines(lineptr, nlines);
		writelines(lineptr, nlines);
		destroy((void**) lineptr, nlines);
		return 0;
	} else {
		printf("input too big to sort\n");
		return 1;
	}
}

