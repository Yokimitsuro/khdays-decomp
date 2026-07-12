/* Register the ov126 object factory (type 0x6) with the shared registrar. */
extern int func_ov107_020c2f7c(int, void *);
extern int func_ov126_020cfb78(int);
int func_ov126_020cfb60(void) {
    return func_ov107_020c2f7c(0x6, (void *)&func_ov126_020cfb78);
}
