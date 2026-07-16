extern void func_ov002_02054850(void *context, void *entry, int arg2, int arg3);
extern void func_ov002_02054878(void *context, void *entry);

void func_ov002_02054894(void *context, void *entry, int arg2, int arg3)
{
    int x = *(short *)((char *)entry + 2);
    int y = *(short *)((char *)entry + 4);

    func_ov002_02054850(context, entry, arg2, arg3);
    func_ov002_02054878(context, entry);
    func_ov002_02054850(context, entry, x, y);
}
