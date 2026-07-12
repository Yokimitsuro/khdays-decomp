/* Register the ov273 object factory (type 0x5f) with the shared registrar. */
extern int func_ov107_020c2f7c(int, void *);
extern int func_ov273_020cfb78(int);
int func_ov273_020cfb60(void) {
    return func_ov107_020c2f7c(0x5f, (void *)&func_ov273_020cfb78);
}
