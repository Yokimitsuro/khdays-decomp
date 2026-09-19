/* Opens the mission owner's +0x2d38 block for this enemy: clears the +0x11c request and the two
 * row heads at +0x12c (stride 0x240), binds data_ov043_020b589c on the +0x10 request, then for
 * each of the 2 rows binds data_ov043_020b58b0 on its 2 requests (+0x130, stride 0x108) and
 * seeds the row's +0x2e8/+0x2ec/+0x2f0 triple (0x1333, then overwritten with 0xccd). Finally
 * the enemy's secondary sub-object is opened (51ec).
 *
 * THUMB. The owner pointer is read once into a local (r7); the block base and the row cursor
 * live in r6 / [sp+8] with the outer counter spilled at [sp+4]. The counters are declared
 * first (lowest registers) and the outer loop steps row, block, counter in that order -- the
 * row's 0x240 takes the copied constant, the block's the in-place one. */
extern void func_0202a634(void *req, void *script, int c, int rate);
extern void func_ov043_020b51ec(int self);
extern char *data_ov043_020b58e0;
extern int data_ov043_020b589c;
extern int data_ov043_020b58b0;

void func_ov043_020b4734(int self)
{
    char *owner = data_ov043_020b58e0;
    char *blk = owner + 0x2d38;
    int i;
    int j;
    char *row;
    char *p;

    *(int *)(blk + 0x11c) = 0;
    for (i = 0, p = blk; i < 2; i++, p += 0x240) {
        *(int *)(p + 0x12c) = 0;
    }
    func_0202a634(blk + 0x10, &data_ov043_020b589c, 1, *(unsigned char *)(owner + 9) + 7);
    for (i = 0, row = blk + 0x130; i < 2; i++) {
        for (j = 0, p = row; j < 2; j++, p += 0x108) {
            func_0202a634(p, &data_ov043_020b58b0, 1, *(unsigned char *)(owner + 9) + 7);
        }
        *(int *)(blk + 0x2e8) = *(int *)(blk + 0x2ec) = *(int *)(blk + 0x2f0) = 0x1333;
        *(int *)(blk + 0x2e8) = *(int *)(blk + 0x2ec) = *(int *)(blk + 0x2f0) = 0xccd;
        row += 0x240;
        blk += 0x240;
    }
    func_ov043_020b51ec(self);
}
