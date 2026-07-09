extern char *data_ov008_02090f24;
extern int OS_IsTickAvailable(void);

void func_ov008_0207bbd4(int value)
{
    *(unsigned char *)(data_ov008_02090f24 + 0x42a) = value;

    if (OS_IsTickAvailable() == 0) {
        *(unsigned char *)(data_ov008_02090f24 + OS_IsTickAvailable() + 0x48e) = value;
    }
}
