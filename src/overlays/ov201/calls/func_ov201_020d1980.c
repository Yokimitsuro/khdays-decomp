/* Register the ov201 object factory (type 0x26) with the shared registrar. */
extern int func_ov107_020c2f7c(int, void *);
extern int func_ov201_020d1998(int);
int func_ov201_020d1980(void) {
    return func_ov107_020c2f7c(0x26, (void *)&func_ov201_020d1998);
}
