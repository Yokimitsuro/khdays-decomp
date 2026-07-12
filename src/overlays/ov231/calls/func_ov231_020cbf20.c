/* Register the ov231 object factory (type 0x3b) with the shared registrar. */
extern int func_ov107_020c2f7c(int, void *);
extern int func_ov231_020cbf38(int);
int func_ov231_020cbf20(void) {
    return func_ov107_020c2f7c(0x3b, (void *)&func_ov231_020cbf38);
}
