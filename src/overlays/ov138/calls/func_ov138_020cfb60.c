/* Register the ov138 object factory (type 0xb) with the shared registrar. */
extern int func_ov107_020c2f7c(int, void *);
extern int func_ov138_020cfb78(int);
int func_ov138_020cfb60(void) {
    return func_ov107_020c2f7c(0xb, (void *)&func_ov138_020cfb78);
}
