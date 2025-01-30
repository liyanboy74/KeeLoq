#include "keeloq.h"

/**
 * @brief Non-Linear Function (NLF) used in KeeLoq encryption algorithm.
 *
 * This function takes an 8-bit input and returns a single bit output based on
 * a predefined non-linear function lookup constant.
 *
 * @param d Bit ndex of NLF lookup constant, from 0 to 31.
 * @return A single bit (0 or 1) derived from the NLF lookup constant.
 */
uint8_t nlf(uint8_t d)
{
    return (((uint32_t)(NLF_LOOKUP_CONSTANT) >> d) & 0x1);
}

/**
 * @brief Encrypts data using the KeeLoq algorithm.
 *
 * This function performs KeeLoq encryption on the provided data using the given key and number of rounds.
 *
 * @param key A pointer to the encryption key, which is an array of 8-bit unsigned integers.
 * @param data A pointer to the data to be encrypted, which is a 32-bit unsigned integer.
 * @param nrounds The number of encryption rounds to perform - KEELOQ_NROUNDS .
 *
 * The KeeLoq encryption algorithm is a lightweight block cipher used primarily in remote keyless entry systems.
 * The function modifies the data in place, performing the specified number of encryption rounds.
 */
void keeloq_encrypt(uint8_t *key, uint32_t *data, const uint16_t nrounds)
{
    uint32_t x;
    uint16_t loop;
    uint8_t o, nlf_input,k,ki;

    for (loop = 0; loop < nrounds; loop++)
    {
        nlf_input = (((*data >> 31) & 0x1) << 4) | (((*data >> 26) & 0x1) << 3) |
                    (((*data >> 20) & 0x1) << 2) | (((*data >> 9) & 0x1) << 1) | ((*data >> 1) & 0x1);

        o = nlf(nlf_input);
        ki=loop % 64;
        k=key[ki/8]>>(ki%8);
        x =k ^ (*data >> 16) ^ *data ^ o;
        *data = (*data >> 1) | (x << 31);
    }
}

/**
 * @brief Decrypts data using the KeeLoq algorithm.
 *
 * This function performs decryption on the provided data using the KeeLoq
 * algorithm. The decryption process involves multiple rounds of bitwise
 * operations and non-linear function (NLF) evaluations.
 *
 * @param key Pointer to the 64-bit key used for decryption.
 * @param data Pointer to the 32-bit data to be decrypted.
 * @param nrounds Number of decryption rounds to be performed - KEELOQ_NROUNDS .
 */
void keeloq_decrypt(uint8_t *key, uint32_t *data,const uint16_t nrounds)
{
    uint32_t x;
    uint16_t loop;
    uint8_t o, nlf_input,k,ki;

    for (loop = 0; loop < nrounds; loop++)
    {
        nlf_input = (((*data >> 30) & 0x1) << 4) | (((*data >> 25) & 0x1) << 3) |
                    (((*data >> 19) & 0x1) << 2) | (((*data >> 8) & 0x1) << 1) | (*data & 0x1);

        o = nlf(nlf_input);
        ki=(uint16_t)(15 - loop) % 64;
        k=key[ki/8]>>(ki%8);
        x = k ^ (*data >> 31) ^ (*data >> 15) ^ o;
        *data = (*data << 1) | x&1;
    }
}

/**
 * @brief Generate a normal key from manufacturer key
 *
 * This function generates a normal key using the provided manufacturer key
 * and serial number. The process involves modifying the serial number,
 * decrypting it using the KeeLoq algorithm, and copying the result into
 * the output key.
 *
 * @param key Output key
 * @param mf_key Input manufacturer key
 * @param ser Input serial number
 */
void keeloq_gen_normal_key(uint8_t *key,uint8_t *mf_key,uint32_t ser)
{
    uint32_t temp;

    ser &= 0x0fffffff;

    temp = ser;
    temp |= 0x20000000;
    keeloq_decrypt(mf_key, &temp, KEELOQ_NROUNDS);
    memccpy(&key[0],&temp,1,4);

    temp = ser;
    temp |= 0x60000000;
    keeloq_decrypt(mf_key,&temp,KEELOQ_NROUNDS);
    memccpy(&key[4],&temp,1,4);
}

/**
 * @brief Generates a secure key using the KeeLoq algorithm.
 *
 * This function generates a secure key by decrypting a manufacturer key (mf_key)
 * with a seed and a serial number (ser). The decrypted values are then copied
 * into the provided key buffer.
 *
 * @param key Pointer to the buffer where the generated secure key will be stored.
 *            The buffer should be large enough to hold the key.
 * @param mf_key Pointer to the manufacturer key used for decryption.
 * @param seed The seed value used for the first decryption.
 * @param ser The serial number used for the second decryption. Only the lower
 *            28 bits of the serial number are used.
 */
void keeloq_gen_secure_key(uint8_t *key,uint8_t *mf_key,uint32_t seed,uint32_t ser)
{
  keeloq_decrypt(mf_key, &seed, KEELOQ_NROUNDS);
  memccpy(&key[0],&seed,1,4);

  ser &= 0x0fffffff;
  keeloq_decrypt(mf_key, &ser, KEELOQ_NROUNDS);
  memccpy(&key[4],&ser,1,4);
}
