/* Create a sub-object via func_0203c5c0 (kind 0x64/0x80, handler func_ov224_020d1404), back-
 * link it, copy the owner state at +0x384 into it, and store it at +0x214. */
extern int func_0203c5c0(int a, int b, int c, void *handler, int e, int *out);
extern void func_ov224_020d1404(void);
void func_ov224_020d06b4(int param_1) {
    int obj;
    func_0203c5c0(*(int *)(param_1 + 0x3c), 0x64, 0x80, (void *)&func_ov224_020d1404, 0, &obj);
    *(int *)obj = param_1;
    *(int *)(obj + 4) = *(int *)(*(int *)obj + 0x384);
    *(int *)(param_1 + 0x214) = obj;
}
