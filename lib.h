/*
 * lib.h
 *
 * Created on: 26.03.2013
 * Author: dev
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>
#include <malloc.h>
#include <ctype.h>

extern int equalfold(char *s, char *t);//

extern int directory(char *s);//

extern int myStrcmp(char *s, char *t);//

extern int myStrcmpf(char *s, char *t);//

extern void reverselines(char *lineptr[], int nlines);

extern int _getline(char s[], int lim);//

extern int readlines(char *lineptr[], int maxlines);//

extern int writelines(char *lineptr[], int nlines);//

extern int check_string_format(char *s);//

extern int numcmp(char *s1, char *s2);//

extern void _swap(void *v[], int i, int j);//

extern void __qsort(void *v[], int left, int right, int(*comp)(void *, void *));//



