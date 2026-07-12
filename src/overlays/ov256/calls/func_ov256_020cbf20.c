/* Register the ov256 object factory (type 0x50) with the shared registrar. */
extern int func_ov107_020c2f7c(int, void *);
extern int func_ov256_020cbf38(int);
int func_ov256_020cbf20(void) {
    return func_ov107_020c2f7c(0x50, (void *)&func_ov256_020cbf38);
}
