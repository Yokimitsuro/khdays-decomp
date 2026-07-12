/* Poll func_ov267_020d124c: on success arm the 0x15e/6 timer and advance to func_ov267_020d3058, otherwise notify func_ov267_020d11fc
 * and advance to func_ov267_020d2fec. */
extern int func_ov267_020d124c(int, int);
extern int func_ov107_020c5af8(int, int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov267_020d11fc(int, int);
extern int func_ov267_020d3058(int);
extern int func_ov267_020d2fec(int);
void func_ov267_020d2f78(int param_1) {
    int owner = *(int *)(param_1 + 4);
    if (func_ov267_020d124c(owner, 1) != 0) {
        func_ov107_020c5af8(*(int *)owner, 0x15e, 6, *(int *)(owner + 8));
        func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov267_020d3058);
    } else {
        func_ov267_020d11fc(owner, 0);
        func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov267_020d2fec);
    }
}
