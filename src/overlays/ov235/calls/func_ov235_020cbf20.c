/* Register the ov235 object factory (type 0x3e) with the shared registrar. */
extern int func_ov107_020c2f7c(int, void *);
extern int func_ov235_020cbf38(int);
int func_ov235_020cbf20(void) {
    return func_ov107_020c2f7c(0x3e, (void *)&func_ov235_020cbf38);
}
