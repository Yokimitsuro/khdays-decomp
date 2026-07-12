/* Register the ov158 object factory (type 0x16) with the shared registrar. */
extern int func_ov107_020c2f7c(int, void *);
extern int func_ov158_020cbf38(int);
int func_ov158_020cbf20(void) {
    return func_ov107_020c2f7c(0x16, (void *)&func_ov158_020cbf38);
}
