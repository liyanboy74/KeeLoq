#ifndef __keeloq_h__
#define __keeloq_h__

#include <stdint.h>
#include <string.h>

#define KEELOQ_NROUNDS  528
#define NLF_LOOKUP_CONSTANT 0x3a5c742e

#ifdef __cplusplus
extern "C" {
#endif

uint8_t nlf(uint8_t d);
void keeloq_encrypt(uint8_t *key, uint32_t *data,const uint16_t nrounds);
void keeloq_decrypt(uint8_t *key, uint32_t *data,const uint16_t nrounds);
void keeloq_gen_normal_key(uint8_t *key,uint8_t *mf_key,uint32_t ser);
void keeloq_gen_secure_key(uint8_t *key,uint8_t *mf_key,uint32_t seed,uint32_t ser);

#ifdef __cplusplus
}
#endif

#endif
