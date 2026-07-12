/* Register the ov255 object factory (type 0x4f) with the shared registrar. */
extern int func_ov107_020c2f7c(int, void *);
extern int func_ov255_020cbf38(int);
int func_ov255_020cbf20(void) {
    return func_ov107_020c2f7c(0x4f, (void *)&func_ov255_020cbf38);
}
