/* Register the ov279 object factory (type 0x64) with the shared registrar. */
extern int func_ov107_020c2f7c(int, void *);
extern int func_ov279_020cfb78(int);
int func_ov279_020cfb60(void) {
    return func_ov107_020c2f7c(0x64, (void *)&func_ov279_020cfb78);
}
