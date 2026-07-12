/* Register the ov225 object factory (type 0x36) with the shared registrar. */
extern int func_ov107_020c2f7c(int, void *);
extern int func_ov225_020cfb78(int);
int func_ov225_020cfb60(void) {
    return func_ov107_020c2f7c(0x36, (void *)&func_ov225_020cfb78);
}
