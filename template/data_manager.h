/* Modul untuk membangun struktur data Graph berdasarkan File .csv
 *
 * */

#ifndef __DATA_MANAGER__H_
#define __DATA_MANAGER__H_
#define DIRPATH "./data"

#define SMALLSTRING 32
#define MEDIUMSTRING 128
#define LONGSTRING 1024

struct anggota_dpr_t {
	int no_urut;
	char nama[MEDIUMSTRING];
	int umur;
	char jenis_kelamin;
	int suara_sah;


	struct partai_t *partai;
	struct provinsi_t *provinsi;
	struct komisi_t *komisi;
};

struct partai_t {
	int index;
	int no_urut;
	char nama[100];
	char singkatan[10];
	int jumlah_anggota;

	struct anggota_dpr_t **anggota;
};

struct provinsi_t {
	int no_provinsi;
	char nama[100];
	int jumlah_anggota;

	struct anggota_dpr_t **anggota;
};

struct komisi_t {
	int nomor_komisi;
	char deskripsi_komisi[100];

	struct anggota_dpr_t **anggota;

};

/**/
// MODULE 

// CREATE table anggota
int create_tabel_anggota (struct anggota_dpr_t***);
int create_tabel_provinsi (struct provinsi_t***);
int create_tabel_partai (struct partai_t***);
int create_relasi (struct anggota_dpr_t**, struct provinsi_t**, struct partai_t**, int);
void **new_array (size_t, int);
void array_cpy (struct anggota_dpr_t***, struct anggota_dpr_t***, int);







#endif /* __DATA_MANAGER__H_ */
