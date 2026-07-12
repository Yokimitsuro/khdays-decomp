/* Register the ov271 object factory (type 0x5d) with the shared registrar. */
extern int func_ov107_020c2f7c(int, void *);
extern int func_ov271_020cfb78(int);
int func_ov271_020cfb60(void) {
    return func_ov107_020c2f7c(0x5d, (void *)&func_ov271_020cfb78);
}
