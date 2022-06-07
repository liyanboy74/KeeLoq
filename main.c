#include <stdio.h>
#include "keeloq.h"

int main()
{
    uint32_t ciphertext,plaintext;
    uint64_t key;
    int nrounds;

    plaintext=0xf741e2db;
    key=0x5cec6701b79fd949;
    nrounds=528;

    printf("Text=0x%08x Key=0x%08x%08x N=%d\r\n",plaintext,key>>32,key,nrounds);

    keeloq_encrypt(&key,&plaintext,&ciphertext,nrounds);
    printf("Encrypted to 0x%08x\r\n",ciphertext);

    plaintext=0;

    keeloq_decrypt(&key,&plaintext,&ciphertext,nrounds);
    printf("Decrypted to 0x%08x\r\n",plaintext);

    return 0;
}