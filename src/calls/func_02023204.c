/*
 * SubObject_SetupDrawsForMode - flag-conditional variant of SubObject_SetupDraws. Clears the active
 * scene render context's sub-object buffer (context = data_0204be08[1]; its object at +0xa0, buffer
 * at +0xc sized by +8) and populates the sub-object draw entries (context+0xc table) via
 * SubObject_ConfigDraw (func_02023340), choosing the layer set from GameState_IsFlagSet(0x2483):
 * when the flag is set only the base layer (slot 3) is drawn; when clear, slots 0 and 1 (and, when
 * the global u16 bit 2 is set, an extra 1/2 pair) are added.
 *
 * THUMB. Matching note: the flag result must be declared BEFORE the context locals so mwcc keeps it
 * in r4 and the context pointer in r5 (declaring it after swaps them and renumbers every use).
 */

extern int  func_02023588(int flag);              /* GameState_IsFlagSet */
extern unsigned short func_02020a9c(void);         /* LoadGlobalU16At0 */
extern void MIi_CpuClearFast(int val, void *dst, unsigned int n);
extern void func_02023340(int table, int index, int a, int b, int c, int d, int e, int f);  /* SubObject_ConfigDraw */
extern int  data_0204be08[];

void func_02023204(void)
{
    int iVar2;
    int iVar4;
    int iVar5;
    unsigned int uVar3;
    unsigned short uVar1;

    iVar4 = data_0204be08[1];
    iVar5 = *(int *)(iVar4 + 0xa0);
    iVar2 = func_02023588(0x2483);
    MIi_CpuClearFast(0, (void *)(iVar5 + 0xc), *(unsigned int *)(iVar5 + 8));
    if (iVar2 != 0) {
        uVar3 = 0xb;
    } else {
        uVar3 = 8;
    }
    func_02023340(iVar4 + 0xc, 3, 0, 0, 10, uVar3, 0xc, 2);
    if (iVar2 == 0) {
        func_02023340(iVar4 + 0xc, 0, 0, 0, 10, 0xb, 0xb, 2);
        uVar1 = func_02020a9c();
        if ((uVar1 & 2) == 0) {
            func_02023340(iVar4 + 0xc, 1, 0xb, 0, 10, 0xd, 0xb, 2);
            return;
        }
        func_02023340(iVar4 + 0xc, 1, 0x16, 0, 10, 0xd, 0xb, 2);
        func_02023340(iVar4 + 0xc, 2, 0, 3, 10, 0xd, 0xb, 2);
    }
}
