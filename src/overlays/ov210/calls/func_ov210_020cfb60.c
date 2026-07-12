/* Register the ov210 object factory (type 0x2b) with the shared registrar. */
extern int func_ov107_020c2f7c(int, void *);
extern int func_ov210_020cfb78(int);
int func_ov210_020cfb60(void) {
    return func_ov107_020c2f7c(0x2b, (void *)&func_ov210_020cfb78);
}
