/* Verify the SHA1 signature of a data blob: require magic 0xc8f592a6 at +0, hash
 * the 0x1cac bytes at +0x18, and compare the 20-byte digest against the stored
 * hash at +4 (func_0201f844 = memcmp). Returns 1 on match, 0 otherwise. */
extern void MATH_CalcSHA1(void *digest, const void *data, unsigned int len);
extern int func_0201f844(const void *a, const void *b, unsigned int len);
int func_ov009_02055b1c(int param_1) {
    unsigned char digest[0x14];
    if (*(unsigned int *)param_1 != 0xc8f592a6) {
        return 0;
    }
    MATH_CalcSHA1(digest, (void *)(param_1 + 0x18), 0x1cac);
    if (func_0201f844(digest, (void *)(param_1 + 4), 0x14) == 0) {
        return 1;
    }
    return 0;
}
