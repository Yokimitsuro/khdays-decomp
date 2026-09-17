/* Resets the ov042 enemy's seven sequence slots (x4: ov042/061/081/098): clears the slot
 * array's active count at +0x2c2c, zeroes every slot's phase word, registers each slot's
 * sequence with the shared descriptor under the enemy's type + 7, then runs the per-slot
 * setup.
 *
 * Levers: loop 1 indexes the slot array (slots[i].phase = 0 -- the hoisted zero is then shared
 * with the second loop's counter), loop 2 walks a plain pointer to the sequence bumped by
 * sizeof(slot), and ONE counter variable serves both loops (two counters swap self/j between
 * r4 and r5). */
typedef unsigned char u8;

typedef struct {
    char pad00[0x14];
    int phase;              /* 0x14 */
    char sequence[0xf4];    /* 0x18 */
} Ov042SeqSlot;             /* 0x10c */

extern void func_0202a634(void *sequence, void *descriptor, int a, int index);   /* RegisterSeqAndInit */
extern void func_ov042_020b3e20(char *self);
extern char *data_ov042_020b4800;
extern char data_ov042_020b47b4[];

void func_ov042_020b3d34(void)
{
    char *self = data_ov042_020b4800;
    Ov042SeqSlot *slots = (Ov042SeqSlot *)(self + 0x2c + 0x2c00);
    char *seq;
    int i;

    *(int *)(self + 0x2c2c) = 0;
    for (i = 0; i < 7; i++) {
        slots[i].phase = 0;
    }
    seq = slots[0].sequence;
    for (i = 0; i < 7; i++) {
        func_0202a634(seq, data_ov042_020b47b4, 1, *(u8 *)(self + 9) + 7);
        seq += sizeof(Ov042SeqSlot);
    }
    func_ov042_020b3e20(self);
}
