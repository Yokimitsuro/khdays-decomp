extern int func_02030788(void);
extern int *func_020315c0(int);
int func_ov008_0208bed8(void)
{
    int *entry = func_020315c0(func_02030788());
    if (entry == 0) {
        return -1;
    }
    return entry[1];
}
