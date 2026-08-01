/*
 * Game_ApplyModeFlags - push the four low mode bits of the global config byte data_0204c240 into
 * the option registry (func_020235e8), one entry per bit. Called from the ov002 gameplay-scene
 * constructor during setup.
 *
 * For each of bits 0..3 it submits func_020235e8(id, 1, bitSet ? 1 : 0) with ids
 * 0x200e / 0x200f / 0x2000 / 0x200d respectively. The flag argument is a u16, so the 0/1 value is
 * zero-extended to 16 bits before the call (the lsl#16/lsr#16 pair). 0x2000 is materialised inline
 * (2 << 12); the other three ids come from the literal pool.
 */

typedef unsigned char  u8;
typedef unsigned short u16;

extern u8   data_0204c240;
extern void func_020235e8(int id, int kind, u16 value);

void func_020350c8(void)
{
    func_020235e8(0x200e, 1, (data_0204c240 & 1) ? 1 : 0);
    func_020235e8(0x200f, 1, (data_0204c240 & 2) ? 1 : 0);
    func_020235e8(0x2000, 1, (data_0204c240 & 4) ? 1 : 0);
    func_020235e8(0x200d, 1, (data_0204c240 & 8) ? 1 : 0);
}
