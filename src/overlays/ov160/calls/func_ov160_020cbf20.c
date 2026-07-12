/* Register the ov160 object factory (type 0x17) with the shared registrar. */
extern int func_ov107_020c2f7c(int, void *);
extern int func_ov160_020cbf38(int);
int func_ov160_020cbf20(void) {
    return func_ov107_020c2f7c(0x17, (void *)&func_ov160_020cbf38);
}
