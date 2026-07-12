/* Register the ov238 object factory (type 0x41) with the shared registrar. */
extern int func_ov107_020c2f7c(int, void *);
extern int func_ov238_020cfb78(int);
int func_ov238_020cfb60(void) {
    return func_ov107_020c2f7c(0x41, (void *)&func_ov238_020cfb78);
}
