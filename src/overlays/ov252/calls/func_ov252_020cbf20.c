/* Register the ov252 object factory (type 0x4c) with the shared registrar. */
extern int func_ov107_020c2f7c(int, void *);
extern int func_ov252_020cbf38(int);
int func_ov252_020cbf20(void) {
    return func_ov107_020c2f7c(0x4c, (void *)&func_ov252_020cbf38);
}
