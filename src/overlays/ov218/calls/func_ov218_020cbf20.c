/* Register the ov218 object factory (type 0x30) with the shared registrar. */
extern int func_ov107_020c2f7c(int, void *);
extern int func_ov218_020cbf38(int);
int func_ov218_020cbf20(void) {
    return func_ov107_020c2f7c(0x30, (void *)&func_ov218_020cbf38);
}
