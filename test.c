#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#include <stdio.h>
#include "keeloq.h"

void test_simple()
{
    // KEELOQ Key LSB-first
    uint8_t key[]= {0x49,0xd9,0x9f,0xb7,0x01,0x67,0xec,0x5c};

    uint32_t plaintext_ok=    0xf741e2db;
    uint32_t ciphertext_ok=   0xe44f4cdf;
    uint32_t temp;

    temp=plaintext_ok;

    // Encrypt plaintext to ciphertext
    keeloq_encrypt(key,&temp,KEELOQ_NROUNDS);

    CU_ASSERT_EQUAL(temp, ciphertext_ok);

    // Decrypt ciphertext to plaintext
    keeloq_decrypt(key,&temp,KEELOQ_NROUNDS);

    CU_ASSERT_EQUAL(temp, plaintext_ok);
}

void test_normal()
{
    // KEELOQ Key LSB-first
    uint8_t mf_key[]={0xef,0xcd,0xab,0x89,0x67,0x45,0x23,0x01};
    uint32_t ser=0x6C46ACA;
    uint8_t key[8];

    uint32_t plaintext_ok=    0x1eca04b4;
    uint32_t ciphertext_ok=   0xecf4c92d;
    uint32_t temp;

    temp=plaintext_ok;

    // Generate normal key
    keeloq_gen_normal_key(key,mf_key,ser);

    // Encrypt plaintext to ciphertext
    keeloq_encrypt(key,&temp,KEELOQ_NROUNDS);

    CU_ASSERT_EQUAL(temp, ciphertext_ok);

    // Decrypt ciphertext to plaintext
    keeloq_decrypt(key,&temp,KEELOQ_NROUNDS);

    CU_ASSERT_EQUAL(temp, plaintext_ok);
}

void test_secure()
{
    // KEELOQ Key LSB-first
    uint8_t mf_key[]={0xef,0xcd,0xab,0x89,0x67,0x45,0x23,0x01};
    uint32_t ser=   0x0B6AF9A8;
    uint32_t seed=  0x4380FD94;
    uint8_t key[8];

    uint32_t plaintext_ok=    0x95874b2c;
    uint32_t ciphertext_ok=   0xc9ebe007;
    uint32_t temp;

    temp=plaintext_ok;

    // Generate secure key
    keeloq_gen_secure_key(key,mf_key,seed,ser);

    // Encrypt plaintext to ciphertext
    keeloq_encrypt(key,&temp,KEELOQ_NROUNDS);

    CU_ASSERT_EQUAL(temp, ciphertext_ok);

    // Decrypt ciphertext to plaintext
    keeloq_decrypt(key,&temp,KEELOQ_NROUNDS);

    CU_ASSERT_EQUAL(temp, plaintext_ok);
}

int main()
{
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Test Suite", 0, 0);
    CU_add_test(suite, "Simple Test", test_simple);
    CU_add_test(suite, "Normal Test", test_normal);
    CU_add_test(suite, "Secure Test", test_secure);
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
