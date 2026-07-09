extern int func_ov008_02050c64(void *object);
extern void func_ov008_02054e74(int arg0, void *out);

void func_ov008_02072fb4(void *object)
{
    int state[2];

    func_ov008_02054e74(func_ov008_02050c64(object), state);

    if (*(unsigned short *)((char *)state + 4) != 1) {
        *(int *)((char *)object + 0x34) = 0;
    }
}
