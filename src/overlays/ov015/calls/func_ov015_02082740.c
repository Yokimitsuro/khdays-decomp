/* func_ov015_02082740 -- Ov015_ScriptOpSpawnPoint: script op that reads a slot, a kind, an
 * index, a packed field / bit pair (raw word at pc + 0x1c: low half the GameState field,
 * next byte its bit) and a facing (fx32), then spawns a point piece (02080fc0) on the
 * slot's class table (ov002 02076468).  Always consumes the op (1). */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

extern int  func_02021980(int vm, u16 *pc);            /* ScriptVm_ReadOperandInt */
extern int  func_02021994(int vm, u16 *pc);            /* ScriptVm_ReadOperandFx32 */
extern int  func_ov002_02076468(int nSlot);            /* class table of a slot */
extern int  func_ov015_02080fc0(int pTable, int nKind, int nIndex, int nField, u8 nBit, int nFacing);

int func_ov015_02082740(int vm, u16 *pc)
{
    int nSlot = func_02021980(vm, pc);
    u32 nKind = func_02021980(vm, pc + 4);
    u32 nIndex = func_02021980(vm, pc + 8);
    u32 nFieldBit = *(u32 *)(pc + 0xe);
    u16 nBitHalf = nFieldBit >> 16;
    int nFacing = func_02021994(vm, pc + 0x10);

    func_ov015_02080fc0(func_ov002_02076468(nSlot), nKind & 0xffff, nIndex & 0xffff, nFieldBit & 0xffff, nBitHalf, nFacing);
    return 1;
}
