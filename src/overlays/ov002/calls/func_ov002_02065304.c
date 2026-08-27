/*
 * Redraws the map panel for one frame.
 *
 * The blink phase is advanced first on its own tick budget, then the tile buffer
 * is cleared and rebuilt: the fixed markers, the goal marker when one is set, the
 * panel decorations, every visible entity's icon, and finally the party rows and
 * the local player's emblem. The finished buffer is handed to the graphics queue.
 *
 * Entities are walked backwards through the room's list and filtered on three
 * flags: the low byte at +0x60 must have bit 0 set and bit 7 clear, the halfword
 * at +0x1ac must not have bit 1 set, and bit 2 there hides an entity unless its
 * icon kind is six.
 *
 * Two things here are load-bearing rather than style.
 *
 * The local player's id is read twice and kept in two separate variables: a
 * halfword for the room lookup and an int for the party block. Folding them into
 * one variable transposes the two scratch registers the party block hands to the
 * id and to the team, and moves six bytes. The two reads are genuinely separate
 * fetches in the ROM, so one variable each is also the honest reading.
 *
 * The count, the id, the team and the loop index are declared ahead of everything
 * else, in that order. That is what puts them in r5, r6, r7 and r8 rather than
 * letting the blink block's register pair push them apart.
 *
 * ARM.
 */
typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Ov002MapScene {
    char pad000[0x1c];
    void *pTiles;
    u8 nMode;
    char pad021[0x17];
    unsigned long long llBlinkAt;
    int bBlinkOn;
} Ov002MapScene;

typedef struct Ov002MapEntry {
    char pad000[0xc];
} Ov002MapEntry;

typedef struct Ov002RoomEntity {
    char pad000[0x60];
    u16 nFlags;
    char pad062[0x117];
    u8 nIconKind;
    char pad17a[0x32];
    u16 nHideFlags;
} Ov002RoomEntity;

typedef struct Ov002RoomList {
    char pad000[0x80];
    char aList[4];
} Ov002RoomList;

typedef struct Ov002RoomRef {
    char pad000[4];
    Ov002RoomList *pRoom;
} Ov002RoomRef;

typedef struct Ov002RoomHolder {
    char pad000[0x4ec];
    Ov002RoomRef *pRef;
} Ov002RoomHolder;

extern Ov002MapScene *data_ov002_0207f638;
extern Ov002MapEntry data_ov002_0207f69c[];
extern Ov002MapEntry data_ov002_0207f63c[];

extern unsigned long long func_020031d4(void);
extern unsigned long long func_02020374(unsigned long long a,
                                            unsigned long long b);
extern void MIi_CpuClearFast(unsigned int data, void *dest, unsigned int size);
extern void func_ov002_02065270(void);
extern int func_ov002_0206c890(Ov002MapEntry *pTable);
extern int func_ov002_0206c900(int nAxis, int nIndex);
extern void func_ov002_02065204(Ov002MapEntry *pEntry, int bWide, int nVariant);
extern int func_ov002_0206378c(void);
extern int func_ov002_020637a0(void);
extern int func_ov002_020651dc(int nGoal);
extern int func_ov002_020729cc(Ov002MapEntry *pTable);
extern int func_ov002_02065248(Ov002MapEntry *pEntry);
extern u16 func_01fffe14(void);
extern Ov002RoomHolder *func_01fffde0(unsigned int nSelf);
extern void *func_01fffdac(void *pList);
extern void *func_01fffdc4(void *pList);
extern void func_ov002_02064cd8(int *aCell, const void *pPos);
extern void func_ov002_020650bc(int nKind, const int *aCell);
extern int func_ov022_020882f8(void);
extern int func_ov022_02088474(int nPlayer);
extern int func_ov022_020882e0(int nPlayer);
extern void func_ov002_020652c8(int nPlayer);
extern void func_ov002_02064fec(int nPlayer);
extern int GFXi_EnqueueCommand(int nCommand, int nTarget, void *pSrc,
                               int nSize);

void func_ov002_02065304(void)
{
    int nPlayers;
    int nSelf;
    int nMine;
    int i;
    Ov002MapScene *pScene;
    unsigned long long llNow;
    unsigned long long llDelta;
    int nCount;
    int bWide;
    int nVariant;
    Ov002RoomHolder *pHolder;
    Ov002RoomList *pRoom;
    Ov002RoomEntity *pEntity;
    void *pNode;
    int aCell[2];
    unsigned int nLow;
    u16 nHide;
    u16 nRoomSelf;

    pScene = data_ov002_0207f638;
    llNow = func_020031d4();
    llDelta = llNow - pScene->llBlinkAt;
    if (llDelta > 0x3fec4) {
        pScene->llBlinkAt = llNow - func_02020374(llDelta, 0x3fec4);
        pScene->bBlinkOn = pScene->bBlinkOn == 0;
    }

    func_ov002_02065270();
    MIi_CpuClearFast(0, pScene->pTiles, 0x12c0);

    if (pScene->nMode < 2) {
        nCount = func_ov002_0206c890(data_ov002_0207f69c);
        for (i = 0; i < nCount; i++) {
            bWide = func_ov002_0206c900(0, i);
            nVariant = func_ov002_0206c900(1, i);
            func_ov002_02065204(&data_ov002_0207f69c[i], bWide, nVariant);
        }

        if (func_ov002_0206378c() != 0) {
            func_ov002_020651dc(func_ov002_020637a0());
        }

        nCount = func_ov002_020729cc(data_ov002_0207f63c);
        for (i = 0; i < nCount; i++) {
            func_ov002_02065248(&data_ov002_0207f63c[i]);
        }

        nRoomSelf = func_01fffe14();
        pHolder = func_01fffde0(nRoomSelf);
        if (pHolder != 0 && pHolder->pRef != 0
            && pHolder->pRef->pRoom != 0) {
            pRoom = pHolder->pRef->pRoom;
            pNode = func_01fffdac(pRoom->aList);
            pEntity = pNode == 0 ? 0 : *(Ov002RoomEntity **)pNode;
            while (pEntity != 0) {
                nHide = pEntity->nHideFlags;
                nLow = (unsigned int)(pEntity->nFlags << 24) >> 24;
                if ((nLow & 1) && !(nLow & 0x80) && !(nHide & 2)
                    && (pEntity->nIconKind == 6 || !(nHide & 4))) {
                    func_ov002_02064cd8(aCell, (char *)pEntity + 0x74);
                    func_ov002_020650bc(pEntity->nIconKind, aCell);
                }
                pNode = func_01fffdc4(pRoom->aList);
                pEntity = pNode == 0 ? 0 : *(Ov002RoomEntity **)pNode;
            }
        }

        nPlayers = func_ov022_020882f8();
        nSelf = func_01fffe14();
        nMine = func_ov022_02088474(nSelf);
        for (i = 0; i < nPlayers; i++) {
            if (i != nSelf && func_ov022_02088474(i) == nMine && func_ov022_020882e0(i) > 0) {
                func_ov002_020652c8(i);
            }
        }
        func_ov002_020652c8(nSelf);
        func_ov002_02064fec(nSelf);
    }

    GFXi_EnqueueCommand(0x16, 0x2720, pScene->pTiles, 0x12c0);
}
