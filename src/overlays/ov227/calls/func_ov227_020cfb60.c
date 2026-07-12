/* Register the ov227 object factory (type 0x38) with the shared registrar. */
extern int func_ov107_020c2f7c(int, void *);
extern int func_ov227_020cfb78(int);
int func_ov227_020cfb60(void) {
    return func_ov107_020c2f7c(0x38, (void *)&func_ov227_020cfb78);
}
