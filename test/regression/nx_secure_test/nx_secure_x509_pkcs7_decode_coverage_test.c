/* This test is to cover nx_secure_x509_pkcs7_decode.c.  */

#include   "tx_api.h"
#include   "nx_api.h"
#include   "nx_tcp.h"
#include   "nx_secure_tls_api.h"
#include   "tls_test_utility.h"

extern void    test_control_return(UINT status);

#define     DEMO_STACK_SIZE         2048

/* Define the ThreadX and NetX object control blocks...  */
static TX_THREAD               thread_0;

/* Define thread prototypes.  */
static void    thread_0_entry(ULONG thread_input);
extern void    _nx_ram_network_driver_1500(struct NX_IP_DRIVER_STRUCT *driver_req);

/* Define what the initial system looks like.  */
#ifdef CTEST
void test_application_define(void *first_unused_memory);
void test_application_define(void *first_unused_memory)
#else
void nx_secure_x509_pkcs7_decode_coverage_test_application_define(void *first_unused_memory)
#endif
{
    /* Create the main thread.  */
    tx_thread_create(&thread_0, "thread 0", thread_0_entry, 0,
                     first_unused_memory, DEMO_STACK_SIZE,
                     4, 4, TX_NO_TIME_SLICE, TX_AUTO_START);
}

static UCHAR signature_data[] = 
{
0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x30, 0x31, 0x30,
0x0d, 0x06, 0x09, 0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x01, 0x05, 0x00, 0x04, 0x20,
0x80, 0xda, 0x3c, 0x9c, 0x9b, 0xf6, 0xe0, 0x4d, 0x4d, 0x2f, 0x92, 0xd5, 0x85, 0x99, 0xb2, 0xfb,
0x53, 0x0c, 0xc7, 0x44, 0xa8, 0xdb, 0x94, 0x89, 0x48, 0x03, 0x66, 0xc2, 0x5f, 0x60, 0xbe, 0xbd,
};


static void    thread_0_entry(ULONG thread_input)
{
UINT status;
UINT signature_length;
const UCHAR *oid;
UINT oid_length;
const UCHAR *decrypted_hash;
UINT decrypted_hash_length;
UCHAR *decrypted_signature;
UCHAR temp;

    /* Print out test information banner.  */
    printf("NetX Secure Test:   X509 PKCS7 Decode Coverage Test....................");

    /* Cover line 151. */
    decrypted_signature = signature_data;
    signature_length = sizeof(signature_data);
    temp = decrypted_signature[0xcd];
    decrypted_signature[0xcd] = 0x31;
    status = _nx_secure_x509_pkcs7_decode(decrypted_signature, signature_length, &oid, &oid_length,
                                          &decrypted_hash, &decrypted_hash_length);
    EXPECT_EQ(NX_SECURE_X509_PKCS7_PARSING_FAILED, status);
    decrypted_signature[0xcd] = 0xb0;
    status = _nx_secure_x509_pkcs7_decode(decrypted_signature, signature_length, &oid, &oid_length,
                                          &decrypted_hash, &decrypted_hash_length);
    EXPECT_EQ(NX_SECURE_X509_PKCS7_PARSING_FAILED, status);
    decrypted_signature[0xcd] = temp;

    /* Cover line 161. */
    temp = decrypted_signature[0xcf];
    decrypted_signature[0xcf] = 0x31;
    status = _nx_secure_x509_pkcs7_decode(decrypted_signature, signature_length, &oid, &oid_length,
                                          &decrypted_hash, &decrypted_hash_length);
    EXPECT_EQ(NX_SECURE_X509_PKCS7_PARSING_FAILED, status);
    decrypted_signature[0xcf] = 0xb0;
    status = _nx_secure_x509_pkcs7_decode(decrypted_signature, signature_length, &oid, &oid_length,
                                          &decrypted_hash, &decrypted_hash_length);
    EXPECT_EQ(NX_SECURE_X509_PKCS7_PARSING_FAILED, status);
    decrypted_signature[0xcf] = temp;

    /* Cover line 178.  */
    temp = decrypted_signature[0xd1];
    decrypted_signature[0xd1] = 0x86;
    status = _nx_secure_x509_pkcs7_decode(decrypted_signature, signature_length, &oid, &oid_length,
                                          &decrypted_hash, &decrypted_hash_length);
    EXPECT_EQ(NX_SECURE_X509_PKCS7_PARSING_FAILED, status);
    decrypted_signature[0xd1] = 0x07;
    status = _nx_secure_x509_pkcs7_decode(decrypted_signature, signature_length, &oid, &oid_length,
                                          &decrypted_hash, &decrypted_hash_length);
    EXPECT_EQ(NX_SECURE_X509_PKCS7_PARSING_FAILED, status);
    decrypted_signature[0xd1] = temp;

    /* Cover line 201.  */
    temp = decrypted_signature[0xde];
    decrypted_signature[0xde] = 0x84;
    status = _nx_secure_x509_pkcs7_decode(decrypted_signature, signature_length, &oid, &oid_length,
                                          &decrypted_hash, &decrypted_hash_length);
    EXPECT_EQ(NX_SECURE_X509_PKCS7_PARSING_FAILED, status);
    decrypted_signature[0xde] = temp;

    printf("SUCCESS!\n");
    test_control_return(0);
}