/* Register the ov254 object factory (type 0x4e) with the shared registrar. */
extern int func_ov107_020c2f7c(int, void *);
extern int func_ov254_020cbf38(int);
int func_ov254_020cbf20(void) {
    return func_ov107_020c2f7c(0x4e, (void *)&func_ov254_020cbf38);
}
