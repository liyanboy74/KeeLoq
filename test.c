#include <stdio.h>
#include <stdio.h>
#include "keeloq.h"

#define TEST_N 2

int main()
{
    int i,err=0;

    uint64_t key=                   {0x5cec6701b79fd949};
    uint32_t plaintext_ok[TEST_N]=  {0xf741e2db,0x0ca69b92};
    uint32_t ciphertext_ok[TEST_N]= {0xe44f4cdf,0xa6ac0ea2};
    uint32_t ciphertext,plaintext;

    for(i=0;i<2;i++)
    {
        printf("------- Test[%03d] -------\r\n",i+1);
        printf("Text=0x%08x\r\nKey=0x%08x%08x N=%d\r\n",plaintext_ok[i],key>>32,key,KEELOQ_NROUNDS);
        keeloq_encrypt(&key,&plaintext_ok[i],&ciphertext,KEELOQ_NROUNDS);
        printf("Encrypted to 0x%08x ",ciphertext);
        if(ciphertext==ciphertext_ok[i]) printf("[ OK ]");
        else
        {
            printf("[ ERROR! ]");
            err++;
        }
        printf("\r\n");
        plaintext=0;
        keeloq_decrypt(&key,&plaintext,&ciphertext,KEELOQ_NROUNDS);
        printf("Decrypted to 0x%08x ",plaintext);
        if(plaintext==plaintext_ok[i]) printf("[ OK ]");
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