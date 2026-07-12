/* Register the ov228 object factory (type 0x39) with the shared registrar. */
extern int func_ov107_020c2f7c(int, void *);
extern int func_ov228_020cdd58(int);
int func_ov228_020cdd40(void) {
    return func_ov107_020c2f7c(0x39, (void *)&func_ov228_020cdd58);
}
