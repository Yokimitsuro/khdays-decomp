/* Sets or clears attachment slot `slot` of an actor.
 *
 * kind 0 on a live slot destroys the slot's created item and frees the
 * 0x1c-byte slot record.  Otherwise the record is allocated on demand, tagged
 * with kind, given a position (the caller's, or the zero vector) and field_10,
 * and when the per-slot/per-kind table names a resource (not -1), an item is
 * created from a handle packed out of the actor manager's +0x88 sprite set and
 * that resource (the same packing as func_ov107_020c9440), flagged with bit 1
 * at +0x5c, and the table's two parameter bytes are copied in.  Slot 2 is
 * mirrored into slot 3.
 *
 * The table is read-only (nothing in the ROM writes it); declaring it const is
 * what lets mwcc schedule its loads past the stores into the slot record. */
typedef struct {
    int x;
    int y;
    int z;
} Vec3;

typedef struct {
    char pad_00[0x5c];
    unsigned int flags_5c;
} CreatedItem;

typedef struct {
    unsigned int kind:4;
    Vec3 pos;                 /* +0x04 */
    int field_10;             /* +0x10 */
    CreatedItem *item;        /* +0x14 */
    unsigned char field_18;   /* +0x18 */
    unsigned char field_19;   /* +0x19 */
} Slot;

typedef struct {
    char pad_00[0x350];
    Slot *slots[8];           /* +0x350 */
} Obj;

typedef struct {
    char pad_00[0x88];
    unsigned int spriteSet_88;
} ActorManager;

typedef struct {
    int resource;             /* -1: no item for this slot/kind */
    unsigned char field_4;
    unsigned char field_5;
    char pad_6[2];
} SlotKindInfo;

extern ActorManager *OS_IsThreadAvailable_0x020c9848(void);
extern void func_0203c7e8(CreatedItem *item);
extern void func_0203d194(void *p);
extern void *func_0203d15c(unsigned int size);
extern CreatedItem *func_0203b898(unsigned int handle);

extern const Vec3 data_02041dc8;
extern const SlotKindInfo data_ov107_020cb9a4[][4];

void func_ov107_020c92b0(Obj *self, int slot, unsigned int kind, Vec3 *pos, int field10)
{
    unsigned int spriteSet = OS_IsThreadAvailable_0x020c9848()->spriteSet_88;
    Slot *entry;
    Vec3 v;
    int resource;

    if (kind == 0 && self->slots[slot] != 0) {
        if (self->slots[slot]->item != 0) {
            func_0203c7e8(self->slots[slot]->item);
            self->slots[slot]->item = 0;
        }
        func_0203d194(self->slots[slot]);
        self->slots[slot] = 0;
        return;
    }

    if (self->slots[slot] == 0) {
        self->slots[slot] = func_0203d15c(0x1c);
    }
    entry = self->slots[slot];
    entry->kind = kind;
    if (pos != 0) {
        v = *pos;
    } else {
        v = data_02041dc8;
    }
    entry->pos = v;
    entry->field_10 = field10;

    resource = data_ov107_020cb9a4[slot][kind].resource;
    if (resource != -1) {
        unsigned int mask = 0xfffffc;
        entry->item = func_0203b898((((spriteSet + 0x8000) & mask) << 7 | 0x80000000)
                                    | (resource & (mask >> 15)));
        entry->item->flags_5c |= 2;
        entry->field_18 = data_ov107_020cb9a4[slot][kind].field_4;
        entry->field_19 = data_ov107_020cb9a4[slot][kind].field_5;
    }

    if (slot == 2) {
        func_ov107_020c92b0(self, 3, kind, pos, field10);
    }
}
