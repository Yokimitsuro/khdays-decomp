/* Register the ov230 object factory (type 0x3a) with the shared registrar. */
extern int func_ov107_020c2f7c(int, void *);
extern int func_ov230_020d1998(int);
int func_ov230_020d1980(void) {
    return func_ov107_020c2f7c(0x3a, (void *)&func_ov230_020d1998);
}
