/* Register the ov223 object factory (type 0x34) with the shared registrar. */
extern int func_ov107_020c2f7c(int, void *);
extern int func_ov223_020cfb78(int);
int func_ov223_020cfb60(void) {
    return func_ov107_020c2f7c(0x34, (void *)&func_ov223_020cfb78);
}
