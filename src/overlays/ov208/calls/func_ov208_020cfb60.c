/* Register the ov208 object factory (type 0x2a) with the shared registrar. */
extern int func_ov107_020c2f7c(int, void *);
extern int func_ov208_020cfb78(int);
int func_ov208_020cfb60(void) {
    return func_ov107_020c2f7c(0x2a, (void *)&func_ov208_020cfb78);
}
