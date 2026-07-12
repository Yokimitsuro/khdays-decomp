/* Poll func_ov266_020cf42c: on success arm the 0x15e/6 timer and advance to func_ov266_020d1238, otherwise notify func_ov266_020cf3dc
 * and advance to func_ov266_020d11cc. */
extern int func_ov266_020cf42c(int, int);
extern int func_ov107_020c5af8(int, int, int, int);
extern int func_0203c634(int, int, void *);
extern int func_ov266_020cf3dc(int, int);
extern int func_ov266_020d1238(int);
extern int func_ov266_020d11cc(int);
void func_ov266_020d1158(int param_1) {
    int owner = *(int *)(param_1 + 4);
    if (func_ov266_020cf42c(owner, 1) != 0) {
        func_ov107_020c5af8(*(int *)owner, 0x15e, 6, *(int *)(owner + 8));
        func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov266_020d1238);
    } else {
        func_ov266_020cf3dc(owner, 0);
        func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov266_020d11cc);
    }
}
