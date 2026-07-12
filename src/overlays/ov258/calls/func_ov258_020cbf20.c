/* Register the ov258 object factory (type 0x52) with the shared registrar. */
extern int func_ov107_020c2f7c(int, void *);
extern int func_ov258_020cbf38(int);
int func_ov258_020cbf20(void) {
    return func_ov107_020c2f7c(0x52, (void *)&func_ov258_020cbf38);
}
