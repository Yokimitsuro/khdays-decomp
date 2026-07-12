/* Register the ov224 object factory (type 0x35) with the shared registrar. */
extern int func_ov107_020c2f7c(int, void *);
extern int func_ov224_020cfb78(int);
int func_ov224_020cfb60(void) {
    return func_ov107_020c2f7c(0x35, (void *)&func_ov224_020cfb78);
}
