#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void print_binary(uint32_t data){
	printf("Binary: ");
    for (int i = 31; i >= 0; i--) {
        printf("%d", (data >> i) & 1);
    }
    printf("\n");	
}

int init_crc32_table(uint32_t* table, uint32_t poly){
	int i, j;
	uint32_t crc;

	for (i = 0; i < 256; i++){
		crc = i;
		for (j = 0; j < 8; j++){
			if (crc & 1){
				crc = crc >> 1 ^ poly;
			}else{
				crc = crc >> 1;
			}
		}
		table[i] = crc;
	}

	return 0;
}


uint32_t genX_formula(void){
	uint32_t genX = 0;
	int exp_list[] = {32, 26, 23, 22, 16, 12, 11, 10, 8, 7, 5, 4, 2, 1, 0};

	int i;
	int list_len = sizeof(exp_list)/sizeof(exp_list[0]);
	printf("list_len: %d\n", list_len);

	for (i = 0; i < list_len; i++){
		genX = genX | (1 << exp_list[i]);
	}

	return genX;
}

uint32_t genX_formula_revert(uint32_t genX){

	uint32_t genX_r = 0;
	int i;

	for (i = 0 ; i < 32; i++){
		if (genX & (1 << i)){
			genX_r = genX_r | (1 << (31 - i));
		}
	}

	return genX_r;
}

uint32_t crc32(const uint8_t* data, int len, uint32_t poly){
	uint32_t crc = 0xFFFFFFFF;
	int i, j;

	for(i = 0; i < len; i++){
		crc ^= data[i];
		for (j = 0 ; j < 8; j++){
			if (crc & 1){
				crc = (crc >> 1) ^ poly;
			}else{
				crc = crc >> 1;
			}
		}
		printf("data:[%d], crc:[0x%8X]\n", data[i], crc);
	}

	return crc ^ 0xFFFFFFFF; // revert
}

uint32_t crc32_by_table(const uint8_t* data, int len, uint32_t *table){
	uint32_t crc = 0xFFFFFFFF;
	int i;
	uint8_t idx;

	for (i = 0 ; i < len; i++){
		idx = (crc ^ data[i]) & 0xFF;
		crc = table[idx] ^ (crc >> 8);
	}

	return crc ^ 0xFFFFFFFF;
}


int main(int argc, char const *argv[])
{
	/* code */

	uint32_t genX; 
	uint32_t genX_r;
	uint8_t test_data[] = "ABC";
	int data_len = sizeof(test_data)/sizeof(test_data[0]) - 1;
	uint32_t crc_result;
	uint32_t crc_table[256];
	uint32_t crc_result_table;

	genX = genX_formula();
	genX_r = genX_formula_revert(genX);
	printf("genX: 0x%8X\n", genX);
	print_binary(genX);
	printf("genX_r: 0x%8X\n", genX_r);
	print_binary(genX_r);
	printf("data_len:%d\n", data_len);
	crc_result = crc32(test_data, data_len, genX_r);
	printf("crc: 0x%8X\n", crc_result);

	init_crc32_table(crc_table, genX_r);
	printf("crc_table[1]:0x%8X, crc_table[2]:0x%8X\n", crc_table[1], crc_table[2]);

	crc_result_table = crc32_by_table(test_data, data_len, crc_table);
	printf("crc32_by_table: 0x%8X\n", crc_result_table);

	return 0;
}

