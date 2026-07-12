/* Register the ov209 object factory (type 0x2a) with the shared registrar. */
extern int func_ov107_020c2f7c(int, void *);
extern int func_ov209_020d1998(int);
int func_ov209_020d1980(void) {
    return func_ov107_020c2f7c(0x2a, (void *)&func_ov209_020d1998);
}
