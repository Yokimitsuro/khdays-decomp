/* ov022: set or clear one slot's claim on the actor.
 *
 * Setting ORs the slot's own pair of 64-bit masks into the actor's third flag
 * word; clearing just drops bit 0 of the slot's own flags. Either way nothing
 * happens unless the slot is enabled.
 *
 * The mask table is two 64-bit values, one per slot, copied onto the stack each
 * call because it is a local with an initialiser.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#define SLOT_STRIDE 0x164

#define ACTOR_FLAGS3(pActor) (*(unsigned long long *)(pActor)->aFlags3)

struct Slot {
    u8 pad000[0xa8];
    u8 nFlags;                   /* 0x0a8 */
    signed char bEnabled;        /* 0x0a9 */
    u8 pad0aa[SLOT_STRIDE - 0xaa];
};

struct Actor {
    u8 pad000[0x46c];
    u32 aFlags3[2];              /* 0x46c: halves of one 64-bit flag word */
    u8 pad474[0x88c];
    struct Slot aSlot[2];        /* 0xd00 */
};

struct MaskTable {
    unsigned long long aMask[2];
};

extern const struct MaskTable data_ov022_020b25f4;

void func_ov022_0209fb98(struct Actor *pActor, int nSlot, int bSet)
{
    struct MaskTable masks;

    masks = data_ov022_020b25f4;
    if (bSet != 0) {
        if (pActor->aSlot[nSlot].bEnabled != 0) {
            ACTOR_FLAGS3(pActor) |= masks.aMask[nSlot];
        }
    } else {
        if (pActor->aSlot[nSlot].bEnabled != 0) {
            pActor->aSlot[nSlot].nFlags &= ~1;
        }
    }
}
