/* Register the ov272 object factory (type 0x5e) with the shared registrar. */
extern int func_ov107_020c2f7c(int, void *);
extern int func_ov272_020cfb78(int);
int func_ov272_020cfb60(void) {
    return func_ov107_020c2f7c(0x5e, (void *)&func_ov272_020cfb78);
}
