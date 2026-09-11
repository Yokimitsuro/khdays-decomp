typedef unsigned int u32;
typedef unsigned short u16;
typedef short s16;

extern int OS_IsThreadAvailable_0x020c9848(void);
extern void *func_0201ef9c(u32 flags, int heap);
extern int func_02020400(int value, int percent);
extern void NNSi_FndFreeFromDefaultHeap(void *p);

void func_ov107_020c8958(char *self, u32 mask) {
    int ctx = OS_IsThreadAvailable_0x020c9848();
    u32 table = *(u32 *)(ctx + 0x84);
    u32 flags = (((table + 0x8000) & 0xfffffc) << 7) | 0x80000000u | (((u32)0xfffffc >> 15) & mask);
    char *allocBase = (char *)func_0201ef9c(flags, 0xb);
    char *src = allocBase;
    int i;
    char buf[8];
    for (i = 0; i < 5; i++) {
        *(u16 *)(buf + 6) = *(u16 *)(src + 0);
        *(int *)(self + 0x314) = func_02020400((int)*(s16 *)(buf + 6) << 4, 100);
        *(u16 *)(buf + 4) = *(u16 *)(src + 2);
        *(int *)(self + 0x318) = func_02020400((int)*(s16 *)(buf + 4) << 4, 100);
        *(u16 *)(buf + 0) = *(u16 *)(src + 4);
        *(u16 *)(buf + 2) = *(u16 *)(src + 4);
        src += 6;
        *(int *)(self + 0x31c) = func_02020400((int)*(s16 *)(buf + 2) << 4, 100);
        self += 0xc;
    }
    NNSi_FndFreeFromDefaultHeap(allocBase);
}
