/**
 * 
 * 
 * 
 */

#ifndef __MODULE__H_
#define __MODULE__H_

/**
 * OUTPUT
 * "NO_URUT", "NAMA", "PROVINSI", "PARTAI"
 * 
 * PARAMETER
 * void show_general (tabel anggota dpr, panjang tabel, index mulai, panjang tampilan per page)
 * 
 * 
*/
void show_general (struct anggota_dpr_t**, int, int, int);

/**
 * OUTPUT
 * "NO_URUT", "NAMA", "UMUR" "JENIS_KELAMIN", "SUARA_SAH"
 *  
 * PARAMETER
 * void show_general (tabel anggota dpr, panjang tabel, index mulai, panjang tampilan per page)
 * 
 * 
*/
void show_tabel (struct anggota_dpr_t**, int, int, int);

/**
 * OUTPUT
 * "NO_PROVINSI", "NAMA", "JUMLAH_ANGGOTA"
 *  
 * PARAMETER
 * void showall_provinsi (tabel provinsi, panjang tabel)
 * 
 * 
*/
void showall_provinsi (struct provinsi_t**, int);

/**
 * OUTPUT
 * "INDEX", "NAMA", "SINGKATAN", "NAMA", "JUMLAH_ANGGOTA"
 *  
 * PARAMETER
 * void showall_partai (tabel partai, panjang tabel) {
 * 
 * 
*/
void showall_partai (struct partai_t**, int);


int sort_by_no_urut (const void*, const void*);
int sort_by_inisial (const void*, const void*);
int sort_by_suara_sah (const void*, const void*);

/**
 * OUTPUT
 * PRINT ARRAY tabel anggota
 *  
 * PARAMETER
 * void showall_partai (tabel anggota, panjang tabel)
 * 
 * 
*/
int sorting_by_no_urut (struct anggota_dpr_t***, int);

/**
 * OUTPUT
 * PRINT ARRAY tabel anggota
 *  
 * PARAMETER
 * void showall_partai (tabel anggota, panjang tabel)
 * 
 * 
*/
int sorting_by_inisial (struct anggota_dpr_t***, int);

/**
 * OUTPUT
 * PRINT ARRAY tabel anggota
 *  
 * PARAMETER
 * void showall_partai (tabel anggota, panjang tabel)
 * 
 * 
*/
int sorting_by_suara_sah (struct anggota_dpr_t***, int);




#endif /* __MODULE__H_ */

