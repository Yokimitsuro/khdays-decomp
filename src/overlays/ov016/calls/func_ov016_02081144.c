/* func_ov016_02081144 -- Ov016_ScriptOpCreateFollower: script op that reads a slot, a kind and
 * an index, a packed GameState field / bit word (pc + 0x1c), the player to trail, the range
 * (fx32), the hold time in seconds (fx32), the turn rate and -- when the operand at pc + 0x40
 * is present -- the cone in degrees (turned into a 16-bit angle by degrees * 0x10000 / 360;
 * 90 by default), then creates a follower piece (Ov016_FollowerCreate 02080810) on the slot's
 * class table (ov002 02076468).  Always consumes the op (1). */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

extern int   func_02021980(int vm, u16 *pc);            /* ScriptVm_ReadOperandInt */
extern int   func_02021994(int vm, u16 *pc);            /* ScriptVm_ReadOperandFx32 */
extern long long func_02020400(int nNumerator, int nDenominator); /* _s32_div_f */
extern void *func_ov002_02076468(int nSlot);            /* class table of a slot */
extern void *func_ov016_02080810(void *pClass, u16 nSlot, u16 nBucket, u16 nField, u8 nBit,
                                 int nPlayer, int nRange, int nSeconds, int nTurnRate, int nCone); /* Ov016_FollowerCreate */

int func_ov016_02081144(int vm, u16 *pc)
{
    u16 nField;
    u8 nBit;
    int nSlot;
    u32 nKind;
    u32 nIndex;
    u32 nRaw;
    int nPlayer;
    int nRange;
    int nSeconds;
    int nTurnRate;
    u32 nCone;
    void *pClass;

    nSlot = func_02021980(vm, pc);
    nKind = func_02021980(vm, pc + 4);
    nIndex = func_02021980(vm, pc + 8);
    nRaw = *(u32 *)(pc + 0xe);
    nField = nRaw;
    nBit = (u16)(nRaw >> 16);
    nPlayer = func_02021980(vm, pc + 0x10);
    nRange = func_02021994(vm, pc + 0x14);
    nSeconds = func_02021994(vm, pc + 0x18);
    nTurnRate = func_02021980(vm, pc + 0x1c);
    nCone = 90;
    if (((short *)pc)[0x20] != 0) {
        nCone = (u16)func_02020400(func_02021980(vm, pc + 0x20) << 16, 360);
    }
    pClass = func_ov002_02076468(nSlot);
    func_ov016_02080810(pClass, nKind & 0xffff, nIndex & 0xffff, nField, nBit, nPlayer, nRange, nSeconds, nTurnRate, nCone);
    return 1;
}
