#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../template/utilitas.h"
#include "../template/data_manager.h"
#include "../template/termcolor-c.h"
/*
static enum entity_flag {
	ANGGOTA,
	PROVINSI,
	PARTAI,
	KOMISI
};
*/
static const char *filepath_anggota = "data/anggota.tsv";
static const char *filepath_provinsi = "data/provinsi.tsv";
static const char *filepath_partai = "data/partai.tsv";
static const char *filepath_relasi = "data/relasi.tsv";


// NEW object
static const void *new_object (size_t object_s) {
	const void *new_t;
	new_t = malloc(object_s);
	if (!new_t) {
		print_n_pause("Gagal membuat object baru !");
		exit(EXIT_FAILURE);
	};
	return new_t;
};

/*
// NEW anggota
static struct anggota_dpr_t *new_anggota () {
	struct anggota_dpr_t *new;
	new = malloc(sizeof(struct anggota_dpr_t));

	if (!new)
		print_n_pause("Gagal membuat anggota baru !");

	new->partai = NULL;
	new->provinsi = NULL;
	new->komisi = NULL;

	return new;
}

// NEW provinsi
static struct provinsi_t *new_provinsi () {
	struct provinsi_t *new;
	new = malloc(sizeof(struct provinsi_t));
	if (!new)
		print_n_pause("Gagal membuat provinsi baru !");
	new->anggota = NULL;

	return new;
};

// NEW partai
// static struct partai_t *new_partai () {
// 	struct provinsi_t *new;
// 	new = malloc(sizeof(struct partai_t));
// 	if (!new)
// 		print_n_pause("Gagal membuat provinsi baru !");
// 	new->anggota = NULL;

// 	return new;
// };

*/

// OPEN file & error handling
static FILE *read_file (const char *filepath) {
	FILE *fp;
	fp = fopen(filepath, "r");
	if (!fp) {
		print_n_pause("Gagal membuka file !");
	}

	return fp;

}

// NEW void array
void **new_array (size_t object_s, int n) {	
	void **new;
	size_t array_s;
	array_s = object_s * n;
	new = (void*) malloc(array_s);
	if (!new) {
		print_n_pause("Gagal membuat array baru !");
		exit(EXIT_FAILURE);
	}
	new[0] = NULL;
	return new;
}


// READ data_anggota from anggota.tsv
int create_tabel_anggota (struct anggota_dpr_t ***tabel_anggota) {
	// FLAG status
	int flag;
	// ARRAY anggota
	(*tabel_anggota) = (struct anggota_dpr_t**) new_array(sizeof(struct anggota_dpr_t*), 575);

	// Error checking
	if (!(*tabel_anggota)) {
		goto END;
		flag = EXIT_FAILURE;
	}
	// READ file
	FILE *fp;
	if( (fp = read_file(filepath_anggota)) == NULL ) {
		goto END;
		flag = EXIT_FAILURE;
	}

	// TEMPORARY anggota
	// Object untuk menyimpan data
	// pada tiap baris file .tsv
	struct anggota_dpr_t *anggota_cur;

	// Abaikan baris pertama
	// karena baris pertama pada file .tsv
	// adalah judul kolom
	fscanf(fp, "%*[^\n]\n");

	// Perulangan untuk mengambil semua
	// data pada setiap baris file .tsv
	do {
		// ENTITY anggota
		// Menginisiasi object sementara tadi
		anggota_cur = (struct anggota_dpr_t*) new_object(sizeof(struct anggota_dpr_t));
		anggota_cur->partai = NULL;
		anggota_cur->provinsi = NULL;
		anggota_cur->komisi = NULL;
		

		// SCAN anggota.tsv
		// @argument 1 membaca file .tsv 
		// @argument 2 mendefinisikan karakteristik kolom dan delimiternya
		// @argument ... mendefinisikan lokasi penyimpanan data yang dispesifikasikan
		// 		 menggunakan format specifier pada argument kedua
		int row = fscanf(fp, "%d\t%[^\t]\t%d\t%c\t%d\n",
				&anggota_cur->no_urut, anggota_cur->nama, &anggota_cur->umur, 
				&anggota_cur->jenis_kelamin, &anggota_cur->suara_sah		
				);

		// CHECK validasi
		// return value dari fscanf adalah data yang berhasil diambil
		if (row == 5) {
			// Kaitkan tmp objek (anggota_cur), dengan array tabel_anggota
			// index ke nomor urut anggota
			(*tabel_anggota)[anggota_cur->no_urut] = anggota_cur;

		} else if (row != EOF) {
			fprintf(stderr, "Format %s tidak valid !\n", filepath_anggota);
			flag = EXIT_FAILURE;
			break;
		} else {
			flag = EXIT_SUCCESS;
			break;		
		}

	} while (true);
	// print_n_pause("Im here %d", ((*tabel_anggota)[69]->no_urut));



	END:
	fclose(fp);
	return flag;
};

