/* Register the ov277 object factory (type 0x62) with the shared registrar. */
extern int func_ov107_020c2f7c(int, void *);
extern int func_ov277_020cbf38(int);
int func_ov277_020cbf20(void) {
    return func_ov107_020c2f7c(0x62, (void *)&func_ov277_020cbf38);
}
