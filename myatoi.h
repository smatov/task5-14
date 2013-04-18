/*
 * itoa.h
 *
 *  Created on: 18.04.2013
 *      Author: dev
 */

#ifndef ITOA_H_
#define ITOA_H_
#define MAX_INT 2147483647

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
#endif /* ITOA_H_ */
