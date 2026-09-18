/* Stops the ov032 enemy's effect block (and its byte-identical twins) from states 1/2: enters
 * state 4, fires cue 0xc5 with situation 0 (index 1) or 1 (index 2) by `alt`, retimes sequences
 * 0, 2 and 1 against the owner's +0x22f8 period with that index and restarts them from zero. */
typedef unsigned char u8;
typedef unsigned short u16;

extern void func_ov022_020a4490(int self, int cue, int situation);
extern int func_ov022_0209560c(void *p);
extern void func_0202accc(void *p, u16 idx, int a, short b);
extern void func_01fff774(void *p, u16 idx, int a);

void func_ov032_020b4ae8(int self, u8 *block, int alt)
{
    int idx;

    if ((u8)(block[0x114] + 0xff) > 1) {
        return;
    }
    block[0x114] = 4;
    if (alt == 0) {
        idx = 1;
        func_ov022_020a4490(self, 0xc5, 0);
    } else {
        idx = 2;
        func_ov022_020a4490(self, 0xc5, 1);
    }
    func_0202accc(block + 0xc, 0, func_ov022_0209560c((void *)(self + 0x22f8)), idx);
    func_0202accc(block + 0xc, 2, func_ov022_0209560c((void *)(self + 0x22f8)), idx);
    func_0202accc(block + 0xc, 1, func_ov022_0209560c((void *)(self + 0x22f8)), idx);
    func_01fff774(block + 0xc, 0, 0);
    func_01fff774(block + 0xc, 2, 0);
    func_01fff774(block + 0xc, 1, 0);
}
