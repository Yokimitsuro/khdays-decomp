/* Create a sub-object via func_0203c5c0 (kind 0x64/0x48, handler func_ov218_020ce48c),
 * back-link it, copy owner state at +0x384, and store it at +0x214. */
extern int func_0203c5c0(int a, int b, int c, void *handler, int e, int *out);
extern void func_ov218_020ce48c(void);
void func_ov218_020ce430(int param_1) {
    int obj;
    func_0203c5c0(*(int *)(param_1 + 0x3c), 0x64, 0x48, (void *)&func_ov218_020ce48c, 0, &obj);
    *(int *)obj = param_1;
    *(int *)(obj + 4) = *(int *)(*(int *)obj + 0x384);
    *(int *)(param_1 + 0x214) = obj;
}
