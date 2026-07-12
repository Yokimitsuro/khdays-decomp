/* Create a sub-object via func_0203c5c0 (kind 0x64/0x6c), back-link it, copy owner
 * state at +0x384, and store it at +0x214. */
extern int func_0203c5c0(int a, int b, int c, void *handler, int e, int *out);
extern void func_ov233_020cd558(void);
void func_ov233_020cca8c(int param_1) {
    int obj;
    func_0203c5c0(*(int *)(param_1 + 0x3c), 0x64, 0x6c, (void *)&func_ov233_020cd558, 0, &obj);
    *(int *)obj = param_1;
    *(int *)(obj + 4) = *(int *)(*(int *)obj + 0x3a8);
    *(int *)(param_1 + 0x214) = obj;
}
