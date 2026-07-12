/* Register the ov236 object factory (type 0x3f) with the shared registrar. */
extern int func_ov107_020c2f7c(int, void *);
extern int func_ov236_020cbf38(int);
int func_ov236_020cbf20(void) {
    return func_ov107_020c2f7c(0x3f, (void *)&func_ov236_020cbf38);
}
