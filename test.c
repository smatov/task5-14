/*
 * test.c
 */

#include "lib.h"
#include <assert.h>



//--EQUALFOLD---//
void test_equalfold_not_same_letters() {
	char *a=malloc(sizeof(char));
	char *b=malloc(sizeof(char));
	*a='a';
	*b='B';
	int ans = equalfold(a,b);
	free(a);
	free(b);
	assert(ans==0);
}


void test_equalfold_not_alpha() {
	char *a=malloc(sizeof(char));
	char *b=malloc(sizeof(char));
	*a='1';
	*b='1';
	int ans = equalfold(a,b);
	free(a);
	free(b);
	assert(ans==1);
}

void test_equalfold_same_letters() {
	char *a=malloc(sizeof(char));
	char *b=malloc(sizeof(char));
	*a='G';
	*b='g';
	int ans = equalfold(a,b);
	free(a);
	free(b);
	assert(ans==1);
}

void test_equalfold_empty_char() {
	char *a=malloc(sizeof(char));
	char *b=malloc(sizeof(char));
	*a='G';
	int ans = equalfold(a,b);
	free(a);
	free(b);
	assert(ans==-1);
}


void test_equalfold(){
	test_equalfold_not_alpha();
	test_equalfold_empty_char();
	test_equalfold_same_letters();
	test_equalfold_not_same_letters();
}


//--MYSTRCMP--//

void test_mystrcmp_empty_strings(){
	char *a=malloc(sizeof(char)*10);
	char *b=malloc(sizeof(char)*10);
	int ans=myStrcmp(a,b);
	free(a);
	free(b);
	assert(ans==0);
}

void test_mystrcmp_not_same_strings(){
	char *a=malloc(sizeof(char)*10);
	char *b=malloc(sizeof(char)*10);
	strcpy(a,"vasya");
	strcpy(b,"petya");
	int ans=myStrcmp(a,b);
	free(a);
	free(b);
	assert(ans>0);
}

void test_mystrcmp_same_strings(){
	char *a=malloc(sizeof(char)*10);
	char *b=malloc(sizeof(char)*10);
	strcpy(a,"vasya");
	strcpy(b,"vasya");
	int ans=myStrcmp(a,b);
	free(a);
	free(b);
	assert(ans==0);
}

void test_mystrcmp(){
	test_mystrcmp_empty_strings();
	test_mystrcmp_not_same_strings();
	test_mystrcmp_same_strings();
}

//--DIRECTORY--//
void test_directory_empty(){
	char *a=malloc(sizeof(char));
	int ans = directory(a);
	free(a);
	assert(ans==-1);
}

void test_directory_space(){
	char *a=malloc(sizeof(char));
	*a=' ';
	int ans = directory(a);
	free(a);
	assert(ans==1);
}

void test_directory_digit(){
	char *a=malloc(sizeof(char));
	*a='2';
	int ans = directory(a);
	free(a);
	assert(ans==1);
}

void test_directory_alpha(){
	char *a=malloc(sizeof(char));
	*a='H';
	int ans = directory(a);
	free(a);
	assert(ans==1);
}

void test_directory_point(){
	char *a=malloc(sizeof(char));
	*a='.';
	int ans = directory(a);
	free(a);
	assert(ans==0);
}

void test_directory(){
	test_directory_point();
	test_directory_alpha();
	test_directory_digit();
	test_directory_space();
	test_directory_empty();
}

//--MYSTRCMPF--//



void test_mystrcmpf_empty_strings(){
	char *a=malloc(sizeof(char)*10);
	char *b=malloc(sizeof(char)*10);
	int ans=myStrcmpf(a,b);
	free(a);
	free(b);
	assert(ans==0);
}

void test_mystrcmpf_not_same_strings(){
	char *a=malloc(sizeof(char)*10);
	char *b=malloc(sizeof(char)*10);
	strcpy(a,"vasya");
	strcpy(b,"PetYa");
	int ans=myStrcmpf(a,b);
	free(a);
	free(b);
	assert(ans>0);
}

void test_mystrcmpf_same_strings(){
	char *a=malloc(sizeof(char)*10);
	char *b=malloc(sizeof(char)*10);
	strcpy(a,"vasya");
	strcpy(b,"vasya");
	int ans=myStrcmpf(a,b);
	free(a);
	free(b);
	assert(ans==0);
}

void test_mystrcmpf_same_strings_folder_mode(){
	char *a=malloc(sizeof(char)*10);
	char *b=malloc(sizeof(char)*10);
	strcpy(a,"vasya");
	strcpy(b,"VasYA");
	int ans=myStrcmpf(a,b);
	free(a);
	free(b);
	assert(ans==0);
}

void test_mystrcmpf(){
	test_mystrcmpf_empty_strings();
	test_mystrcmpf_not_same_strings();
	test_mystrcmpf_same_strings();
	test_mystrcmpf_same_strings_folder_mode();
}


//--CHECK_STRING_FORMAT--//

void test_check_string_format_empty_string(){
	char *a=malloc(sizeof(char)*20);
	int ans=check_string_format(a);
	free(a);
	assert(ans==-1);
	
}

void test_check_string_format_not_digits_only(){
	char *a=malloc(sizeof(char)*20);
	strcpy(a,"1234a2132e");
	int ans=check_string_format(a);
	free(a);
	assert(ans==0);
	
}

void test_check_string_format_digits_only(){
	char *a=malloc(sizeof(char)*20);
	strcpy(a,"99002391239909");
	int ans=check_string_format(a);
	free(a);
	assert(ans==1);
	
}

void test_check_string_format(){
	test_check_string_format_empty_string();
	test_check_string_format_not_digits_only();
	test_check_string_format_digits_only();
}
//--NUMCPM--//


void test_numcmp_empty(){
	char *a=malloc(sizeof(char)*10);
	char *b=malloc(sizeof(char)*10);
	int ans=numcmp(a,b);
	free(a);
	free(b);
	assert(ans==300);
}

void test_numcmp_some_strings_not_numeric(){
	char *a=malloc(sizeof(char)*10);
	char *b=malloc(sizeof(char)*10);
	strcpy(a,"123a123");
	strcpy(b,"33ff");
	int ans=numcmp(a,b);
	free(a);
	free(b);
	assert(ans==300);
}

void test_numcmp_numeric_strings(){
	char *a=malloc(sizeof(char)*10);
	char *b=malloc(sizeof(char)*10);
	strcpy(a,"123");
	strcpy(b,"33");
	int ans=numcmp(a,b);
	strcpy(a,"222");
	strcpy(b,"900");
	int am=numcmp(a,b);
	free(a);
	free(b);
	assert(ans==1 && am==-1);
}

void test_numcmp(){
	test_numcmp_numeric_strings();	
	test_numcmp_some_strings_not_numeric();
	test_numcmp_empty();
}



int main() {
	test_numcmp();
	return 0;
}
