#include <stdio.h>
#include "keeloq.h"

int main()
{
    int i,err=0;

    // KEELOQ Key LSB-first
    uint8_t key[]= {0x49,0xd9,0x9f,0xb7,0x01,0x67,0xec,0x5c};

    uint32_t plaintext_ok[]=    {0xf741e2db,0x0ca69b92};
    uint32_t ciphertext_ok[]=   {0xe44f4cdf,0xa6ac0ea2};
    uint32_t temp;

    for(i=0;i<(sizeof(plaintext_ok)/sizeof(plaintext_ok[0]));i++)
    {
        printf("------- Test[%03d] -------\r\n",i+1);

        temp=plaintext_ok[i];

        printf("Text=0x%08x\r\n",temp);
        printf("N=%d\r\n",KEELOQ_NROUNDS);

        // Encrypt plaintext to ciphertext
        keeloq_encrypt(key,&temp,KEELOQ_NROUNDS);

        printf("Encrypted to 0x%08x ",temp);
        if(temp==ciphertext_ok[i]) printf("[ OK ]");
        else
        {
            printf("[ ERROR! ]");
            err++;
        }
        printf("\r\n");

        // Decrypt ciphertext to plaintext
        keeloq_decrypt(key,&temp,KEELOQ_NROUNDS);

        printf("Decrypted to 0x%08x ",temp);
        if(temp==plaintext_ok[i]) printf("[ OK ]");
        else
        {
            printf("[ ERROR! ]");
            err++;
        }
        printf("\r\n-------------------------\r\n");

    }

    printf("Test Status : ");
    if(err)printf("FAIL!");
    else printf("PASS");
    printf("\r\n-------------------------\r\n");

    return err;
}