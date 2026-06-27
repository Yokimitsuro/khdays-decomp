extern int PXIi_TryLock(void);
extern void PXIi_SendCommand(unsigned int cmd);

struct CC {
    char _0[0x20];
    int field_20;
    int field_24;
};
extern struct CC data_020463cc;

int PXIi_SendCmd0x64(int arg0, int arg1, int arg2, int arg3)
{
    if (PXIi_TryLock() == 0) return 1;
    data_020463cc.field_20 = arg2;
    data_020463cc.field_24 = arg3;
    PXIi_SendCommand((arg0 & 0xff) | 0x02006400);
    PXIi_SendCommand(0x01010000 | (arg1 & 0xffff));
    return 0;
}
