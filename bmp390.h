#ifndef __BMP390_H__
#define __BMP390_H__

#include <stdint.h>

typedef struct bmp390_handle_s {
    uint8_t iic_addr;                                                                   /**< iic device address */
    uint8_t buf[512 + 1];                                                               /**< inner buffer */
    uint8_t(*iic_init)(void);                                                          /**< point to an iic_init function address */
    uint8_t(*iic_deinit)(void);                                                        /**< point to an iic_deinit function address */
    uint8_t(*iic_read)(uint8_t addr, uint8_t reg, uint8_t* buf, uint16_t len);         /**< point to an iic_read function address */
    uint8_t(*iic_write)(uint8_t addr, uint8_t reg, uint8_t* buf, uint16_t len);        /**< point to an iic_write function address */
    uint8_t(*spi_init)(void);                                                          /**< point to a spi_init function address */
    uint8_t(*spi_deinit)(void);                                                        /**< point to a spi_deinit function address */
    uint8_t(*spi_read)(uint8_t reg, uint8_t* buf, uint16_t len);                       /**< point to a spi_read function address */
    uint8_t(*spi_write)(uint8_t reg, uint8_t* buf, uint16_t len);                      /**< point to a spi_write function address */
    void (*receive_callback)(uint8_t type);                                             /**< point to a receive_callback function address */
    void (*delay_ms)(uint32_t ms);                                                      /**< point to a delay_ms function address */
    void (*debug_print)(const char* const fmt, ...);                                    /**< point to a debug_print function address */
    uint8_t inited;                                                                     /**< inited flag */
    uint8_t iic_spi;                                                                    /**< iic spi interface */
    uint16_t t1;                                                                        /**< t1 register */
    uint16_t t2;                                                                        /**< t2 register */
    int8_t t3;                                                                          /**< t3 register */
    int16_t p1;                                                                         /**< p1 register */
    int16_t p2;                                                                         /**< p2 register */
    int8_t p3;                                                                          /**< p3 register */
    int8_t p4;                                                                          /**< p4 register */
    uint16_t p5;                                                                        /**< p5 register */
    uint16_t p6;                                                                        /**< p6 register */
    int8_t p7;                                                                          /**< p7 register */
    int8_t p8;                                                                          /**< p8 register */
    int16_t p9;                                                                         /**< p9 register */
    int8_t p10;                                                                         /**< p10 register */
    int8_t p11;                                                                         /**< p11 register */
    int64_t t_fine;
} bmp390_handle_t;

extern bmp390_handle_t bmp390_init(uint16_t t1, uint16_t t2, int8_t t3);
extern int64_t bmp390_compensate_temperature(bmp390_handle_t* handle, uint32_t data);
extern float bmp390_compensate_temperature_f(bmp390_handle_t* handle, uint32_t data);
extern int64_t bmp390_compensate_temperature_orionm(bmp390_handle_t* handle, uint32_t data);


#endif // !__BMP390_H__
