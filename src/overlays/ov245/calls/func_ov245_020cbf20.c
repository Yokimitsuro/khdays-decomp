/* Register the ov245 object factory (type 0x47) with the shared registrar. */
extern int func_ov107_020c2f7c(int, void *);
extern int func_ov245_020cbf38(int);
int func_ov245_020cbf20(void) {
    return func_ov107_020c2f7c(0x47, (void *)&func_ov245_020cbf38);
}
