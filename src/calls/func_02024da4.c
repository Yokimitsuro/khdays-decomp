typedef unsigned short u16;

/* Four packed u16 fields; matches func_0200c92c's Rec layout (a touch-panel
 * calibration point). */
typedef struct {
    u16 field_00;
    u16 field_02;
    u16 field_04;
    u16 field_06;
} Rec;

extern int GX_GetBankForOBJExtPltt(void);
extern void func_0200c92c(Rec *out, Rec *in);
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int len);
extern Rec data_0204c1c4[];

int func_02024da4(Rec *table) {
    int bank;
    int i;
    short count = 0;

    if (!((*(volatile u16 *)0x027fffa8 & 0x8000) >> 15)) {
        Rec buf;

        bank = GX_GetBankForOBJExtPltt();
        i = 0;
        bank -= 3;

        for (; i < 4; i++) {
            int idx = bank + i;
            if (idx < 0) {
                idx += 5;
            }
            func_0200c92c(&buf, &data_0204c1c4[idx]);
            MI_CpuCopy8(&buf, &table[count++], 8);
        }
    }

    return count;
}
