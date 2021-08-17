
#ifndef __CRC_16_H__
#define __CRC_16_H__

#include <stdint.h>

uint16_t crc_16( const unsigned char *input_str, size_t num_bytes );

uint16_t crc_modbus( const unsigned char *input_str, size_t num_bytes );

uint16_t update_crc_16( uint16_t crc, unsigned char c );

#endif
