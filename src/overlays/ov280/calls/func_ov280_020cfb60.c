/* Register the ov280 object factory (type 0x65) with the shared registrar. */
extern int func_ov107_020c2f7c(int, void *);
extern int func_ov280_020cfb78(int);
int func_ov280_020cfb60(void) {
    return func_ov107_020c2f7c(0x65, (void *)&func_ov280_020cfb78);
}
