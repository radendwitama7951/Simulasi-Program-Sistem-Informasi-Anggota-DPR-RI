/* Program Simulasi Sistem Informasi DPR RI
 * by Kelompok 3
 *
 *
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include "./template/utilitas.h"
#include "./template/data_manager.h"

/////////////////////////////
/* ABAIKAN YANG ADA DISINI */
/////////////////////////////

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

static const char *filepath_anggota = "data/anggota.tsv";

// NEW anggota
static struct anggota_dpr_t *new_anggota () {
	struct anggota_dpr_t *new;
	new = malloc(sizeof(struct anggota_dpr_t));

	if (!new)
		print_n_pause("Gagal membuat anggota baru !");

	new->partai = NULL;
	new->dapil = NULL;
	new->komisi = NULL;

	return new;
}


// OPEN file & error handling
static FILE *read_file (const char *filepath) {
	FILE *fp;
	fp = fopen(filepath_anggota, "r");
	if (!fp) {
		print_n_pause("Gagal membuka file !");
	}

	return fp;

}

// NEW void array
void **new_array (size_t object_s, int n) {	
	void **new;
	size_t array_s;
	array_s = object_s * n+1;
	new = (void*) malloc(array_s);
	if (!new) {
		print_n_pause("Gagal membuat array baru !");
	}
	new[0] = NULL;
	return new;
}


// READ data_anggota from data.tsv
int create_tabel_anggota (struct anggota_dpr_t ***tabel_anggota) {
	// FLAG status
	int flag;
	// ARRAY anggota
	(*tabel_anggota) = (struct anggota_dpr_t**) new_array(sizeof(struct anggota_dpr_t*), 575);
	struct anggota_dpr_t *new_here = new_anggota();
	new_here->no_urut = 6969;
	(*tabel_anggota)[69] = new_here;
//	print_n_pause("Im here %d", ((*tabel_anggota)[69]->no_urut));
	if (!(*tabel_anggota))
		return EXIT_FAILURE;
	// READ file
	FILE *fp;
	if( (fp = read_file(filepath_anggota)) == NULL )
		return EXIT_FAILURE;

	// TEMPORARY anggota
	struct anggota_dpr_t *anggota_cur;

	fscanf(fp, "%*[^\n]");
	do {
		// ENTITY anggota
		anggota_cur = new_anggota();

		// SCAN data.tsv
	
		int row = fscanf(fp, "%d\t%[^\t]%d\t%c%d",
				&anggota_cur->no_urut, anggota_cur->nama, &anggota_cur->umur, 
				&anggota_cur->jenis_kelamin, &anggota_cur->suara_sah		
				);
		// CHECK validasi
		// printf("No %d\nNama %s\n\n", row, anggota_cur->nama);
		if (row == 5) {
			(*tabel_anggota)[anggota_cur->no_urut] = anggota_cur;
			
		} else if (row != EOF) {
			fputs("Format data.tsv tidak valid !\n", stderr);
			flag = EXIT_FAILURE;
			break;
		} else {
			flag = EXIT_SUCCESS;
			break;		
		}

	} while (true);
	// print_n_pause("Im here %d", ((*tabel_anggota)[69]->no_urut));


	flag = fclose(fp);

	return flag;
}

// SHOW array of entity
void show_tabel (struct anggota_dpr_t **tabel, int start, int stop) {
	struct anggota_dpr_t *tmp;
	printf("%10s%50s%30s\n", "no", "nama", "suara_sah");
	for (int i = start, count = 0; i <= stop; i++) {
		count++;
		tmp = tabel[i];
		printf("%10d%50s%30d\n", tmp->no_urut, tmp->nama, tmp->suara_sah );

		if (count == 100) {
			system("pause");
			clrscr;
			count = 0;
		}

	
	}

}
/////////////////////////////
/* ABAIKAN YANG ADA DISINI*/
/////////////////////////////

/* Kode komparasi sorting dengan fungsi qsort */
int sort_by_no_urut (const void* a, const void* b) {
	struct anggota_dpr_t *object_a = *(struct anggota_dpr_t**) a;
	struct anggota_dpr_t *object_b = *(struct anggota_dpr_t**) b;

		 
	if (object_a->no_urut < object_b->no_urut) return -1;
	if (object_a->no_urut > object_b->no_urut) return 1;
	return 0;
}