// READ tabel provinsi
int create_tabel_provinsi (struct provinsi_t ***tabel_provinsi) {
	// FLAG status
	int flag;
	// ARRAY provinsi
	(*tabel_provinsi) = (struct provinsi_t**) new_array(sizeof(struct provinsi_t*), 34+1);
	// READ file
	FILE *fp;
	if( (fp = read_file(filepath_provinsi)) == NULL ) {
		flag = EXIT_FAILURE;
		goto END;
	}

	

	// TEMPORARY provinsi
	struct provinsi_t *provinsi_cur;

	fscanf(fp, "%*[^\n]\n");
	do {
		// ENTITY provinsi
		provinsi_cur = (struct provinsi_t*) new_object(sizeof(struct provinsi_t));
		provinsi_cur->anggota = NULL;

		// SCAN data.tsv		
		int row = fscanf(fp, "%d\t%[^\t]\t%d\n",
				&provinsi_cur->no_provinsi, provinsi_cur->nama, &provinsi_cur->jumlah_anggota
				);
		// CHECK validasi
		// printf("No %d\nNama %s\nJumlah Anggota %d\n\n", row, provinsi_cur->nama, provinsi_cur->jumlah_anggota);
		if (row == 3) {
			provinsi_cur->anggota = (struct anggota_dpr_t**) new_array(sizeof(struct anggota_dpr_t*), provinsi_cur->jumlah_anggota);
			if (!provinsi_cur->anggota) {
				flag = EXIT_FAILURE;
				break;
			}
			provinsi_cur->jumlah_anggota = 0;
			(*tabel_provinsi)[provinsi_cur->no_provinsi] = provinsi_cur;
			
		} else if (row != EOF) {
			fprintf(stderr, "Format %s tidak valid !\n", filepath_provinsi);
			flag = EXIT_FAILURE;
			break;
		} else {
			flag = EXIT_SUCCESS;
			break;		
		}

	} while (true);
	// print_n_pause("Im here %d", ((*tabel_provinsi)[69]->no_urut));
	// print_n_pause("\n\ndone\n\n");


	
	
	END:
	fclose(fp);
	return flag;
}


// READ tabel partai
int create_tabel_partai (struct partai_t ***tabel_partai) {
	// FLAG status
	int flag;
	// ARRAY partai
	(*tabel_partai) = (struct partai_t**) new_array(sizeof(struct partai_t*), 9+1);
	if (!(*tabel_partai)) {
		flag = EXIT_FAILURE;
		goto END;
	}
	// READ file
	FILE *fp;
	if( (fp = read_file(filepath_partai)) == NULL ) {
		flag = EXIT_FAILURE;
		goto END;
	}

	

	// TEMPORARY partai
	struct partai_t *partai_cur;

	fscanf(fp, "%*[^\n]\n");
	do {
		// ENTITY anggota
		partai_cur = (struct partai_t*) new_object(sizeof(struct partai_t));
		partai_cur->anggota = NULL;

		// SCAN data.tsv
		int row = fscanf(fp, "%d\t%d\t%[^\t]\t%[^\t]\t%d\n",
				&partai_cur->index, &partai_cur->no_urut, partai_cur->nama,
				partai_cur->singkatan, &partai_cur->jumlah_anggota
				);
		// CHECK validasi
		// print_n_pause("No %d\nNama %s\nJumlah Anggota %d\n\n", row, partai_cur->nama, partai_cur->jumlah_anggota);
		if (row == 5) {
			partai_cur->anggota = (struct anggota_dpr_t**) new_array(sizeof(struct anggota_dpr_t*), partai_cur->jumlah_anggota);
			if (!partai_cur->anggota) {
				flag = EXIT_FAILURE;
				break;
			}
			partai_cur->jumlah_anggota = 0;
			(*tabel_partai)[partai_cur->index] = partai_cur;
			
		} else if (row != EOF) {
			fprintf(stderr, "Format %s tidak valid !\n", filepath_partai);
			flag = EXIT_FAILURE;
			break;
		} else {
			flag = EXIT_SUCCESS;
			break;		
		}

	} while (true);
	// print_n_pause("Im here %d", ((*tabel_partai)[69]->no_urut));
	// print_n_pause("\n\ndone\n\n");


	
	
	END:
	fclose(fp);
	return flag;
}

// CREATE relations
int create_relasi (struct anggota_dpr_t **anggota, struct provinsi_t **provinsi, struct partai_t **partai, int length) {
	int flag;
	int pk_anggota, pk_provinsi, pk_partai;	


	FILE *fp;
	if( (fp = read_file(filepath_relasi)) == NULL ) {
		flag = EXIT_FAILURE;
		goto END;
	}


	fscanf(fp, "%*[^\n]\n");
	do {
		// ENTITY anggota
		// SCAN relasi.tsv
		/**
		 * PK : PRIMARY KEY
		*/
		int row = fscanf(fp, "%d\t%d\t%d\n",
				&pk_anggota, &pk_provinsi, &pk_partai);
		// CHECK validasi
		// print_n_pause("Anggota %d\nProvinsi %d\nPartai %d\n", pk_anggota, pk_provinsi, pk_partai);
		if (row == 3) {
			anggota[pk_anggota]->provinsi = provinsi[pk_provinsi];	
			anggota[pk_anggota]->partai = partai[pk_partai];
			provinsi[pk_provinsi]->anggota[provinsi[pk_provinsi]->jumlah_anggota++] = anggota[pk_anggota];
			partai[pk_partai]->anggota[partai[pk_partai]->jumlah_anggota++] = anggota[pk_anggota];
		} else if (row != EOF) {
			fprintf(stderr, "Format %s tidak valid !\n", filepath_relasi);
			flag = EXIT_FAILURE;
			break;
		} else {
			flag = EXIT_SUCCESS;
			break;		
		}

	} while (true);


	// print_n_pause("%d \t%s\t%s\t%s\n\n", 1, anggota[1]->nama, anggota[1]->partai->nama, anggota[1]->provinsi->nama);


	END:
	fclose(fp);
	return flag;


};

// COPY ARRAY
void array_cpy (struct anggota_dpr_t ***dest, struct anggota_dpr_t ***src, int length) {
	for (int i = 1, k = 0; i <= length; i++) {
		(*dest)[k] = (*src)[i];
		k++;
	}
}
