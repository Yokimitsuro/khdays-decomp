/*
 * [nonmatching: dead `& 0` flag term — unreproducible from clean C]
 *
 * When global flag data_0204c240 bit2 is clear and *(arg1+0x179)==1, and the
 * node's field[0x11a] bit2 is clear, sets bit 0x80000 in the node's word 0.
 *
 * The original's second guard is `(field[0x11a] & 4) != 0 || (field[0x119] & K)
 * != 0` where K is a build-time 0-valued flag macro: the compiler emitted
 * `ldr; and r1,r1,#0; cmp r1,#0` (a live load AND'd with a zeroed register),
 * and reused that held 0 for a trailing `field[1] = field[1] | 0` self-store.
 * mwcc 3.0/139 constant-folds ANY literal `& 0` we write (even through
 * volatile), dropping both the load and the self-store. Without the original
 * header's 0-valued macro the term cannot be reproduced, so this is left
 * uncarved (byte-exact in the blob); the clean C below omits the always-false
 * term and the resulting no-op store.
 */
extern int data_0204c240;

void func_ov022_0209a630(int arg0, int arg1) {
    unsigned int *p = *(unsigned int **)(arg0 + 0x18c);
    if ((*(unsigned char *)&data_0204c240 & 4) != 0) return;
    if (*(unsigned char *)(arg1 + 0x179) != 1) return;
    if ((p[0x11a] & 4) != 0) return;
    *p |= 0x80000;
}
