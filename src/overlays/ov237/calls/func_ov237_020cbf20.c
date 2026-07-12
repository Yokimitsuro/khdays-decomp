/* Register the ov237 object factory (type 0x40) with the shared registrar. */
extern int func_ov107_020c2f7c(int, void *);
extern int func_ov237_020cbf38(int);
int func_ov237_020cbf20(void) {
    return func_ov107_020c2f7c(0x40, (void *)&func_ov237_020cbf38);
}
