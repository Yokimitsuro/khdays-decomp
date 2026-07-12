/* Register the ov260 object factory (type 0x54) with the shared registrar. */
extern int func_ov107_020c2f7c(int, void *);
extern int func_ov260_020cbf38(int);
int func_ov260_020cbf20(void) {
    return func_ov107_020c2f7c(0x54, (void *)&func_ov260_020cbf38);
}
