#include "cx.h"

uint32_t app_stack_canary[1000] = {0};

void os_longjmp(unsigned int exception) {
    longjmp(try_context_get()->jmp_buf, exception);
}

try_context_t *current_context = NULL;
try_context_t *try_context_get(void) {
    return current_context;
}

try_context_t *try_context_set(try_context_t *ctx) {
    try_context_t *previous_ctx = current_context;
    current_context = ctx;
    return previous_ctx;
}

cx_err_t cx_ripemd160_init_no_throw(cx_ripemd160_t *hash) {
    return CX_OK;
}

size_t cx_hash_get_size(const cx_hash_t *ctx) {
    return 32;
}

cx_err_t cx_sha256_init_no_throw(cx_sha256_t *hash) {
    return CX_OK;
}

cx_err_t cx_hash_no_throw(cx_hash_t *hash, uint32_t mode, const uint8_t *in, size_t len, uint8_t *out, size_t out_len) {
    return CX_OK;
}

size_t cx_hash_sha256(const uint8_t *in, size_t len, uint8_t *out, size_t out_len)
{
    return CX_SHA256_SIZE;
}

cx_err_t cx_rng_no_throw(uint8_t *buf, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        buf[i] = rand();
    }
    return CX_OK;
}

void os_perso_derive_node_bip32 ( cx_curve_t curve, const unsigned int * path, unsigned int pathLength, unsigned char * privateKey, unsigned char * chain ) {                                                 
    unsigned int parameters [2+5];                                                
    parameters[0] = (unsigned int)curve;                                                                                                                                                                        
    parameters[1] = (unsigned int)path;                                           
    parameters[2] = (unsigned int)pathLength;                                                                                                                                                                   
    parameters[3] = (unsigned int)privateKey;                                     
    parameters[4] = (unsigned int)chain;                                                                                                                                                                                     
    return;                                                                       
}

cx_err_t cx_ecfp_init_private_key_no_throw(cx_curve_t curve, const unsigned char * rawkey,size_t key_len, cx_ecfp_private_key_t * pvkey)
{
    return CX_OK;
}

cx_err_t cx_ecfp_init_public_key_no_throw(cx_curve_t curve, const unsigned char * rawkey,size_t key_len, cx_ecfp_public_key_t * pvkey)
{
    return CX_OK;
}

cx_err_t cx_ecfp_generate_pair_no_throw(cx_curve_t             curve,               
                               cx_ecfp_public_key_t * pubkey,                       
                               cx_ecfp_private_key_t *privkey,                                                                                                                                                     
                               bool                   keepprivate)
{
    return CX_OK;
}

cx_err_t cx_ecdsa_sign_no_throw(const cx_ecfp_private_key_t *key,                   
                       uint32_t                     mode,                           
                       cx_md_t                      hashID,                         
                       const uint8_t *              hash,                           
                       size_t                       hash_len,                       
                       uint8_t *                    sig,                            
                       size_t *                     sig_len,                        
                       uint32_t *                   info)
{
    return CX_OK;
}

void *pic(void *link_address)
{
    return link_address;
}

void nvm_write ( void * dst_adr, void * src_adr, unsigned int src_len ) {
}

void io_seproxyhal_se_reset(void) {
}