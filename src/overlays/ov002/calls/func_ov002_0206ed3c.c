/* Deliver the event unless the addressed slot is muted. Bit 12 of the id marks
 * it as slot-addressed; the rest of the id is the slot index into the table at
 * +0x1ac. A muted slot (top bit of the byte at +0x15) swallows the event and
 * reports 0; everything else is delivered and reports 1. */
extern void func_ov002_0206e99c(int id);

typedef struct {
    char pad0000[0x15];
    signed char bLevel : 7;     /* +0x15 bits 0-6 */
    signed char bMuted : 1;     /* +0x15 bit 7 */
} Ov002EventSlot;

typedef struct {
    char pad0000[0x1ac];
    Ov002EventSlot *slots[1];   /* +0x1ac */
} Ov002EventContext;

extern Ov002EventContext *data_ov002_0207fa04;

int func_ov002_0206ed3c(int id) {
    Ov002EventContext *ctx = data_ov002_0207fa04;

    if ((id & 0x1000) != 0) {
        Ov002EventSlot *slot = ctx->slots[id & ~0x1000];

        if (slot != 0 && slot->bMuted != 0) {
            return 0;
        }
    }

    func_ov002_0206e99c(id);
    return 1;
}
