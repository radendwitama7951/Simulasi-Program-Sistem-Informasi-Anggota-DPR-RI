#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include "../template/utilitas.h"

// Utility Function
/* Mencetak string ke console
 *
 * */
int print_n_pause (const char *msg, ...) {
	va_list ap;
	va_start(ap, msg);

	int errno_save;
	errno_save = errno;
	vfprintf(stdout, msg, ap);
	if (errno_save != 0) {
		fprintf(stderr, "\n");
		fprintf(stderr, "Error : %s, %d\n", strerror(errno_save), errno_save);
		errno = 0;
	}
	fprintf(stdout, "\n\n");
	system("pause");

	va_end(ap);

	return errno_save;
}

/* Mengambil karakter dari stdin
 *
 * */
char get_char (const char *msg, ...) {
	char res;
	va_list ap;
	va_start(ap, msg);
	vfprintf(stdout, msg, ap);
	
	scanf(" %c", &res);
	fflush(stdin);

	va_end(ap);

	return res;	
}

/* Mengambil integer dari stdin
 *
 * */
int get_int (enum INTEGER_FORMAT fmt, const char *msg, ...) {
	int res;
	bool valid;
	va_list ap;
	va_start(ap, msg);
	
	do {
		vfprintf(stdout, msg, ap);
		scanf(" %d", &res);
		fflush(stdin);
		
		switch (fmt) {
			case ACCEPTALL :
				valid = true;
				break;
			case NONEGATIVE : case POSITIVEONLY:
				if (res < 0) {
					print_n_pause("hanya menerima bilangan positif saja ! (cth. 0,1,2,3,4,..)");
					printf("\n\n");
					valid = false;
				} else {
					valid = true;
				}
				break;

			case REALNUMONLY :
				if (res <= 0) {
					print_n_pause("hanya menerima bilangan asli saja ! (cth. 1,2,3,4,..)");
					printf("\n\n");
					valid = false;
				} else {
					valid = true;
				}
				break;
			default :
				print_n_pause("Undifined condition !");
				exit(EXIT_FAILURE);
		}
	} while (!valid);


	va_end(ap);

	return res;	
}

/* Mengambil integer dalam rentang (n,m) dari konsol
 * */
int get_range (int lower, int upper, const char *msg, ...) {
	int res;
	bool valid;
	va_list ap;
	va_start(ap, msg);
	
	do {
		vfprintf(stdout, msg, ap);
		scanf(" %d", &res);
		fflush(stdin);

		if (res < lower || res >= upper) {
			print_n_pause("hanya menerima bilangan antara %d sampai %d saja !", lower, upper);
			printf("\n\n");
			valid = false;
		} else {
			valid = true;
		}
	} while (!valid);


	va_end(ap);

	return res;	
}


char *get_string (size_t length, const char *msg, ...) {
	char *res;
	va_list ap;
	va_start(ap, msg);

	res = malloc(length);
	if (!res) {
		print_n_pause("Get string failed !\n");
	} else {
		vfprintf(stdout, msg, ap);
		scanf(" %[^\n]", res);
		fflush(stdin);
		va_end(ap);
	}
	return res;	
	
}

const char *get_time (enum TIME_FORMAT fmt) {
	char *buff = NULL;
	size_t bufflen;
	time_t rawtime = time(NULL);
	if (rawtime == -1) {
		printf("Get rawtime failed !\n\n");
		exit(EXIT_FAILURE);
	}
	
	struct tm *ptm = localtime(&rawtime);
	if (ptm == NULL) {
		printf("Get localtime failed !\n\n");
		exit(EXIT_FAILURE);
	}

	switch (fmt) {
		case FULL :
			bufflen = 30;
			buff = malloc(bufflen);
			snprintf(buff, bufflen, "%s", asctime(ptm));
			buff[strlen(buff)-1] = '\0';
			break;
		case JAM :
			bufflen = 10;
			buff = malloc(bufflen);
			strftime(buff, bufflen, "%X", ptm);
			break;
		case JAMUNDERSCORED :
			bufflen = 10;
			buff = malloc(bufflen);
			strftime(buff, bufflen, "%H_%M_%S", ptm);
			break;
		case JAMNOSEPARATOR :
			bufflen = 7;
			buff = malloc(bufflen);
			strftime(buff, bufflen, "%H%M%S", ptm);
			break;

		case TANGGAL :
			bufflen = 11;
			buff = malloc(bufflen);
			strftime(buff, bufflen, "%d/%m/%Y", ptm);
			break;
		default :
			print_n_pause("Undifined format !\n");
	}

	return buff;
}


