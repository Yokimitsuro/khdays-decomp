/* NONMATCHING: semantically complete, register-alloc tie in the setup. Body (struct copy via
 * ldm/stm, resolved-value stores, draw call, flag guard) matches; only the 8-instruction
 * prologue differs -- ROM loads the global (r1/r2 temporaries) before copying index to r5,
 * mwcc copies index first and uses r0/r1. Inline vs base-variable forms both leave it.
 * Behaviour: fill slot obj[0x8bd0][index*0x44] -- 3-word header from func_ov022_020881f8,
 * value at +0xc, tail at +0x10 via func_ov002_020726a0; func_02035c60 once when flag bit2
 * is clear and index==0. */
typedef struct {
    int a;
    int b;
    int c;
} SlotHeader;

extern int *data_ov002_0207fa00;
extern unsigned char data_0204c240;
extern SlotHeader *func_ov022_020881f8(void);
extern int func_ov022_02088254(int index);
extern int func_ov022_02088474(int index);
extern void func_ov002_020726a0(int id, int *unused, void *out);
extern void func_02035c60(void);

void func_ov002_02069b14(int index) {
    int *slot = (int *)(*(int *)((int)data_ov002_0207fa00 + 0x8bd0) + index * 0x44);
    SlotHeader *src = func_ov022_020881f8();

    *(SlotHeader *)slot = *src;
    slot[3] = func_ov022_02088254(index);
    func_ov002_020726a0(func_ov022_02088474(index), 0, slot + 4);

    if ((data_0204c240 & 4) == 0 && index == 0) {
        func_02035c60();
    }
}
