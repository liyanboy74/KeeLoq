#include <stdio.h>
#include "keeloq.h"

int main()
{
    int i,err=0;

    // in keeloq header file we can chose if compiler doesn't support 64 bit variable!
    // that option useful for embeded device.
    #ifdef USE_VIRTUAL_UINT64_VARIABLE
    uint64_v key= {0x5cec6701,0xb79fd949};
    #else
    uint64_v key= {0x5cec6701b79fd949};
    #endif

    uint32_t plaintext_ok[]=    {0xf741e2db,0x0ca69b92};
    uint32_t ciphertext_ok[]=   {0xe44f4cdf,0xa6ac0ea2};
    uint32_t ciphertext,plaintext;

    for(i=0;i<(sizeof(plaintext_ok)/sizeof(plaintext_ok[0]));i++)
    {
        printf("------- Test[%03d] -------\r\n",i+1);

        #ifdef USE_VIRTUAL_UINT64_VARIABLE
        printf("Text=0x%08x\r\nKey=0x%08x%08x\r\n",plaintext_ok[i],key.H,key.L);
        #else
        printf("Text=0x%08x\r\nKey=0x%08x%08x\r\n",plaintext_ok[i],key>>32,key);
        #endif

        printf("N=%d\r\n",KEELOQ_NROUNDS);

        // Encrypt plaintext to ciphertext
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

        // Decrypt ciphertext to plaintext
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