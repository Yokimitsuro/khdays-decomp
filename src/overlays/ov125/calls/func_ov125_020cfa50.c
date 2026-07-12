/* Spawn a child object via func_0203c5c0 (callback ov125_020cfaac), link it back to this object,
 * copy *(child)+0x9c into the child's +4 field and store it at +0x214. */
extern int func_0203c5c0(int a, int b, int c, void *cb, int flag, int *out);
extern void func_ov125_020cfaac(int);
void func_ov125_020cfa50(int param_1) {
    int obj;
    func_0203c5c0(*(int *)(param_1 + 0x3c), 0x64, 0x20, (void *)&func_ov125_020cfaac, 0, &obj);
    *(int *)obj = param_1;
    *(int *)(obj + 4) = *(int *)(*(int *)obj + 0x9c);
    *(int *)(param_1 + 0x214) = obj;
}
