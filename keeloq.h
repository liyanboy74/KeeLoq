#ifndef __keeloq_h__
#define __keeloq_h__

#include <stdint.h>

//#define USE_VIRTUAL_UINT64_VARIABLE
#define KEELOQ_NROUNDS  528

#ifdef USE_VIRTUAL_UINT64_VARIABLE
typedef struct{
    uint32_t H;
    uint32_t L;
}uint64_t;
#endif

#define NLF_LOOKUP_CONSTANT 0x3a5c742e

uint16_t nlf(uint16_t d);
void keeloq_encrypt(uint64_t *key, uint32_t *plaintext, uint32_t *ciphertext, uint16_t nrounds);
void keeloq_decrypt(uint64_t *key, uint32_t *plaintext, uint32_t *ciphertext, uint16_t nrounds);

#endif
