extern char *data_ov008_02090f24;
extern int OS_IsTickAvailable(void);

int func_ov008_0207bc10(void)
{
    return (unsigned char)*(data_ov008_02090f24 + OS_IsTickAvailable() + 0x48e);
}
