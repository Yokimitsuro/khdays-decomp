/* Scene exit for the context published at data_ov002_0207f9f4's sibling slot:
 * when the party count at +0xc is more than one, hand the object at +0x10 back
 * through slot 0xc, run the two teardown steps and finally drop the global.
 * func_02030788 is called for its side effect only -- the ROM discards r0. */
extern int func_02030788(void);
extern void func_ov002_02053610(int handle, int slot);
extern void func_ov002_020662b8(void);
extern void func_ov002_020538a0(int a);

extern int data_ov002_0207f9f0;

void func_ov002_02066ba8(void) {
    int ctx = data_ov002_0207f9f0;

    func_02030788();
    if (*(int *)(ctx + 0xc) >= 2) {
        func_ov002_02053610(*(int *)(ctx + 0x10), 0xc);
    }
    func_ov002_020662b8();
    func_ov002_020538a0(0);
    data_ov002_0207f9f0 = 0;
}
