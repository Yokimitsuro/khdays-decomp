/* func_ov016_02080ffc -- Ov016_ScriptOpCreateLift: script op that reads a slot, a kind and an
 * index, two packed GameState field / bit words (pc + 0x1c: the lift's own state, pc + 0x24:
 * the trigger), the position (three fx32), an angle in degrees (turned into a 16-bit facing
 * by angle * 0x10000 / 360), the top and bottom heights, the speed and -- when the operand at
 * pc + 0x60 is present -- the wait in seconds (times 30 frames; 60 seconds by default),
 * then creates a lift piece (Ov016_LiftCreate 0207ff40) on the slot's class table (ov002
 * 02076468).  Always consumes the op (1). */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct VecFx32 { int x, y, z; } VecFx32;

extern int   func_02021980(int vm, u16 *pc);            /* ScriptVm_ReadOperandInt */
extern int   func_02021994(int vm, u16 *pc);            /* ScriptVm_ReadOperandFx32 */
extern long long func_02020400(int nNumerator, int nDenominator); /* _s32_div_f */
extern void *func_ov002_02076468(int nSlot);            /* class table of a slot */
extern void *func_ov016_0207ff40(void *pClass, u16 nSlot, u16 nBucket, VecFx32 *pPos, short nFacing,
                                 u16 nField, u8 nBit, u16 nTriggerField, u8 nTriggerBit,
                                 int nTop, int nBottom, int nSpeed, int nWait);   /* Ov016_LiftCreate */

int func_ov016_02080ffc(int vm, u16 *pc)
{
    VecFx32 position;
    u16 nField;
    u8 nBit;
    u16 nFacing;
    u16 nTriggerField;
    u8 nTriggerBit;
    int nSlot;
    u32 nKind;
    u32 nIndex;
    u32 nRaw;
    int nTop;
    int nBottom;
    int nSpeed;
    int nWait;
    void *pClass;

    nSlot = func_02021980(vm, pc);
    nKind = func_02021980(vm, pc + 4);
    nIndex = func_02021980(vm, pc + 8);
    nRaw = *(u32 *)(pc + 0xe);
    nField = nRaw;
    nBit = (u16)(nRaw >> 16);
    nRaw = *(u32 *)(pc + 0x12);
    nTriggerField = nRaw;
    nTriggerBit = (u16)(nRaw >> 16);
    position.x = func_02021994(vm, pc + 0x14);
    position.y = func_02021994(vm, pc + 0x18);
    position.z = func_02021994(vm, pc + 0x1c);
    nFacing = (u16)func_02020400(func_02021980(vm, pc + 0x20) << 16, 360);
    nTop = func_02021994(vm, pc + 0x24);
    nBottom = func_02021994(vm, pc + 0x28);
    nSpeed = func_02021994(vm, pc + 0x2c);
    nWait = 0x3c000;
    if (((short *)pc)[0x30] != 0) {
        nWait = func_02021994(vm, pc + 0x30) * 30;
    }
    pClass = func_ov002_02076468(nSlot);
    func_ov016_0207ff40(pClass, nKind & 0xffff, nIndex & 0xffff, &position, nFacing, nField, nBit,
                        nTriggerField, nTriggerBit, nTop, nBottom, nSpeed, nWait);
    return 1;
}
