extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int mask);
extern void SND_StartTimer(unsigned int chBitMask, unsigned int capBitMask, unsigned int alarmBitMask, unsigned int reserved);
extern void func_0201ada0(void *obj, int arg);

struct obj_s {
    char pad00[0x24];
    unsigned int flags;     /* +0x24 */
    char pad28[0x38 - 0x28];
    int counter;            /* +0x38 */
    char pad3c[0x40 - 0x3c];
    unsigned int shift;     /* +0x40 */
    unsigned int chBitMask; /* +0x44 */
};

void func_0201ae9c(struct obj_s *obj)
{
    int mask;

    if (!((int)(obj->flags << 30) >> 31)) {
        return;
    }

    while (obj->counter != 0) {
        mask = OS_DisableInterrupts();
        func_0201ada0(obj, 1);
        OS_RestoreInterrupts(mask);
    }

    SND_StartTimer(obj->chBitMask, 0, 1 << obj->shift, 0);
}
