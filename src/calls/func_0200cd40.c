extern int PXIi_TryLock(void);
extern void PXIi_SendCommand(unsigned int cmd);

struct CC {
    char _0[0x20];
    int field_20;
    int field_24;
};
extern struct CC data_020463cc;

int func_0200cd40(unsigned int arg0, int arg1, int arg2)
{
    if (PXIi_TryLock() == 0) return 1;
    data_020463cc.field_20 = arg1;
    data_020463cc.field_24 = arg2;
    PXIi_SendCommand(((arg0 >> 16) & 0xff) | 0x02006300);
    PXIi_SendCommand(0x01010000 | (arg0 & 0xffff));
    return 0;
}
