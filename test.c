/*
 * test.c
 */

#include "lib.h"
#include <assert.h>
#include <stdio.h>
#define MAXLINES 100
#define MAXLEN 100

//--READLINES--//
void test_readlines_emptyfile()
{
	char *lineptr[MAXLINES];
	int i=readlines(lineptr,MAXLEN);
	assert(i==0);
	
}

void test_readlines_somelines()
{
	char *lineptr[MAXLINES];
	char *testptr[MAXLINES];
	int x;
	for(x=0; x<MAXLINES; x++)
		testptr[x] = malloc(sizeof(char)*MAXLEN);
	strcpy(testptr[0],"123");
	strcpy(testptr[1],"vasyaASDSDDSDDSDSDSDDS");
	strcpy(testptr[2],"IMAFIRINMAHLAZOR");
	int f=readlines(lineptr,MAXLEN);
	assert(f==3);
	int i;
	for(i=0; i<3; i++)
		assert(*lineptr[i]==*testptr[i]);
	for(x=0; x<MAXLINES; x++)
		free(testptr[x]);
	destroy(lineptr,f);
}


//--WRITELINES--//
void test_writelines_nolines()
{
	char *lineptr[MAXLINES];
	int i=readlines(lineptr,MAXLEN);
	int f=writelines(lineptr,i);
	assert(f==-1);
}

void test_writelines_empty_string_inside()
{
	char *testptr[MAXLINES];
	int x;
	for(x=0; x<MAXLINES; x++)
		testptr[x] = malloc(sizeof(char)*MAXLEN);
	strcpy(testptr[0],"123");
	strcpy(testptr[2],"IMAFIRINMAHLAZOR");
	*testptr[1]='\0';
	int f=writelines(testptr,3);
	assert(f==0);
	destroy(testptr,3);
}

void test_writelines()
{
	test_writelines_nolines();
	test_writelines_empty_string_inside();
}

void test_readlines()
{
	test_readlines_somelines();
	test_readlines_emptyfile();
}

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
	*a='\0';
	*b='\0';
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
	*a='\0';
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
	*a='\0';
	*b='\0';
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
	*a='\0';
	*b='\0';
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

//--SWAP--//
void test_swap_single_line()
{
	char *lineptr[MAXLINES];
	int x;
	for(x=0; x<MAXLINES; x++)
		lineptr[x]=malloc(sizeof(char)*MAXLEN);
	strcpy(lineptr[0],"123lal");
	_swap((void**)lineptr,0,0);
	assert(strcmp(lineptr[0],"123lal")==0);
	destroy(lineptr,MAXLINES);
}

void test_swap_somelines()
{
	char *lineptr[MAXLINES];
	int x;
	for(x=0; x<MAXLINES; x++)
		lineptr[x]=malloc(sizeof(char)*MAXLEN);
	strcpy(lineptr[0],"123lal");
	strcpy(lineptr[1],"faf");
	_swap((void**)lineptr,0,1);
	assert((strcmp(lineptr[1],"123lal")==0)&&(strcmp(lineptr[0],"faf")==0));
	destroy(lineptr,MAXLINES);
}

void test_swap()
{
	test_swap_single_line();
	test_swap_somelines();
}


//--GETLINE--//

void test_getline()
{
	char *s=malloc(sizeof(char)*MAXLEN);
	
}

void run_all_tests()
{
	test_numcmp();
	test_directory();
	test_check_string_format();
	test_readlines();
	test_writelines();
	test_mystrcmp();
	test_mystrcmpf();
	test_swap();
	test_equalfold();
}

int main() 
{
	test_equalfold();
	//run_all_tests();
	return 0;
}
