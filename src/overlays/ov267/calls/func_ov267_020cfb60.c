/* Register the ov267 object factory (type 0x5a) with the shared registrar. */
extern int func_ov107_020c2f7c(int, void *);
extern int func_ov267_020cfb78(int);
int func_ov267_020cfb60(void) {
    return func_ov107_020c2f7c(0x5a, (void *)&func_ov267_020cfb78);
}
