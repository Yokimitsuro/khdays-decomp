/* RunClassConstructor(obj, desc, ctorArg): build a 0x2c-byte task object from the class
 * descriptor, link it into the global object list (data_0204c058+4), then run the
 * descriptor's constructor with `obj` as the current object; the ctor's return becomes the
 * object's initial per-frame state fn (obj+0x14). Descriptor: +0/+2 u16 magics, +4 ctor,
 * +8 method, +0xc auxSize, +0x10 arenaRef. */
extern int func_0202362c(int arena);
extern void *func_020236cc(int size, int arena);
extern void MI_CpuFill8(void *dst, int val, int n);
extern void func_02023778(int obj);
extern char data_0204c058;

int *func_02023960(int *obj, unsigned short *desc, int ctorArg) {
    int def, saved, token;
    obj[0] = 0;
    obj[1] = ((int *)&data_0204c058)[1];
    *(unsigned short *)((char *)obj + 0x10) = desc[0];
    *(unsigned short *)((char *)obj + 0x12) = desc[1];
    def = 0;
    if (*(int **)((char *)desc + 0x10) != 0) {
        def = **(int **)((char *)desc + 0x10);
    }
    obj[7] = def;
    obj[9] = *(int *)((char *)desc + 0xc);
    obj[5] = 0;
    obj[6] = *(int *)((char *)desc + 8);
    obj[10] = 0;
    token = func_0202362c(obj[7]);
    if (obj[9] == 0) {
        obj[8] = 0;
    } else {
        obj[8] = (int)func_020236cc(obj[9], obj[7]);
        MI_CpuFill8((void *)obj[8], 0, obj[9]);
    }
    func_02023778((int)obj);
    saved = ((int *)&data_0204c058)[1];
    ((int *)&data_0204c058)[1] = (int)obj;
    *(int *)(((int *)&data_0204c058)[1] + 0x14) =
        (*(int (**)(int))((char *)desc + 4))(ctorArg);
    ((int *)&data_0204c058)[1] = saved;
    func_0202362c(token);
    return obj;
}
