/* Expire the entry once its deadline has passed. The deadline is a 64-bit tick
 * count at +0x24, compared against the current tick with the usual cmp/cmpeq
 * pair -- high words first, low words only if the high words agree. */
extern unsigned long long func_020031d4(void);
extern void func_ov002_0205a1d4(void *self, int reason);

typedef struct {
    char pad0000[0x24];
    unsigned long long qwDeadline;  /* +0x24 */
} Ov002TimedEntry;

void func_ov002_02059d48(Ov002TimedEntry *self) {
    if (self->qwDeadline > func_020031d4()) {
        return;
    }

    func_ov002_0205a1d4(self, 1);
}
