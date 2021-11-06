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
#include "./template/modules.h"


int sorting_menu (struct anggota_dpr_t ***tabel, int length) {
	struct anggota_dpr_t **tmp_tabel = (*tabel);
	int pilihan, running;
	running = 1;

	// Opsi Looping || Akan berjalan terus selama user tidak keluar ke main menu
	do {
		// Opsi Sorting
		printf("Menu:\n");
		printf("\t1. Sort by No Urut\n\t2. Sort by Inisial\n\t3. Sort by jumlah pemilih\n\n\t0. Keluar\n\n");
		pilihan = get_range(0, 4, "Pilihan anda : ");

		
		// PEMANGGILAN FUNGSI SORTING BY NO_URUT				
		switch (pilihan) {
				case 1:
					// Sorting berdasarkan nomor urut anggota
					qsort((tmp_tabel), length, sizeof(struct anggota_dpr_t*), sort_by_no_urut);
					//sorting_by_no_urut(&tmp_tabel, 575);

					// Show tabel setelah di sorting
					show_tabel(tmp_tabel, length, 0, 100);

					break;
				case 2:
					// Sorting berdasarkan inisial nama anggota
					qsort((tmp_tabel), length, sizeof(struct anggota_dpr_t*), sort_by_inisial);
					//sorting_by_nama(&tmp_tabel, 575);

					// Show tabel setelah di sorting
					show_tabel(tmp_tabel, length, 0, 100);

					break;
				case 3:
					// Sorting berdasarkan jumlah suara sah anggota
					qsort((tmp_tabel), length, sizeof(struct anggota_dpr_t*), sort_by_suara_sah);
					//sorting_by_suara_sah(&tmp_tabel, 575);

					// Show tabel setelah di sorting
					show_tabel(tmp_tabel, length, 0, 100);

					break;

				case 0:
					running = 0;
					break;
				default:
					print_n_pause("Undefined");
					return EXIT_FAILURE;
			
		};

	} while (running);

		return 1;

};

// Menu opsi provinsi || return value = provinsi spesifik
struct provinsi_t *provinsi_menu (struct provinsi_t **tabel_provinsi) {
	int pilihan;
	printf("Menu:\n");
	showall_provinsi(tabel_provinsi, 34);
	printf("\n\n");
	pilihan = get_range(1, 35, "Pilihan anda : ");
	return tabel_provinsi[pilihan];
};

// Menu opsi partai || return value = partai spesifik
struct partai_t *partai_menu (struct partai_t **tabel_partai) {
	int pilihan;
	printf("Menu:\n");
	showall_partai(tabel_partai, 9);
	printf("\n\n");
	pilihan = get_range(1, 10, "Pilihan anda : ");
	return tabel_partai[pilihan];
};

// Main Menu || Memilih kategori anggota
int main_menu () {
	int pilihan;
	printf("Selamat datang di program Sistem Informasi Data Anggota DPR RI\n\n");
	printf("Menu:\n");
	printf("\t1. Lihat semua anggota DPR\n\t2. Lihat berdasarkan Provinsi\n\t3. Lihat berdasarkan Partai Politik\n\n\t0. Keluar\n\n");
	pilihan = get_range(0, 4, "Pilihan anda : ");

	return pilihan;
};



/////////////////////////
/*       MAIN          */
////////////////////////
int main (void) {

	// Variabel untuk main looping
	int pilihan, running;

	// Variabel tabel
	struct anggota_dpr_t **tabel_anggota, **tmp_tabel;
	struct provinsi_t **tabel_provinsi, *tmp_provinsi;
	struct partai_t **tabel_partai, *tmp_partai;

	// Tabel creation
	if (create_tabel_anggota(&tabel_anggota) ||
		create_tabel_provinsi(&tabel_provinsi) || 
		create_tabel_partai(&tabel_partai) ||
		create_relasi(tabel_anggota, tabel_provinsi, tabel_partai,1)
		) {
		print_n_pause("Gagal membuat tabel !");	
		return EXIT_FAILURE;
	} else {
		show_general(tabel_anggota, 576, 1, 600);
		print_n_pause("Membuat tabel berhasil !");
		clrscr;
	};
	

	// Working Table
	tmp_tabel = (struct anggota_dpr_t**) new_array(sizeof(struct anggota_dpr_t*), 575);
	array_cpy(&tmp_tabel, &tabel_anggota, 575);

	// Main Looping
	do {
		// Running paramater
		running = 1;

		// Clrscr = clear screen
		clrscr;

		// User Input main menu
		pilihan = main_menu();
		clrscr;

		// Opsi Pengelompokan
		switch(pilihan) {
			// Sort semua
			case 1 :
				// Show tabel seluruh anggota
				show_tabel(tmp_tabel, 575, 0, 100);
				
				// User input metode sorting
				sorting_menu(&tmp_tabel, 575);
				break;

			// Sort berdasarkan provinsi
			case 2 :
				// Show tabel provinsi && select provinsi pilihan
				tmp_provinsi = provinsi_menu(tabel_provinsi);

				// Print nama provinsi pilihan
				printf("\nPROVINSI %s\n\n", tmp_provinsi->nama);

				// Show tabel anggota berdasarkan provinsi pilihan
				show_tabel(tmp_provinsi->anggota, tmp_provinsi->jumlah_anggota, 0, 100);

				// User input metode sorting
				sorting_menu(&tmp_provinsi->anggota, tmp_provinsi->jumlah_anggota);
				break;

			// Sort berdasarkan partai
			case 3 :
				// Show tabel partai && select partai pilihan
				tmp_partai = partai_menu(tabel_partai);

				// Print nama partai pilihan
				printf("\nPARTAI %s\n\n", tmp_partai->nama);

				// Show tabel anggota berdasarkan provinsi pilihan
				show_tabel(tmp_partai->anggota, tmp_partai->jumlah_anggota, 0, 100);

				// User input metode sorting
				sorting_menu(&tmp_partai->anggota, tmp_partai->jumlah_anggota);
				break;

			// Exit
			case 0 :
				running = 0;
				print_n_pause("Terima kasih telah mencoba :)");
				break;
			default :
				print_n_pause("Undefined !");
				exit(EXIT_FAILURE);
		}

	} while (running);

	


	return 0;
}
