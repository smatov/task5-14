/*
 * itoa.h
 *
 *  Created on: 18.04.2013
 *      Author: dev
 */
#include <malloc.h>
#ifndef ITOA_H_
#define ITOA_H_
#define MAX_INT 2147483647
#define MIN(a,b) (((a)<(b))?(a):(b))

void _reverse(char *s) {
	int cnt = 0;
	char *t;
	t = s;
	while (*t) {
		cnt++;
		t++;
	}
	while (cnt > 0) {
		char tmp;
		tmp = *s;
		*s = *(s + cnt - 1);
		*(s + cnt - 1) = tmp;
		s++;
		cnt -= 2;
	}
}

int myAtoi(char *s, int *ans) {
	long int tmp = 0;
	int sg = 1;
	if (*s == '\0') {
		return -1;
	}
	if(strlen(s) > 11) return -1;
	if (*s == '-') {
		sg = -1;
		s++;
	} else if (*s == '+') {
		sg = 1;
		s++;
	} else if (strlen(s) > 10)
		return -1;
	while (*s != '\0') {
		tmp *= 10;
		if (!isdigit(*s)) {
			return -1;
		}
		tmp += *s - '0';
		s++;
	}
	if (tmp > MAX_INT)
		return -1;
	*ans = tmp * sg;

	return 0;
}


int myItoa(int x, char *s) {
	int sg = 1;
	char *t;
	t = s;
	if (x < 0) {
		x *= -1;
		sg = -1;
	}

	int tsize = 0;
	int tmp = x;
	do {
		tsize++;
		tmp /= 10;
	} while (tmp > 0);
	if (tsize - MIN(sg,0) > malloc_usable_size(s))
		return -1;
	*s = '0';
	while (x > 0) {
		*s = x % 10 + '0';
		x /= 10;
		s++;
	}
	if (sg < 0)
		*s = '-';
	*(++s)='\0';
	_reverse(t);
	return 0;
}

#endif /* ITOA_H_ */
