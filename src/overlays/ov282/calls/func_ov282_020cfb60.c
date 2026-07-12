/* Register the ov282 object factory (type 0x67) with the shared registrar. */
extern int func_ov107_020c2f7c(int, void *);
extern int func_ov282_020cfb78(int);
int func_ov282_020cfb60(void) {
    return func_ov107_020c2f7c(0x67, (void *)&func_ov282_020cfb78);
}
