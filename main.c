#include <stdio.h>
#include <unistd.h>
#include "bmp390.h"

int main() {
        uint16_t t1 = 0x6CE0;
        uint16_t t2 = 0x4D98;
        int8_t   t3 = (int8_t)0xF9;

        uint32_t raw_temp = 0x0070D100;

        int count = 100;
        
	bmp390_handle_t bmp390_my = bmp390_init(t1, t2, t3);
	int64_t result = 0;
	float result_f = .0;
	int64_t result_orionm = 0;

	printf("Hello BHI checker\n");

	/*result = bmp390_compensate_temperature(&bmp390_my, raw_temp);
	result_f = bmp390_compensate_temperature_f(&bmp390_my, raw_temp);
	result_orionm = bmp390_compensate_temperature_orionm(&bmp390_my, raw_temp);

	printf("TTemp result: %ld\n", result);
	printf("TTemp result f: %f\n", result_f);
	printf("TTemp result orionm: %ld\n", result_orionm);*/

        while (count++ > 0) {
            result = bmp390_compensate_temperature(&bmp390_my, raw_temp);
            result_f = bmp390_compensate_temperature_f(&bmp390_my, raw_temp);
            result_orionm = bmp390_compensate_temperature_orionm(&bmp390_my, raw_temp);
            printf("RAW TEMP: 0x%08X\n", raw_temp);
            printf("TTemp result: %ld\n", result);
            printf("TTemp result f: %f\n", result_f);
            printf("TTemp result orionm: %ld\n\n", result_orionm);
            raw_temp -= 100000;
            sleep(1);
        }

	getchar();
	return 0;
}
