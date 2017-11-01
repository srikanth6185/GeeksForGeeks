/*
 * strings.c
 *
 *  Created on: Oct 30, 2017
 *      Author: srikanth6185
 */
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include"Strings.h"


void print_str_rec(char *str)
{
	if (str && (*str != '\0')) {
		print_str_rec((str + 1));
		printf("%c", *str);
	}

	return;
}
