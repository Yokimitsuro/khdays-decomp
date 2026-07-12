/* Register the ov259 object factory (type 0x53) with the shared registrar. */
extern int func_ov107_020c2f7c(int, void *);
extern int func_ov259_020cbf38(int);
int func_ov259_020cbf20(void) {
    return func_ov107_020c2f7c(0x53, (void *)&func_ov259_020cbf38);
}
