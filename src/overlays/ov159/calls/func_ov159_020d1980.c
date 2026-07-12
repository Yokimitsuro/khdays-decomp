/* Register the ov159 object factory (type 0x16) with the shared registrar. */
extern int func_ov107_020c2f7c(int, void *);
extern int func_ov159_020d1998(int);
int func_ov159_020d1980(void) {
    return func_ov107_020c2f7c(0x16, (void *)&func_ov159_020d1998);
}