/* Kode komparasi sorting dengan fungsi qsort */
int sort_by_inisial (const void* a, const void* b) {
	struct anggota_dpr_t *object_a = *(struct anggota_dpr_t**) a;
	struct anggota_dpr_t *object_b = *(struct anggota_dpr_t**) b;
		 
	if (tolower(object_a->nama[0]) < tolower(object_b->nama[0])) return -1;
	if (tolower(object_a->nama[0]) > tolower(object_b->nama[0])) return 1;
	return 0;
}

/* Kode komparasi sorting dengan fungsi qsort */
int sort_by_suara_sah (const void* a, const void* b) {
	struct anggota_dpr_t *object_a = *(struct anggota_dpr_t**) a;
	struct anggota_dpr_t *object_b = *(struct anggota_dpr_t**) b;
		 
	if (object_a->suara_sah < object_b->suara_sah) return -1;
	if (object_a->suara_sah > object_b->suara_sah) return 1;
	return 0;
}

/* Mengambil data dari array mentah ke array untuk sorting */
void array_cpy (struct anggota_dpr_t ***dest, struct anggota_dpr_t ***src, int length) {
	for (int i = 1, k = 0; i <= length; i++) {
		(*dest)[k] = (*src)[i];
		k++;
	}


}

/* Interface menu utama */
int main_menu () {
	printf("Menu:\n");
	printf("\t1. Sort by No Urut\n\t2. Sort by Inisial\n\t3. Sort by jumlah suara\n\n\t0. Keluar\n\n");
	return get_range(0, 4, "Pilihan anda : ");
}


// Deklarasi fungsi sorting
void sorting_by_no_urut (struct anggota_dpr_t***, int);
void sorting_by_nama (struct anggota_dpr_t***, int);
void sorting_by_suara_sah (struct anggota_dpr_t***, int);


/////////////////////////
/*       MAIN          */
////////////////////////

int main (void) {
	int pilihan, running;
	struct anggota_dpr_t **tabel_anggota, **tmp_tabel;
	if (create_tabel_anggota(&tabel_anggota)) {
		print_n_pause("Gagal membuat tabel !");	
		return EXIT_FAILURE;
	} else {
		show_tabel(tabel_anggota, 1, 575);
		print_n_pause("\n\ndone.\n\n");
	
	};
	


	

	tmp_tabel = (struct anggota_dpr_t**) new_array(sizeof(struct anggota_dpr_t*), 574);
	array_cpy(&tmp_tabel, &tabel_anggota, 575);

	do {
		clrscr;
		//system("cls");
		pilihan = main_menu();
		switch (pilihan) {
			case 1:
				qsort((tmp_tabel), 575, sizeof(struct anggota_dpr_t*), sort_by_no_urut);

				// PEMANGGILAN FUNGSI SORTING BY NO_URUT		
				sorting_by_no_urut(&tmp_tabel, 575);

				show_tabel(tmp_tabel, 0, 574);
				print_n_pause("\n\ndone.\n\n");

				break;
			case 2:
				qsort((tmp_tabel), 575, sizeof(struct anggota_dpr_t*), sort_by_inisial);

				// PEMANGGILAN FUNGSI SORTING BY NAMA/INISIAL		
				sorting_by_nama(&tmp_tabel, 575);

				show_tabel(tmp_tabel, 0, 574);
				print_n_pause("\n\ndone.\n\n");

				break;
			case 3:
				qsort((tmp_tabel), 575, sizeof(struct anggota_dpr_t*), sort_by_suara_sah);

				// PEMANGGILAN FUNGSI SORTING BY JUMLAH PEMILIH/ SUARA SAH
				sorting_by_suara_sah(&tmp_tabel, 575);

				show_tabel(tmp_tabel, 0, 574);
				print_n_pause("\n\ndone.\n\n");

				break;

			case 0:
				print_n_pause("Terima kasih telah mencoba :)");
				running = 0;
				break;
			default:
				print_n_pause("Undefined");
				return EXIT_FAILURE;
		
		};
		
	} while (running);

	


	return 0;
}

///////////////////////
//   FUNGSI SORTING  //
//////////////////////

// SORTING BY NO URUT
void sorting_by_no_urut (struct anggota_dpr_t ***tabel_anggota, int n) {
	struct anggota_dpr_t **array = (*tabel_anggota);
};

// SORTING BY NAMA/ INISIAL
void sorting_by_nama (struct anggota_dpr_t ***tabel_anggota, int n) {
	struct anggota_dpr_t **array = (*tabel_anggota);

};

// SORTING BY JUMLAH PEMILIH/ SUARA SAH
void sorting_by_suara_sah (struct anggota_dpr_t ***tabel_anggota, int n) {
	struct anggota_dpr_t **array = (*tabel_anggota);

};








