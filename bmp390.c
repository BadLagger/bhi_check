#include "bmp390.h"
#include <math.h>

bmp390_handle_t bmp390_init(uint16_t t1, uint16_t t2, int8_t t3)
{
	struct bmp390_handle_s ret = {
		.t1 = t1,
		.t2 = t2,
		.t3 = t3,
	};

	return ret;
}

int64_t bmp390_compensate_temperature(bmp390_handle_t* handle, uint32_t data)
{
    uint64_t partial_data1;
    uint64_t partial_data2;
    uint64_t partial_data3;
    int64_t partial_data4;
    int64_t partial_data5;
    int64_t partial_data6;
    int64_t comp_temp;

    /* calculate compensate temperature */
    partial_data1 = (uint64_t)(data - (256 * (uint64_t)(handle->t1)));
    partial_data2 = (uint64_t)(handle->t2 * partial_data1);
    partial_data3 = (uint64_t)(partial_data1 * partial_data1);
    partial_data4 = (int64_t)(((int64_t)partial_data3) * ((int64_t)handle->t3));
    partial_data5 = ((int64_t)(((int64_t)partial_data2) * 262144) + (int64_t)partial_data4);
    partial_data6 = (int64_t)(((int64_t)partial_data5) / 4294967296U);
    comp_temp = (int64_t)((partial_data6 * 25) / 16384);

    return comp_temp;
}

float bmp390_compensate_temperature_f(bmp390_handle_t* handle, uint32_t data)
{
    double partial_data1;
    double partial_data2;

    double par_t1 = handle->t1 / pow(2, -8);
    double par_t2 = handle->t2 / pow(2, 30);
    double par_t3 = handle->t3 / pow(2, 48);

    partial_data1 = (double)(data - par_t1);
    partial_data2 = (double)(partial_data1 * par_t2);

    return (partial_data2 + (partial_data1 * partial_data1) * par_t3);
}

/* Attribute TEMPERATURE */
#define DO_DIV_10(x, n) {			\
        int i;					\
        int sign=(x > 0) ? 0 : 1;               \
        if(sign)                                \
            x *= (-1);				\
        for ( i=0; i < n; ++i ) {               \
            x /= 10;                      \
        }                                       \
        if(sign)                                \
            x *= (-1);				\
    }

int64_t bmp390_compensate_temperature_orionm(bmp390_handle_t* handle, uint32_t data)
{
    int64_t partial_data1;
    int64_t partial_data2;
    int64_t partial_data3;

    int64_t result = 0;

    int64_t par_t1 = (int64_t)handle->t1 * ((int32_t)1 << 8);
    int64_t par_t2 = (int64_t)handle->t2 * 931322;
    int64_t par_t3 = (int64_t)handle->t3 * 4;

    partial_data1 = (int64_t)data - par_t1;
    partial_data2 = partial_data1 * par_t2;
    partial_data3 = partial_data1 * partial_data1 * par_t3;

    result = partial_data2 + partial_data3;

    DO_DIV_10(result, 13);
    return result;
}