extern void INITi_CpuClear32_0x01ff86fc(unsigned int value, void *dst, unsigned int size);
extern void DC_FlushRange(void *base, unsigned int size);
extern void SND_StartTimer(unsigned int chMask, unsigned int capMask, unsigned int alarmMask, unsigned int flags);

typedef struct {
    int active;          /* +0x00 */
    char _04[0x0c - 0x04];
    void *bufA;          /* +0x0c */
    void *bufB;          /* +0x10 */
    unsigned int size;   /* +0x14 */
    char _18[0x1c - 0x18];
    int flag1c;          /* +0x1c */
    char _20[0x24 - 0x20];
    unsigned int chMask; /* +0x24 */
    unsigned int capMask;/* +0x28 */
    int alarm;           /* +0x2c */
} Obj0201b0ec;

extern Obj0201b0ec data_0204acf8;

void func_0201b0ec(void)
{
    Obj0201b0ec *p = &data_0204acf8;

    if (p->active == 0) {
        return;
    }

    p->flag1c = 0;
    INITi_CpuClear32_0x01ff86fc(0, p->bufA, p->size);
    INITi_CpuClear32_0x01ff86fc(0, p->bufB, p->size);
    DC_FlushRange(p->bufA, p->size);
    DC_FlushRange(p->bufB, p->size);

    SND_StartTimer(p->chMask, p->capMask, p->alarm >= 0 ? 1 << p->alarm : 0, 0);
}
