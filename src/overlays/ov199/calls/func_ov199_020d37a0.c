/* Register the ov199 object factory (type 0x25) with the shared registrar. */
extern int func_ov107_020c2f7c(int, void *);
extern int func_ov199_020d37b8(int);
int func_ov199_020d37a0(void) {
    return func_ov107_020c2f7c(0x25, (void *)&func_ov199_020d37b8);
}
