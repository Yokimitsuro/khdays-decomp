/* Register the ov263 object factory (type 0x57) with the shared registrar. */
extern int func_ov107_020c2f7c(int, void *);
extern int func_ov263_020cfb78(int);
int func_ov263_020cfb60(void) {
    return func_ov107_020c2f7c(0x57, (void *)&func_ov263_020cfb78);
}
