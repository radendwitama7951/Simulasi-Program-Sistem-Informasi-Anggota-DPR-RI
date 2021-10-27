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
	struct partai_t himpunan_partai[10];
	struct provinsi_t himpunan_provinsi[33];
	struct komisi_t himpunan_komisi[11];
	struct anggota_t himpunan_anggota[165];

	himpunan_partai[0].singkatan_parpol = "pdip",
		.nama_parpol = "Partai Demokrasi Indonesia Perjuangan",
		.gambar_parpol = "banteng"
	};
	himpunan_provinsi[18] = {
		.nomor_provinsi = 18,
		.nama_provinsi = "Jakarta"
	
	};
	himpunan_komisi[0] = {
		.nomor_komisi = 1,
		.deskripsi_komisi = "Legislasi dan Pemilu"
	};

	
	himpunan_anggota[0] = {
		.no_urut = 18,
		.nama = "Puan Maharani",
		.umur = 150,
		.jenis_kelamin = 'p',
		.parpol = &himpunan_partai[0],
		.dapil = &himpunan_provinsi[18],
		.komisi = &himpunan_komisi[0]


	};
	himpunan_anggota[1] = {
		.no_urut = 69,
		.nama = "Fadli Zon",
		.umur = 900,
		.jenis_kelamin = 'l',
		.parpol = &himpunan_partai[0],
		.dapil = &himpunan_provinsi[18],
		.komisi = &himpunan_komisi[0]

	};


	printf("No : %d\nNama : %s\nUmur : %d\nJenis Kelamin : %c\nParpol : %s\nDapil : %s\nKomisi : %d\n\n", himpunan_anggota[1].no_urut, himpunan_anggota[1].nama, himpunan_anggota[0].umur, himpunan_anggota[0].jenis_kelamin, himpunan_anggota[0].parpol->gambar_parpol, himpunan_anggota[0].dapil->nama_provinsi, himpunan_anggota[0].komisi->nomor_komisi);


	printf("No : %d\nNama : %s\nUmur : %d\nJenis Kelamin : %c\nParpol : %s\nDapil : %s\nKomisi : %d\n\n", himpunan_anggota[1].no_urut, himpunan_anggota[1].nama, himpunan_anggota[1].umur, himpunan_anggota[1].jenis_kelamin, himpunan_anggota[1].parpol->gambar_parpol, himpunan_anggota[1].dapil->nama_provinsi, himpunan_anggota[1].komisi->nomor_komisi);

	system("pause");

	return 0;
}
