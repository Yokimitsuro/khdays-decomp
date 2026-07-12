/* Create a sub-object via func_0203c5c0 (kind 0x64/0x2c, handler
 * func_ov137_020cec74), back-link it to the owner, and store it at +0x214. */
extern int func_0203c5c0(int a, int b, int c, void *handler, int e, int *out);
extern void func_ov137_020cec74(void);
void func_ov137_020cec28(int param_1) {
    int obj;
    func_0203c5c0(*(int *)(param_1 + 0x3c), 0x64, 0x2c, (void *)&func_ov137_020cec74, 0, &obj);
    *(int *)obj = param_1;
    *(int *)(param_1 + 0x214) = obj;
}
