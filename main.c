#include <stdio.h>
#include "bmp390.h"

int main() {
	bmp390_handle_t bmp390_my = bmp390_init(0xE0, 0x98, 0xF9);
	int64_t result = 0;
	float result_f = .0;
	int64_t result_orionm = 0;

	printf("Hello BHI checker\n");

	result = bmp390_compensate_temperature(&bmp390_my, -9782016);
	result_f = bmp390_compensate_temperature_f(&bmp390_my, -9782016);
	result_orionm = bmp390_compensate_temperature_orionm(&bmp390_my, -9782016);

	printf("TTemp result: %lld\n", result);
	printf("TTemp result f: %f\n", result_f);
	printf("TTemp result orionm: %lld\n", result_orionm);

	getchar();
	return 0;
}