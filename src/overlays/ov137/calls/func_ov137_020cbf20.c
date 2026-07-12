/* Register the ov137 object factory (type 0xb) with the shared registrar. */
extern int func_ov107_020c2f7c(int, void *);
extern int func_ov137_020cbf38(int);
int func_ov137_020cbf20(void) {
    return func_ov107_020c2f7c(0xb, (void *)&func_ov137_020cbf38);
}
