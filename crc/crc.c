#include "crc.h"


uint8_t crc8_byte(const uint8_t* data, uint32_t data_len)
{
    const uint8_t *d = (const uint8_t *)data;
    uint8_t tbl_idx;
    uint8_t crc = 0x00; // Initial CRC value
    while (data_len--) {
        tbl_idx = crc ^ *d;
        crc = (crc8_byte_table[tbl_idx]) & 0xff;
        d++;
    }
    return crc & 0xff;
}

uint8_t crc8_nibbble(const uint8_t* data, uint32_t data_len)
{
    const uint8_t *d = (const uint8_t *)data;
    uint8_t tbl_idx;
    uint8_t crc = 0x00; // Initial CRC value
    while (data_len--) {
        tbl_idx =  (crc >> 4) ^ (*d >> 4);
        crc = (crc8_nibble_table[tbl_idx & 0x0f]) ^ (crc << 4);
        tbl_idx = (crc >> 4) ^ (*d >> 0);
        crc = (crc8_nibble_table[tbl_idx & 0x0f]) ^ (crc << 4);
        d++;
    }
    return crc & 0xff;
}

uint16_t crc16_byte(const uint8_t* data, uint32_t data_len)
{
    const uint8_t *d = (const uint8_t *)data;
    uint32_t crc = 0xffff; // Initial CRC value
    uint16_t tbl_idx;

    while (data_len--) {
        tbl_idx = ((crc >> 8) ^ *d) & 0xFF;  // 计算查表索引
        crc = (crc16_byte_table[tbl_idx] ^ (crc << 8)) & 0xFFFF;  // 直接查表计算
        d++;
    }
    return crc & 0xffff;
}
 
uint16_t crc16_nibbble(const uint8_t* data, uint32_t data_len)
{
    const unsigned char *d = (const unsigned char *)data;
    uint16_t tbl_idx;
    uint16_t  crc = 0xffff;

    while (data_len--) {
        // 处理字节的高4位
        tbl_idx = (crc >> 12) ^ (*d >> 4);
        crc = (crc16_nibble_table[tbl_idx & 0x0F] ^ (crc << 4)) & 0xFFFF;
        
        // 处理字节的低4位
        tbl_idx = (crc >> 12) ^ (*d & 0x0F);
        crc = (crc16_nibble_table[tbl_idx & 0x0F] ^ (crc << 4)) & 0xFFFF;
        
        d++;
    }
    return crc & 0xFFFF;
}

uint32_t crc32_byte(const uint8_t* data, uint32_t data_len)
{
    const uint8_t *d = (const uint8_t *)data;
    uint32_t tbl_idx;
    uint32_t crc = 0xffffffff;
    while (data_len--) {
        tbl_idx = (crc ^ *d) & 0xff;

        crc = (crc32_byte_table[tbl_idx] ^ (crc >> 8)) & 0xffffffff;
        d++;
    }
    return crc & 0xffffffff;
}

uint32_t crc32_nibble(const uint8_t* data, uint32_t data_len)
{
    const uint8_t *d = (const uint8_t *)data;
    uint8_t tbl_idx;
    uint32_t crc = 0xffffffff; // Initial CRC value    

    while (data_len--) {
        tbl_idx = crc ^ *d;
        crc = crc32_nibble_table[tbl_idx & 0x0f] ^ (crc >> 4); // 直接访问数组
        tbl_idx = crc ^ (*d >> 4);
        crc = crc32_nibble_table[tbl_idx & 0x0f] ^ (crc >> 4); // 直接访问数组
        d++;
    }
    return crc & 0xffffffff;
}

uint32_t crc_reflect(uint32_t data, uint32_t data_len)
{
    uint32_t i;
    uint32_t ret;

    ret = data & 0x01;
    for (i = 1; i < data_len; i++) {
        data >>= 1;
        ret = (ret << 1) | (data & 0x01);
    }
    return ret;
}

