/* Register the ov283 object factory (type 0x68) with the shared registrar. */
extern int func_ov107_020c2f7c(int, void *);
extern int func_ov283_020cbf38(int);
int func_ov283_020cbf20(void) {
    return func_ov107_020c2f7c(0x68, (void *)&func_ov283_020cbf38);
}
