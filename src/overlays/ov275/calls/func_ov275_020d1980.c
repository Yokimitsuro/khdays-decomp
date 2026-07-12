/* Register the ov275 object factory (type 0x60) with the shared registrar. */
extern int func_ov107_020c2f7c(int, void *);
extern int func_ov275_020d1998(int);
int func_ov275_020d1980(void) {
    return func_ov107_020c2f7c(0x60, (void *)&func_ov275_020d1998);
}
