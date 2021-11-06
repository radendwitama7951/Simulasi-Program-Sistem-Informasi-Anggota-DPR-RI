/* Main
 * by Kelompok 3 PSD 2021
 * 6/10/2021
 *
 * */

#include <stdio.h>
#include <stdlib.h>

struct anggota_t {
	 int no_urut;
	 char nama[100];
	 int umur;
	 char jenis_kelamin;


	 struct partai_t *parpol;
	 struct provinsi_t *dapil;
	 struct komisi_t *komisi;

};

struct partai_t {
	char singkatan_parpol[10];
	char nama_parpol[100];
	char gambar_parpol[100];
};

struct provinsi_t {
	int nomor_provinsi;
	char nama_provinsi[100];

};

struct komisi_t {
	int nomor_komisi;
	char deskripsi_komisi[100];

};





int main (void) {
	struct partai_t pdip = {
		.singkatan_parpol = "pdip",
		.nama_parpol = "Partai Demokrasi Indonesia Perjuangan",
		.gambar_parpol = "banteng"
	};
	struct provinsi_t jkt = {
		.nomor_provinsi = 18,
		.nama_provinsi = "Jakarta"
	
	};
	struct komisi_t satu = {
		.nomor_komisi = 1,
		.deskripsi_komisi = "Legislasi dan Pemilu"
	};
	struct anggota_t anggota_1 = {
		.no_urut = 18,
		.nama = "Puan Maharani",
		.umur = 150,
		.jenis_kelamin = 'p',
		.parpol = &pdip,
		.dapil = &jkt,
		.komisi = &satu

	};
	struct anggota_t anggota_2 = {
		.no_urut = 69,
		.nama = "Fadli Zon",
		.umur = 900,
		.jenis_kelamin = 'l',
		.parpol = &pdip,
		.dapil = &jkt,
		.komisi = &satu

	};


	printf("No : %d\nNama : %s\nUmur : %d\nJenis Kelamin : %c\nParpol : %s\nDapil : %s\nKomisi : %d\n\n", anggota_1.no_urut, anggota_1.nama, anggota_1.umur, anggota_1.jenis_kelamin, anggota_1.parpol->gambar_parpol, anggota_1.dapil->nama_provinsi, anggota_1.komisi->nomor_komisi);


	printf("No : %d\nNama : %s\nUmur : %d\nJenis Kelamin : %c\nParpol : %s\nDapil : %s\nKomisi : %d\n\n", anggota_2.no_urut, anggota_2.nama, anggota_2.umur, anggota_2.jenis_kelamin, anggota_2.parpol->gambar_parpol, anggota_2.dapil->nama_provinsi, anggota_2.komisi->nomor_komisi);

	system("pause");

	return 0;
}
