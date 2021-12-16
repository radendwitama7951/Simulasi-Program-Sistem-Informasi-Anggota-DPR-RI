/* Module.c
 * Module untuk digunakan oleh end user
* */

#pragma GCC diagnostic ignored "-Wunused-variable"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "../template/utilitas.h"
#include "../template/data_manager.h"
#include "../template/modules.h"


// SHOW General
void show_general (struct anggota_dpr_t **tabel, int length, int start, int length_page) {
	int total_page, current_page;
	current_page = 0;
	total_page = (((length - start) % length_page) == 0) ? (length - start) / length_page : ((length - start) / length_page) + 1;
	struct anggota_dpr_t *tmp;
	printf("%10s%64s%30s%30s\n", "NO_URUT", "NAMA", "PROVINSI", "PARTAI");
	for (int i = start, count = 0; i < length; i++) {
		count++;
		current_page = ((count%length_page) != 0) ? (count/length_page)+1 : count/length_page;

		tmp = tabel[i];
		printf("%10d%64s%30s%30s\n", tmp->no_urut, tmp->nama, tmp->provinsi->nama, tmp->partai->singkatan);

		if ((count%length_page) == 0 || i == length-1) {
			print_n_pause("\nPage %d of %d", current_page, total_page);
			clrscr;
			//count = 0;
		}

	
	}
};

// SHOW array of entity
/*
 * Prosedur
*/
void show_tabel (struct anggota_dpr_t **tabel, int length, int start, int length_page) {
	int total_page, current_page;
	current_page = 0;
	total_page = (((length - start) % length_page) == 0) ? (length - start) / length_page : ((length - start) / length_page) + 1;
	struct anggota_dpr_t *tmp;
	printf("%10s%64s%20s%20s%30s\n", "NO_URUT", "NAMA", "UMUR", "JENIS_KELAMIN", "SUARA_SAH");
	for (int i = start, count = 0; i < length; i++) {
		count++;
		current_page = ((count%length_page) != 0) ? (count/length_page)+1 : count/length_page;

		tmp = tabel[i];
		printf("%10d%64s%20d%20c%30d\n", tmp->no_urut, tmp->nama, tmp->umur, tmp->jenis_kelamin, tmp->suara_sah );

		if ((count%length_page) == 0 || i == length-1) {
			print_n_pause("\nPage %d of %d", current_page, total_page);
			// clrscr;
			//count = 0;
		}

	
	}
};

// SHOW array of entity
/*
 * Tabel provinsi only
*/
void showall_provinsi (struct provinsi_t **tabel, int length) {
	printf("%10s%64s%20s\n", "NO_PROVINSI", "NAMA", "JUMLAH_ANGGOTA");
	for (int i = 1; i <= length; i++) {
		printf("%10d%64s%20d\n", tabel[i]->no_provinsi, tabel[i]->nama, tabel[i]->jumlah_anggota);
	}
}

// SHOW array of entity
/*
 * Tabel partai only
*/
void showall_partai (struct partai_t **tabel, int length) {
	printf("%10s%10s%20s%72s%20s\n", "INDEX", "NAMA", "SINGKATAN", "NAMA", "JUMLAH_ANGGOTA");
	for (int i = 1; i <= length; i++) {
		printf("%10d%10d%20s%72s%20d\n", tabel[i]->index, tabel[i]->no_urut, tabel[i]->singkatan,
				tabel[i]->nama, tabel[i]->jumlah_anggota);
	}
}



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

////////////////////////////////////////////
/// 		LOGIKA		SORTIG			///
////////////////////////////////////////////


// BY NO URUT
int sorting_by_no_urut (struct anggota_dpr_t ***tabel_anggota, int length) {
	// RETURN value jika sorting berhasil / gagal
	int flag;
	flag = EXIT_SUCCESS;

	// ARRAY[] untuk disorting
	struct anggota_dpr_t **array = (*tabel_anggota);

	// SORTING HERE

	struct anggota_dpr_t tmp;

	for (int i = 0; i < length - 1; i++) {
		for (int j = 0; j < length - 1 - i; j++) {
			if (tabel_anggota[j].no_urut > tabel_anggota[j + 1].no_urut) {
				tmp = tabel_anggota[j];
				tabel_anggota[j] = tabel_anggota[j + 1];
				tabel_anggota[j + 1] = tmp;
			};
		};
	};
};
	return flag;
};

// BY INISIAL
int sorting_by_no_inisial (struct anggota_dpr_t ***tabel_anggota, int length) {
	// RETURN value jika sorting berhasil / gagal
	int flag;
	flag = EXIT_SUCCESS;

	// ARRAY[] untuk disorting
	struct anggota_dpr_t **array = (*tabel_anggota);

	int i, j;
        i = 1;
        while(i < length){
        	tabel_anggota = array[j];
                j = i - 1;
                while(j >= 0 && array[j]->nama > tabel_anggota){
                	array[j + 1] = array[j];
                        j--;
                };
                array[j + 1] = tabel_anggota;
                i++;
        };

	return flag;
};

// BY JUMLAH SUARA
int sorting_by_suara_sah (struct anggota_dpr_t ***tabel_anggota, int length) {
	// RETURN value jika sorting berhasil / gagal
	int flag;
	flag = EXIT_SUCCESS;

	// ARRAY[] untuk disorting
	struct anggota_dpr_t **array = (*tabel_anggota);

	// SORTING HERE

	return flag;
};




