/* Register the ov222 object factory (type 0x33) with the shared registrar. */
extern int func_ov107_020c2f7c(int, void *);
extern int func_ov222_020d1998(int);
int func_ov222_020d1980(void) {
    return func_ov107_020c2f7c(0x33, (void *)&func_ov222_020d1998);
}
