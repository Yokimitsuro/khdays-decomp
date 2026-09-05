/* Registered hit handler. Refuses the hit once the actor's hit points are
   spent; otherwise it applies the damage the shared helper computes, clamps the
   remaining points into [0, cap], and plays one of two alternating impact
   sounds unless the event is the specific flag combination that suppresses
   them. Requests state 3 when the points run out, state 6 while the owner is
   already in state 5 or 6, and state 5 for a flagged hit otherwise.

   Same routine as the matched ov128 handler, minus its busy-bit gate: this one
   writes the subtraction straight back to the field and reads it again for the
   clamp, which is what puts the two loads either side of the store.

   The state test is written double-negated because 5 and 6 are consecutive:
   spelled as an ordinary pair of equalities mwcc range-reduces it to
   (unsigned)(x - 5) <= 1, and the ROM keeps the cmp/cmpne cascade. */

typedef unsigned char u8;
typedef unsigned short u16;

struct HitState {
    char *pOwner;
    char pad04[8];
    void *pAt0c;
    char pad10[0x48];
    u8 bToggle58;
};

struct HitFlags { unsigned int lo : 16, hi : 16; };

struct HitMsg {
    unsigned int uFlags;
    char pad04[0x24];
    int nDamage28;
};

/* The two sound ids of one impact kind, copied out of the table as a unit so
   the alternating counter can pick between them. */
struct ImpactPair { u8 nFirst; u8 nSecond; };
union ImpactSlot { struct ImpactPair sPair; u8 aModes[2]; };

extern int func_ov107_020c89e8(char *actor, struct HitMsg *msg);
extern void func_ov107_020c5af8(char *actor, int nId, u8 nMode, void *pAt);

/* Four bytes: the loud pair at 0, the quiet pair at 2. */
extern const u8 data_ov292_020d48b8[];

int func_ov292_020d3c38(char *actor, int nSource, struct HitMsg *msg)
{
    struct HitState *hs;
    int nLeft;
    int nNext;

    hs = *(struct HitState **)(actor + 0x214);
    if (*(short *)(actor + 0x21a) <= 0) {
        return 0;
    }

    nLeft = func_ov107_020c89e8(actor, msg);
    msg->nDamage28 = nLeft;
    *(short *)(actor + 0x21a) = (short)(*(short *)(actor + 0x21a) - nLeft);

    nNext = *(short *)(actor + 0x218);
    nLeft = *(short *)(actor + 0x21a);
    if (nLeft <= nNext) {
        if (nLeft < 0) {
            nLeft = 0;
        }
        nNext = nLeft;
    }
    *(short *)(actor + 0x21a) = (short)nNext;

    if (msg->nDamage28 > 0) {
      struct HitFlags *hf = (struct HitFlags *)msg;
      if ((hf->lo & 8) == 0 || (hf->lo & 0x80) == 0 || hf->hi != 0x80) {
        if ((hf->lo & 0x22) != 0) {
            union ImpactSlot uSlot;

            uSlot.sPair = *(const struct ImpactPair *)&data_ov292_020d48b8[0];
            hs->bToggle58++;
            func_ov107_020c5af8(actor, 0x175, uSlot.aModes[hs->bToggle58 & 1],
                                hs->pAt0c);
        } else {
            union ImpactSlot uSlot;

            uSlot.sPair = *(const struct ImpactPair *)&data_ov292_020d48b8[2];
            hs->bToggle58++;
            func_ov107_020c5af8(actor, 0x175, uSlot.aModes[hs->bToggle58 & 1],
                                hs->pAt0c);
        }
      }
    }

    if (*(short *)(actor + 0x21a) == 0) {
        *(u8 *)(hs->pOwner + 0x1c7) = 3;
    } else if (!(*(signed char *)(hs->pOwner + 0x1c6) != 5 &&
                 *(signed char *)(hs->pOwner + 0x1c6) != 6)) {
        *(u8 *)(hs->pOwner + 0x1c7) = 6;
    } else if ((((struct HitFlags *)msg)->lo & 0x8000) != 0) {
        *(u8 *)(hs->pOwner + 0x1c7) = 5;
    }
    return 1;
}
