/* Register the ov244 object factory (type 0x46) with the shared registrar. */
extern int func_ov107_020c2f7c(int, void *);
extern int func_ov244_020cbf38(int);
int func_ov244_020cbf20(void) {
    return func_ov107_020c2f7c(0x46, (void *)&func_ov244_020cbf38);
}
