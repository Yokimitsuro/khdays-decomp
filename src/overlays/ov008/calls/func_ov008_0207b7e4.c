extern int func_02030640(void);
extern int func_01fff974(void);
extern int OS_IsTickAvailable_0x01ff8138(void);
extern void func_ov008_0207bc94(void *value);

void func_ov008_0207b7e4(void)
{
    unsigned short value;

    if (func_02030640() != 0) {
        value = func_01fff974();
    } else {
        value = OS_IsTickAvailable_0x01ff8138();
    }

    func_ov008_0207bc94(&value);
}
