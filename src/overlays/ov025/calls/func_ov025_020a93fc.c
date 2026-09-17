/* func_ov025_020a93fc -- Ov025_MissionList_CursorNext: move the mission list's cursor slot (+0x54)
 * to the next accepted slot (Ov025_StepCursorToAcceptedSlot 020a5284) while the +0x68,
 * +0x4f8 and +0x30 words are all clear and a page transition is active (02084e38); when the
 * slot changed the rows are rebuilt (Ov025_BuildMissionListRows 020a8360).  The rebuild is
 * called with the new slot as a second argument the callee ignores: that is what keeps the
 * slot in r1 (`mov r1, r0`) so the byte store can follow the `mov r0, r4` of the call. */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct Ov008MissionList {
    u8   pad_00[0x30];
    int  nField30;            /* 0x30 */
    u8   pad_34[0x54 - 0x34];
    u8   nCursorSlot;         /* 0x54 */
    u8   pad_55[0x68 - 0x55];
    int  nField68;            /* 0x68 */
    u8   pad_6c[0x4f8 - 0x6c];
    int  nField4f8;           /* 0x4f8 */
} Ov008MissionList;

extern int   func_ov025_02084e38(void);                             /* Ov025_GetCtxObject9634: page transition */
extern u32   func_ov025_020a5284(Ov008MissionList *pList, int nStep); /* Ov025_StepCursorToAcceptedSlot */
extern void  func_ov025_020a8360(Ov008MissionList *pList, u32 nSlot); /* Ov025_BuildMissionListRows: the slot is passed but unused */

void func_ov025_020a93fc(Ov008MissionList *pList)
{
    u32 nSlot;

    if (pList->nField68 != 0 || pList->nField4f8 != 0 || pList->nField30 != 0) {
        return;
    }
    if (func_ov025_02084e38() == 0) {
        return;
    }
    nSlot = func_ov025_020a5284(pList, 1);
    if (nSlot != pList->nCursorSlot) {
        pList->nCursorSlot = nSlot;
        func_ov025_020a8360(pList, nSlot);
    }
}
