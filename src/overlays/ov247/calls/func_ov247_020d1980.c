/* Register the ov247 object factory (type 0x48) with the shared registrar. */
extern int func_ov107_020c2f7c(int, void *);
extern int func_ov247_020d1998(int);
int func_ov247_020d1980(void) {
    return func_ov107_020c2f7c(0x48, (void *)&func_ov247_020d1998);
}
