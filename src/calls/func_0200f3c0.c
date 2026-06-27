extern void CpuSet(const void *src, void *dst, unsigned ctrl);
extern int OS_GetLockID(void);

extern int data_02046d4c;
extern struct { char _pad[6]; unsigned short lockid; } data_02046d48;

void func_0200f3c0(void) {
    int zero = 0;
    CpuSet(&zero, &data_02046d4c, 0x05000001);
    data_02046d48.lockid = (unsigned short)OS_GetLockID();
}
