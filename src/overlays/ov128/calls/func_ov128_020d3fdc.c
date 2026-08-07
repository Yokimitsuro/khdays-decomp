/* Registered hit handler. Refuses the hit while the actor's busy bit is set or
   its hit points are already spent; otherwise it applies the damage the shared
   helper computes, clamps the remaining points into [0, cap], records the
   source, and plays one of two alternating impact sounds unless the event is
   the specific flag combination that suppresses them. Requests state 3 when the
   points run out and state 6 otherwise. */

typedef unsigned char u8;
typedef unsigned short u16;

struct HitState {
    char *pOwner;
    char pad04[8];
    int nSource0c;
    void *pAt10;
    char pad14[0x2c];
    u8 bToggle40;
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
extern const u8 data_ov128_020d4fc4[];

int func_ov128_020cc75c(char *actor, int nSource, struct HitMsg *msg)
{
    struct HitState *hs;
    int nLeft;
    int nNext;

    hs = *(struct HitState **)(actor + 0x214);
    if ((*(u16 *)(actor + 0x1ac) & 1) != 0) {
        return 0;
    }
    if (*(short *)(actor + 0x21a) <= 0) {
        return 0;
    }

    nLeft = func_ov107_020c89e8(actor, msg);
    msg->nDamage28 = nLeft;
    nLeft = *(short *)(actor + 0x21a) - nLeft;
    if (nLeft < 0) {
        nNext = 0;
    } else {
        nNext = *(short *)(actor + 0x218);
        if (nLeft <= *(short *)(actor + 0x218)) {
            nNext = nLeft;
        }
    }
    *(short *)(actor + 0x21a) = (short)nNext;
    hs->nSource0c = nSource;

    if (msg->nDamage28 > 0) {
      struct HitFlags *hf = (struct HitFlags *)msg;
      if ((hf->lo & 8) == 0 || (hf->lo & 0x80) == 0 || hf->hi != 0x80) {
        if ((hf->lo & 0x22) != 0) {
            union ImpactSlot uSlot;

            uSlot.sPair = *(const struct ImpactPair *)&data_ov128_020d4fc4[0];
            hs->bToggle40++;
            func_ov107_020c5af8(actor, 0x118, uSlot.aModes[hs->bToggle40 & 1],
                                hs->pAt10);
        } else {
            union ImpactSlot uSlot;

            uSlot.sPair = *(const struct ImpactPair *)&data_ov128_020d4fc4[2];
            hs->bToggle40++;
            func_ov107_020c5af8(actor, 0x118, uSlot.aModes[hs->bToggle40 & 1],
                                hs->pAt10);
        }
      }
    }

    if (*(short *)(actor + 0x21a) == 0) {
        *(u8 *)(hs->pOwner + 0x1c7) = 3;
        return 1;
    }
    *(u8 *)(hs->pOwner + 0x1c7) = 6;
    return 1;
}
