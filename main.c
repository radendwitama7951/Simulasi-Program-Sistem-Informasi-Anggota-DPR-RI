/* Program Simulasi Sistem Informasi DPR RI
 * by Kelompok 3
 *
 *
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "./template/utilitas.h"
#include "./template/data_manager.h"

int sort_by_no_urut (const void* a, const void* b) {
	struct anggota_dpr_t *object_a = *(struct anggota_dpr_t**) a;
	struct anggota_dpr_t *object_b = *(struct anggota_dpr_t**) b;


		 
	if (object_a->no_urut < object_b->no_urut) return -1;
	if (object_a->no_urut > object_b->no_urut) return 1;
	return 0;
}

int sort_by_inisial (const void* a, const void* b) {
	struct anggota_dpr_t *object_a = *(struct anggota_dpr_t**) a;
	struct anggota_dpr_t *object_b = *(struct anggota_dpr_t**) b;
		 
	if (tolower(object_a->nama[0]) < tolower(object_b->nama[0])) return -1;
	if (tolower(object_a->nama[0]) > tolower(object_b->nama[0])) return 1;
	return 0;
}

void array_cpy (struct anggota_dpr_t ***dest, struct anggota_dpr_t ***src, int length) {
	for (int i = 1, k = 0; i <= length; i++) {
		(*dest)[k] = (*src)[i];
		k++;
	}


}

int main_menu () {
	printf("Menu:\n");
	printf("\t1. Sort by No Urut\n\t2. Sort by Inisial\n\n\t0. Keluar\n\n");
	return get_range(0, 3, "Pilihan anda : ");
}


int main (void) {
	int pilihan, running;
	struct anggota_dpr_t **tabel_anggota, **tmp_tabel;
	if (create_tabel_anggota(&tabel_anggota)) {
		print_n_pause("Gagal membuat tabel !");	
		return EXIT_FAILURE;
	} else {
		show_tabel(tabel_anggota, 575);
		print_n_pause("\n\ndone.\n\n");
	
	};

	tmp_tabel = (struct anggota_dpr_t**) new_array(sizeof(struct anggota_dpr_t*), 574);
	array_cpy(&tmp_tabel, &tabel_anggota, 575);

	do {
		clrscr;
		pilihan = main_menu();
		switch (pilihan) {
			case 1:
				qsort((tmp_tabel), 575, sizeof(struct anggota_dpr_t*), sort_by_no_urut);				
				show_tabel(tmp_tabel, 574);
				print_n_pause("\n\ndone.\n\n");

				break;
			case 2:
				qsort((tmp_tabel), 575, sizeof(struct anggota_dpr_t*), sort_by_inisial);
				show_tabel(tmp_tabel, 574);
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
