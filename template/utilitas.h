/* Library Utilitas
 * by Raden Dwitama Baliano
 *
 * */
#ifndef __UTILITAS_H__
#define __UTILITAS_H__

#ifdef __WIN32__
#define clrscr system("cls")
#else
#define clrscr system("clear")
#endif /* __WIN32__ */
enum TIME_FORMAT {
	FULL,
	JAM,
	JAMUNDERSCORED,
	JAMNOSEPARATOR,
	TANGGAL
};

enum INTEGER_FORMAT {
	ACCEPTALL,
	NONEGATIVE,
	POSITIVEONLY,
	REALNUMONLY
};


int print_n_pause (const char *msg, ...);
char get_char (const char *msg, ...);

char *get_string (size_t length, const char *msg, ...);
int get_int (enum INTEGER_FORMAT fmt, const char *msg, ...);
int get_range (int lower, int upper, const char *msg, ...);
const char *get_time (enum TIME_FORMAT fmt);

#endif /* __UTILITAS_H__ */
