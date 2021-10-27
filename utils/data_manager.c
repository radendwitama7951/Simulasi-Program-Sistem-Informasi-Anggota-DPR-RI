#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../template/utilitas.h"
#include "../template/data_manager.h"
/*
static enum entity_flag {
	ANGGOTA,
	PROVINSI,
	PARTAI,
	KOMISI
};
*/
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
void show_tabel (struct anggota_dpr_t **tabel, int length) {
	struct anggota_dpr_t *tmp;
	printf("%10s%50s\n", "No", "Nama");
	for (int i = 1; i <= length; i++) {
		tmp = tabel[i];
		printf("%10d%50s\n", tmp->no_urut, tmp->nama );

	
	}

}
