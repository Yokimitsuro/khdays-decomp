/* Register the ov274 object factory (type 0x60) with the shared registrar. */
extern int func_ov107_020c2f7c(int, void *);
extern int func_ov274_020cfb78(int);
int func_ov274_020cfb60(void) {
    return func_ov107_020c2f7c(0x60, (void *)&func_ov274_020cfb78);
}
