/* Register the ov266 object factory (type 0x5a) with the shared registrar. */
extern int func_ov107_020c2f7c(int, void *);
extern int func_ov266_020cdd58(int);
int func_ov266_020cdd40(void) {
    return func_ov107_020c2f7c(0x5a, (void *)&func_ov266_020cdd58);
}
