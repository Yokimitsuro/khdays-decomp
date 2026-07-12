/* Register the ov265 object factory (type 0x59) with the shared registrar. */
extern int func_ov107_020c2f7c(int, void *);
extern int func_ov265_020cfb78(int);
int func_ov265_020cfb60(void) {
    return func_ov107_020c2f7c(0x59, (void *)&func_ov265_020cfb78);
}
