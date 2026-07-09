extern void func_ov008_02055874(void *context, void *entry, int arg2, int arg3);
extern void func_ov008_0205589c(void *context, void *entry);

void func_ov008_020558b8(void *context, void *entry, int arg2, int arg3)
{
    int x = *(short *)((char *)entry + 2);
    int y = *(short *)((char *)entry + 4);

    func_ov008_02055874(context, entry, arg2, arg3);
    func_ov008_0205589c(context, entry);
    func_ov008_02055874(context, entry, x, y);
}
