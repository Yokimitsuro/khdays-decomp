typedef unsigned char u8;
typedef unsigned short u16;
typedef struct VecFx32 { int x, y, z; } VecFx32;
typedef struct Ov002SessionMarker {
    VecFx32 place;
    int nOwner;
    int nKind;
    char szName[0x30];
} Ov002SessionMarker;
typedef struct Ov002SessionBlock {
    int nSessionToken;
    Ov002SessionMarker *pMarkers;
} Ov002SessionBlock;
typedef struct Ov002MissionMemberHead {
    u16 wHead0, wHead2, wHead4, wHead6;
} Ov002MissionMemberHead;
typedef struct Ov002MissionMember {
    Ov002MissionMemberHead head;
    char pad008[0xfc];
} Ov002MissionMember;

extern char *data_ov002_0207fa00;
extern u8 data_0204c240, data_02042a1d, data_02042a1c;
extern Ov002MissionMember data_0204c678[];
extern void func_ov002_02072b58(void);
extern void func_ov002_02069878(const VecFx32 *pPlace, int nAngle, int nIndex, VecFx32 *pOut);
extern int func_ov002_0206e6e8(void);
extern void func_02035444(int nMemberIndex, int nFlags, int nMemberKind, int nLevel);
extern void func_02035638(int nMemberIndex, int nBehaviorId);

/* Append a member using marker zero as its initial placement, then restore
 * the four halfwords of that member's header in place.
 *
 * The three header cursors intentionally spell the same 32-bit address three
 * ways. A byte-pointer sum, integer sum, and integer roundtrip before the
 * byte-pointer sum make MWCC retain distinct address-expression nodes until
 * register allocation. They coalesce without extra instructions, matching
 * the ROM's base=r2, offset=r3 and cursor=r1. A single cursor swaps r1/r3.
 * The identity masks preserve the ROM's load/store pairs.
 * THUMB: 176 bytes, 10 relocs.
 */
void func_ov002_0206da94(int nMemberKind, int nBehaviorId, int nLevelBias)
{
    Ov002SessionBlock *pSession = (Ov002SessionBlock *)(data_ov002_0207fa00 + 0x8bcc);
    int nIndex = data_02042a1d;
    Ov002MissionMemberHead *pHead;
    if (!(data_0204c240 & 4)) {
        data_02042a1d++;
        data_02042a1c++;
        func_ov002_02072b58();
        pSession->pMarkers[nIndex].place = pSession->pMarkers[0].place;
        pSession->pMarkers[nIndex].nOwner = pSession->pMarkers[0].nOwner;
        pSession->pMarkers[nIndex].nKind = pSession->pMarkers[0].nKind;
        func_ov002_02069878(&pSession->pMarkers[0].place, pSession->pMarkers[0].nOwner,
            nIndex, &pSession->pMarkers[nIndex].place);
        func_02035444(nIndex, 0, nMemberKind, nLevelBias + func_ov002_0206e6e8());
        func_02035638(nIndex, nBehaviorId);
        Ov002MissionMemberHead *pHeadWords2And6, *pHeadWord4;
        pHead = (Ov002MissionMemberHead *)((char *)data_0204c678 + nIndex * 0x104);
        pHeadWords2And6 = (Ov002MissionMemberHead *)((unsigned int)data_0204c678 + nIndex * 0x104);
        pHeadWord4 = (Ov002MissionMemberHead *)((char *)((unsigned int)data_0204c678) + nIndex * 0x104);
        pHead->wHead0 &= 0xffff;
        pHeadWords2And6->wHead2 &= 0xffff;
        pHeadWord4->wHead4 &= 0xffff;
        pHeadWords2And6->wHead6 &= 0xffff;
    }
}
