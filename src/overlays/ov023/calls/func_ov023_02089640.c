/* func_ov023_02089640 -- Ov023_ActorAttachToParent: hang an actor off a parent actor.  The
 * child gets flag bit 12 (+0x1a28), the parent bit 11 and one more child (+0x1a3c); the parent
 * link (+0) and the height offset (+0x15ac) are set.  An empty track name (data_ov023_0208a744)
 * leaves the parent without a track (+0x15b0 = -1); otherwise the track is found on the
 * parent's entity (+0x15e0; 02087510) and the entity's track pointer (+0x58 of its animation
 * control at +0x24) aimed at the parent's track table (+0xa9c). */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct Ov023AnimCtl {
    u32  nControl;            /* 0x00 */
    u8   pad_04[0x34 - 0x04];
    void *pTracks;            /* 0x34 */
} Ov023AnimCtl;

typedef struct Ov023Entity {
    int  nFlags;              /* 0x00 */
    u16  wFlags;              /* 0x04: the animation starts here */
    u8   pad_06[0x24 - 0x06];
    Ov023AnimCtl anim;        /* 0x24 */
} Ov023Entity;

typedef struct Ov023Actor {
    struct Ov023Actor *pParent; /* 0x0000 */
    u8   pad_0004[0xa9c - 0x4];
    u8   aTrack[0x15ac - 0xa9c]; /* 0x0a9c: the track table */
    int  nHeightOffset;       /* 0x15ac */
    int  nTrack;              /* 0x15b0 */
    u8   pad_15b4[0x15e0 - 0x15b4];
    Ov023Entity *pEntity;     /* 0x15e0 */
    u8   pad_15e4[0x1a28 - 0x15e4];
    int  nFlags;              /* 0x1a28 */
    u8   pad_1a2c[0x1a3c - 0x1a2c];
    int  nChildren;           /* 0x1a3c */
} Ov023Actor;

extern int func_0201fabc(const char *pA, const char *pB);          /* STD_CompareString */
extern int func_ov023_02087510(void *pAnim, char *pszTrack);       /* Ov023_FindAnimTrack */
extern char data_ov023_0208a744[];                                  /* "" */

void func_ov023_02089640(Ov023Actor *pActor, Ov023Actor *pParent, char *pszTrack, int nHeightOffset)
{
    pActor->nFlags |= 0x1000;
    pParent->nFlags |= 0x800;
    pParent->nChildren++;
    pActor->pParent = pParent;
    pActor->nHeightOffset = nHeightOffset;
    if (func_0201fabc(pszTrack, data_ov023_0208a744) == 0) {
        pParent->nTrack = -1;
        return;
    }
    pParent->nTrack = func_ov023_02087510(&pParent->pEntity->wFlags, pszTrack);
    pParent->pEntity->anim.pTracks = pParent->aTrack;
}
