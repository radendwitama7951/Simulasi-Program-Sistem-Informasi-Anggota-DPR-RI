/* All Object are Here
 *
 *
 *
 *
 * */

#ifndef __OBJECT__H__
#define __OBJECT__H__

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
	int deskripsi_komisi;

};


#endif /* __OBJECT__H__ */