uint8_t crc8_bit(const uint8_t* data, uint32_t data_len, uint32_t poly, uint32_t init, uint32_t xor_out, bool reflect_in, bool reflect_out)
{
    uint8_t crc = init;
    const uint8_t *d = (const uint8_t *)data;
    uint8_t i, c;
    uint8_t bit;

    while (data_len--) {
        c = *d++;
        if (reflect_in) {
            c = crc_reflect(c, 8);
        }
        for (i = 0x80; i > 0; i >>= 1) {
            bit = (crc & 0x80) ^ ((c & i) ? 0x80 : 0);
            crc <<= 1;
            if (bit) {
                crc ^= poly;
            }
        }
        crc &= 0xff;
    }

    if (reflect_out) {
        crc = crc_reflect(crc, 8);
    }

    crc ^= xor_out;

    return crc & 0xff;
}

uint16_t crc16_bit(const uint8_t* data, uint32_t data_len, uint32_t poly, uint32_t init, uint32_t xor_out, bool reflect_in, bool reflect_out)
{
    uint16_t crc = init;
    const uint8_t *d = (const uint8_t *)data;
    uint8_t i, c;
    uint16_t bit;

    while (data_len--) {
        c = *d++;
        if (reflect_in) {
            c = crc_reflect(c, 8);
        }
        for (i = 0x80; i > 0; i >>= 1) {
            bit = (crc & 0x8000) ^ ((c & i) ? 0x8000 : 0);
            crc <<= 1;
            if (bit) {
                crc ^= poly;
            }
        }
        crc &= 0xffff;
    }

    if (reflect_out) {
        crc = crc_reflect(crc, 16);
    }

    crc ^= xor_out;

    return crc & 0xffff;

}

uint32_t crc32_bit(const uint8_t* data, uint32_t data_len, uint32_t poly, uint32_t init, uint32_t xor_out, bool reflect_in, bool reflect_out)
{
    uint32_t crc = init;
    const uint8_t *d = (const uint8_t *)data;
    uint8_t i, c;
    uint32_t bit;
 
    while (data_len--) {
        c = *d++;
        if (!reflect_in) {
            c = crc_reflect(c, 8);
        }   
        for (i = 0x01; i & 0xff; i <<= 1) {
            bit = (crc & 0x80000000) ^ ((c & i) ? 0x80000000 : 0);
            crc <<= 1;
            if (bit) {
                crc ^= 0x04c11db7;
            }
        }
        crc &= 0xffffffff;
    }

    if (reflect_out) {
        crc = crc_reflect(crc, 32);
    }

    crc ^= xor_out;

    return crc & 0xffffffff;
}

uint8_t CRC_8(const uint8_t* data, uint32_t data_len)
{
    return crc8_bit(data, data_len, 0x07, 0x00, 0x00, false, false);
}

uint16_t CRC_16_CCITT(const uint8_t* data, uint32_t data_len)
{
    return crc16_bit(data, data_len, 0x1021, 0x0000, 0x0000, true, true);
}

uint16_t CRC_16_CCITT_FALSE(const uint8_t* data, uint32_t data_len)
{
    return crc16_bit(data, data_len, 0x1021, 0xFFFF, 0x0000, false, false);
}

uint16_t CRC_16_MODUSB(const uint8_t* data, uint32_t data_len)
{
    return crc16_bit(data, data_len, 0x8005, 0xFFFF, 0x0000, true, true);
}

uint16_t CRC_16_USB(const uint8_t* data, uint32_t data_len)
{
    return crc16_bit(data, data_len, 0x8005, 0xFFFF, 0xFFFF, true, true);
}

uint32_t CRC_32(const uint8_t* data, uint32_t data_len)
{
    return crc32_bit(data, data_len, 0x04C11DB7, 0xFFFFFFFF, 0xFFFFFFFF, true, true);
}

uint32_t CRC_32_JAM(const uint8_t* data, uint32_t data_len)
{
    return crc32_bit(data, data_len, 0x04C11DB7, 0xFFFFFFFF, 0x00000000, true, true);
}

uint32_t CRC_32_XFER(const uint8_t* data, uint32_t data_len)
{
    return crc32_bit(data, data_len, 0x000000AF, 0x00000000, 0x00000000, false, false);
}

