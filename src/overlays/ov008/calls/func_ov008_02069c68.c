extern int func_ov008_02050c54(void);
extern void func_ov008_02054d3c(int arg0, int arg1, int arg2);
extern void func_ov008_02054c80(int arg0, int arg1, int arg2);
extern void func_ov008_02054c08(int arg0, int arg1);

void func_ov008_02069c68(void *object)
{
    int value = func_ov008_02050c54();

    func_ov008_02054d3c(value, *(int *)((char *)object + 4), 1);
    func_ov008_02054c80(value, *(int *)((char *)object + 4), 0);
    func_ov008_02054c08(value, *(int *)((char *)object + 4));
}
