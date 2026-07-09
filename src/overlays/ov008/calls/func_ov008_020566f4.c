extern void func_ov008_02056418(void *);
extern void func_ov008_02056478(void *, int, int);
void func_ov008_020566f4(char *obj, int value)
{
    func_ov008_02056418(obj);
    func_ov008_02056478(obj, *(int *)(obj + 0xc), value);
}
