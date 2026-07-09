extern void func_02030788(void *arg0);
extern int *func_020315c0(void);
extern int data_ov008_0208e8a4[];

int func_ov008_02051b20(int *out)
{
    int result = 0xa;
    int *entry;

    func_02030788(out);
    entry = func_020315c0();

    if (entry != 0) {
        result = data_ov008_0208e8a4[entry[1]];
    }

    if (out != 0) {
        *out = entry[1];
    }

    return result;
}
