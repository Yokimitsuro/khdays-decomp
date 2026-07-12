/* Register the ov119 object factory (type 0x3) with the shared registrar. */
extern int func_ov107_020c2f7c(int, void *);
extern int func_ov119_020cbf38(int);
int func_ov119_020cbf20(void) {
    return func_ov107_020c2f7c(0x3, (void *)&func_ov119_020cbf38);
}
