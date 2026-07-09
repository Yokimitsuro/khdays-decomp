extern int func_02030788(void);
extern int *func_020315c0(int);
int func_ov008_0206b7f8(void)
{
    int *entry = func_020315c0(func_02030788());
    if (entry != 0) {
        return entry[1];
    }
    return 0;
}
