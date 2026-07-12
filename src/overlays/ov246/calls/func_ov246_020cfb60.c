/* Register the ov246 object factory (type 0x48) with the shared registrar. */
extern int func_ov107_020c2f7c(int, void *);
extern int func_ov246_020cfb78(int);
int func_ov246_020cfb60(void) {
    return func_ov107_020c2f7c(0x48, (void *)&func_ov246_020cfb78);
}
