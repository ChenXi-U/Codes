#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "crc.h"
#include "bcc.h"


int main() 
{
    // Example data to calculate CRC
    uint8_t data[] = {0x01,0x02,0x03,0x04};
    uint8_t data_len = sizeof(data) / sizeof(data[0]);
    uint8_t crc = 0x00; // Initial CRC value
    // Update the CRC with the data
    crc = crc8_bit(data, data_len, 0x07, 0x00, 0x00, true, true);
    // Print the calculated CRC value
    printf("CRC-8 (bit): 0x%02X\n", crc);
    
    crc = 0x00;
    // Update the CRC with the data using byte method
    crc = crc8_byte(data, data_len);
    // Print the calculated CRC value
    printf("CRC-8 (byte): 0x%02X\n", crc);

    crc = 0x00;
    // Update the CRC with the data using nibble method
    crc = crc8_nibbble(data, data_len);
    // Print the calculated CRC value
    printf("CRC-8 (nibble): 0x%02X\n", crc);


    crc = CRC_8(data, data_len);
    // Print the calculated CRC-8 value
    printf("CRC-8 (function): 0x%02X\n", crc);
    






    uint16_t crc16 = 0x0000; // Initial CRC-16 value
    
    // Update the CRC with the data using bit method for CRC-16
    crc16 = crc16_bit(data, data_len, 0x1021, 0xFFFF, 0x0000, true, false);
    // Print the calculated CRC-16 value
    printf("CRC-16 (bit): 0x%04X\n", crc16);
    
    crc16 = 0x00;
    // Update the CRC with the data using byte method for CRC-16
    crc16 = crc16_byte(data, data_len);
    // Print the calculated CRC-16 value
    printf("CRC-16 (byte): 0x%04X\n", crc16);

    crc16 = 0x00;
    // Update the CRC with the data using nibble method for CRC-16
    crc16 = crc16_nibbble(data, data_len);
    // Print the calculated CRC-16 value
    printf("CRC-16 (nibble): 0x%04X\n", crc16);


    crc16 = CRC_16_CCITT(data, data_len);
    // Print the calculated CRC-16 value using function
    printf("CRC-16 (function): 0x%04X\n", crc16);
    crc16 = CRC_16_CCITT_FALSE(data, data_len);
    // Print the calculated CRC-16 value using function
    printf("CRC-16 CCITT FALSE (function): 0x%04X\n", crc16);
    crc16 = CRC_16_USB(data, data_len);
    // Print the calculated CRC-16 value using function
    printf("CRC-16 USB (function): 0x%04X\n", crc16);
    
    crc16 = CRC_16_MODUSB(data, data_len);
    // Print the calculated CRC-16 MODUSB value using function
    printf("CRC-16 MODUSB (function): 0x%04X\n", crc16);




    uint32_t crc32 = 0x00000000; // Initial CRC-32 value



    crc32 = 0x00;
    // Update the CRC with the data using the crc_update function
    crc32 = crc32_byte(data, data_len);
    // Print the calculated CRC-32 value
    printf("CRC-32 (byte): 0x%08X\n", crc32);

    crc32 = 0x00;
    // Update the CRC with the data using the crc_update function
    crc32 = crc32_nibble(data, data_len);
    // Print the calculated CRC-32 value
    printf("CRC-32 (nibble): 0x%08X\n", crc32);

    crc32 = 0x00;
    // Update the CRC with the data using the crc_update function with custom parameters
    crc32 = crc32_bit(data, data_len, 0x04C11DB7, 0xFFFFFFFF, 0xFFFFFFFF, true, true);
    // Print the calculated CRC-32 value with custom parameters
    printf("CRC-32 (bit2): 0x%08X\n", crc32);

    crc32 = CRC_32(data, data_len);
    // Print the calculated CRC-32 value using function
    printf("CRC-32 (function): 0x%08X\n", crc32);
    crc32 = CRC_32_JAM(data, data_len);
    // Print the calculated CRC-32 JAM value using function
    printf("CRC-32 JAM (function): 0x%08X\n", crc32);

    crc32 = CRC_32_XFER(data, data_len);
    // Print the calculated CRC-32 XFER value using function
    printf("CRC-32 XFER (function): 0x%08X\n", crc32);

    unsigned char checksum = 0;
	
    int ret = funBccCreate(data, data_len, &checksum);
    if(0 == ret)
    {
		printf("Computed BCC Checksum: 0x%02X\n", checksum);
    }
    else
    {
		perror("funBccCreate err :");
    }
    
    printf("hello\n");


    return 0;
}