/* Register the ov232 object factory (type 0x3b) with the shared registrar. */
extern int func_ov107_020c2f7c(int, void *);
extern int func_ov232_020cfb78(int);
int func_ov232_020cfb60(void) {
    return func_ov107_020c2f7c(0x3b, (void *)&func_ov232_020cfb78);
}
