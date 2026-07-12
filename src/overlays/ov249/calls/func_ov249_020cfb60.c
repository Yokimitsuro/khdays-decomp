/* Register the ov249 object factory (type 0x4a) with the shared registrar. */
extern int func_ov107_020c2f7c(int, void *);
extern int func_ov249_020cfb78(int);
int func_ov249_020cfb60(void) {
    return func_ov107_020c2f7c(0x4a, (void *)&func_ov249_020cfb78);
}
