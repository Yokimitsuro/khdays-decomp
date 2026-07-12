/* Register the ov268 object factory (type 0x5b) with the shared registrar. */
extern int func_ov107_020c2f7c(int, void *);
extern int func_ov268_020cfb78(int);
int func_ov268_020cfb60(void) {
    return func_ov107_020c2f7c(0x5b, (void *)&func_ov268_020cfb78);
}
