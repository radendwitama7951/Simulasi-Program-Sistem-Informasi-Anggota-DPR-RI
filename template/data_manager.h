/* Modul untuk membangun struktur data Graph berdasarkan File .csv
 *
 * */

#define DIRPATH "./data"
#define SMALLSTRING 32
#define MEDIUMSTRING 128
#define LONGSTRING 1024
#ifndef __GRAPH_MODULE__H_
#define __GRAPH_MODULE__H_
struct anggota_dpr_t {
	int no_urut;
	char nama[MEDIUMSTRING];
	int umur;
	char jenis_kelamin;
	int suara_sah;


	struct partai_t *partai;
	struct provinsi_t *dapil;
	struct komisi_t *komisi;

};

struct partai_t {
	int no_partai;
	char singkatan_parpol[10];
	char nama_parpol[100];
	char gambar_parpol[100];
};

struct provinsi_t {
	int no_provinsi;
	int nomor_provinsi;
	char nama_provinsi[100];
};

struct komisi_t {
	int nomor_komisi;
	char deskripsi_komisi[100];

};

/**/
// MODULE 

// CREATE table anggota
int create_tabel_anggota (struct anggota_dpr_t***);
void **new_array (size_t, int);
void show_tabel (struct anggota_dpr_t**, int start, int length);







#endif /* __GRAPH_MODULE__H_ */
