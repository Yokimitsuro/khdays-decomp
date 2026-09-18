/* Drives the ov032 enemy's effect block state machine (and its byte-identical twins). A
 * running block whose owner (+0x22f8) is no longer busy goes idle. State 1 waits for the
 * +0x7b0 timer to reach 0x1d000, then restarts sequences 0, 2 and 1 from zero and advances
 * to 2; states 2 and 4 poll the block against the +0x2aba rate, 4 ending in state 5 once
 * the poll reports done. */
typedef unsigned char u8;

extern int func_ov022_02095524(void *p);
extern void func_01fff774(void *p, int idx, int a);
extern unsigned int func_0202a818(void *p, int rate);

void func_ov072_020b9ac4(int self, char *block)
{
    if (*(u8 *)(block + 0x114) != 0 && func_ov022_02095524((void *)(self + 0x22f8)) == 0) {
        *(u8 *)(block + 0x114) = 0;
    }
    switch (*(u8 *)(block + 0x114)) {
    case 1:
        if (*(int *)(self + 0x7b0) < 0x1d000) {
            return;
        }
        func_01fff774(block + 0xc, 0, 0);
        func_01fff774(block + 0xc, 2, 0);
        func_01fff774(block + 0xc, 1, 0);
        *(u8 *)(block + 0x114) = 2;
        return;
    case 2:
        func_0202a818(block + 0xc, *(short *)(self + 0x2aba));
        return;
    case 4:
        if (func_0202a818(block + 0xc, *(short *)(self + 0x2aba)) != 0) {
            *(u8 *)(block + 0x114) = 5;
        }
        return;
    }
}
