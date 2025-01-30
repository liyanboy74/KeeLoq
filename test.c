#include <stdio.h>
#include "keeloq.h"

int test_normal()
{
    int err=0;

    // KEELOQ Key LSB-first
    uint8_t key[]= {0x49,0xd9,0x9f,0xb7,0x01,0x67,0xec,0x5c};

    uint32_t plaintext_ok=    0xf741e2db;
    uint32_t ciphertext_ok=   0xe44f4cdf;
    uint32_t temp;


    printf("------- Normal test -------\r\n");

    temp=plaintext_ok;

    printf("Text=0x%08x\r\n",temp);
    printf("N=%d\r\n",KEELOQ_NROUNDS);

    // Encrypt plaintext to ciphertext
    keeloq_encrypt(key,&temp,KEELOQ_NROUNDS);

    printf("Encrypted to 0x%08x ",temp);
    if(temp==ciphertext_ok) printf("[ OK ]");
    else
    {
        printf("[ ERROR! ]");
        err++;
    }
    printf("\r\n");

    // Decrypt ciphertext to plaintext
    keeloq_decrypt(key,&temp,KEELOQ_NROUNDS);

    printf("Decrypted to 0x%08x ",temp);
    if(temp==plaintext_ok) printf("[ OK ]");
    else
    {
        printf("[ ERROR! ]");
        err++;
    }
    printf("\r\n-------------------------\r\n");

    return err;
}

int main()
{
    int err=0;
    err=test_normal();

    printf("Test Status : ");
    if(err)printf("FAIL!");
    else printf("PASS");
    printf("\r\n-------------------------\r\n");

    return err;
}