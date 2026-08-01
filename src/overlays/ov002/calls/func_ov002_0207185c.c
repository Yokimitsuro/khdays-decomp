/*
 * Ov002_AllocSceneState - allocate and zero/fill-initialise the ov002 scene-state object at
 * data_ov002_0207fa10. Dep of the gameplay constructor func_ov002_020679d4.
 *
 * Allocates 0x2340 bytes, publishes the pointer to data_ov002_0207fa10, then sets its header
 * fields: word fields at 0/4/8 = 0, the two index bytes at 0xc/0xd = -1, assorted flag bytes to 0,
 * clears several sub-regions (obj+0x34 .. and obj+0x58/0x7c/0x22a0/0x22b0 via CpuClear32, plus the
 * MI_CpuFill8 runs), and walks the 0x20-entry table (stride 0x10c) clearing the byte at +0x21c of
 * each entry. Finishes with the 0xff fill runs at obj+0x17/0x2f/0xf and the byte/word at
 * obj+0x2298/0x2294.
 *
 * THUMB. The table walk uses a pointer cursor (single accumulator obj + i*0x10c, byte written at
 * +0x21c) rather than an index*stride expression, matching the original's strength-reduced form.
 * The -1 index bytes (0xc/0xd/0x2298) are stored through signed char so the compiler keeps -1 as a
 * full 0xffffffff (subs/mvns from the live zero) instead of materialising 0xff; that in turn stops
 * it from deriving the 0x104/0x105/0x110 offsets by adding to a 0xff register and forces the
 * 0x41<<2 materialisation the original uses.
 */

typedef unsigned char u8;

extern int  data_ov002_0207fa10;
extern int  NNSi_FndAllocFromDefaultExpHeap(int size);
extern void INITi_CpuClear32_0x01ff86fc(int data, void *dest, int size);
extern void MI_CpuFill8(void *dest, int data, int size);

void func_ov002_0207185c(void)
{
    char *obj = (char *)NNSi_FndAllocFromDefaultExpHeap(0x8d << 6);
    int i;

    data_ov002_0207fa10 = (int)obj;
    *(int *)(obj + 8) = 0;
    *(int *)(obj + 0) = 0;
    *(signed char *)(obj + 0xc) = -1;
    *(int *)(obj + 4) = 0;
    *(signed char *)(obj + 0xd) = -1;
    *(u8 *)(obj + 0xe) = 0;
    *(u8 *)(obj + 0x104) = 0;
    *(u8 *)(obj + 0x105) = 0;
    *(u8 *)(obj + 0x54) = 0;
    *(u8 *)(obj + 0x110) = 0;
    INITi_CpuClear32_0x01ff86fc(0, obj + 0x34, 0x20);
    INITi_CpuClear32_0x01ff86fc(0, obj + 0x108, 8);
    *(u8 *)(obj + 0x111) = 0;
    {
        char *p = obj;
        for (i = 0; i < 0x20; i++) {
            *(u8 *)(p + 0x21c) = 0;
            p += 0x10c;
        }
    }
    *(signed char *)(obj + 0x2298) = -1;
    *(int *)(obj + 0x2294) = 0;
    *(u8 *)(obj + 0x78) = 0;
    MI_CpuFill8(obj + 0xfc, 0, 4);
    INITi_CpuClear32_0x01ff86fc(0, obj + 0x58, 0x20);
    INITi_CpuClear32_0x01ff86fc(0, obj + 0x7c, 0x80);
    INITi_CpuClear32_0x01ff86fc(0, obj + 0x22a0, 0x10);
    INITi_CpuClear32_0x01ff86fc(0, obj + 0x22b0, 0x10);
    MI_CpuFill8(obj + 0x22c0, 0, 0x80);
    MI_CpuFill8(obj + 0x17, 0xff, 0x18);
    MI_CpuFill8(obj + 0x2f, 0xff, 4);
    MI_CpuFill8(obj + 0xf, 0xff, 4);
}
