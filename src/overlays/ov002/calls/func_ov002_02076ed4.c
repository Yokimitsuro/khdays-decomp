typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;

typedef struct Ov002PieceClass {
    char pad000[0x58];
    char aName[0x10];           /* +0x58 */
    s16 nRequestA;              /* +0x68, negative means the class has none */
} Ov002PieceClass;

typedef struct Ov002PieceElement {
    char pad000[8];
    Ov002PieceClass *pOwner;    /* +0x08 */
    char pad00c[8];
    u16 wRequestId;             /* +0x14 */
    u8 bRequestSlot;            /* +0x16 */
    char pad017[1];
    u16 nAngle;                 /* +0x18 */
    char pad01a[0x12];
    char aNode[0xc];            /* +0x2c */
    int nNodeFlags;             /* +0x38 */
    u16 wAnimFlags;             /* +0x3c */
    char pad03e[0x7a];
    u16 nHomeAngle;             /* +0xb8 */
    char pad0ba[0xfc];
    u8 bDropsOn : 1;            /* +0x1b6 bit 0 */
    u8 nReplays : 7;            /* +0x1b6 bits 1..7 */
} Ov002PieceElement;

extern void *func_ov002_0206da70(char *pName);      /* name -> resource entry */
extern void func_0202b930(char *pObj, void *pEntry, int nA, int nB);
extern int func_ov002_0207c6c0(u16 *pAnim);         /* how many tracks it has */
extern int func_020235d0(u16 nId, u8 nSlot);   /* low bit gates the node */
extern void func_0202bedc(char *pObj, int bOn);
extern void func_0203355c(int nRequestId);

/* Builds one piece as it comes on stage: the class name picks the model, the
   node is bound to it, and the animation is asked how many tracks it carries so
   the replay count is right for whatever was loaded.
   The first build also remembers the angle the piece was placed at, guarded
   by bit 5 so a rebuild keeps the original.
   Whether the node starts enabled comes from the low bit of the request query,
   and a class carrying a request id reissues it on the way out. */
void func_ov002_02076ed4(Ov002PieceElement *pElement)
{
    Ov002PieceClass *pClass;
    void *pEntry;
    u16 nAngle;
    int nAnswer;

    pClass = pElement->pOwner;
    pEntry = func_ov002_0206da70(pClass->aName);
    func_0202b930(pElement->aNode, pEntry, 1, 4);

    nAngle = pElement->nAngle;
    if ((pElement->nNodeFlags & 0x20) == 0) {
        pElement->nHomeAngle = nAngle;
        pElement->wAnimFlags |= 0x20;
    }

    pElement->nReplays = (u8)func_ov002_0207c6c0(&pElement->wAnimFlags);

    nAnswer = func_020235d0(pElement->wRequestId, pElement->bRequestSlot);
    func_0202bedc(pElement->aNode, (nAnswer & 1) != 0);

    if (pClass->nRequestA >= 0) {
        func_0203355c(pClass->nRequestA);
    }
}
