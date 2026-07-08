extern void func_0203b9fc(void *obj, int state, short subitem, int value);
extern void func_0203c7ac(void *obj, int value);

void func_ov301_020cc1f0(int obj, int subitem, int value)
{
    func_0203b9fc(*(void **)(obj + 0x384), 2, subitem, value);
    func_0203b9fc(*(void **)(obj + 0x384), 0, subitem, value);
    func_0203c7ac(*(void **)(obj + 0x384), 0);
}
