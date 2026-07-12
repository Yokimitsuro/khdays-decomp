/* Register the ov226 object factory (type 0x37) with the shared registrar. */
extern int func_ov107_020c2f7c(int, void *);
extern int func_ov226_020cfb78(int);
int func_ov226_020cfb60(void) {
    return func_ov107_020c2f7c(0x37, (void *)&func_ov226_020cfb78);
}
