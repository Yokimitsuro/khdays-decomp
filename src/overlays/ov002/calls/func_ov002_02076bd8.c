/*
 * func_ov002_02076bd8 - set bit 0 of a game-state field to a boolean (ARM).
 *
 * Reads the game-state field addressed by the actor's (fieldHi, fieldLo) id pair via func_020235d0,
 * clears its low bit, sets that bit to (on != 0), and writes it back via func_020235e8. The id pair
 * is re-read for the store because the get call may touch the same state. The value is kept as a u16
 * (mask 0xfffe), which is why each step re-truncates to 16 bits.
 */
typedef struct {
    char _0[0x14];
    unsigned short fieldHi;   /* +0x14 */
    unsigned char  fieldLo;   /* +0x16 */
} Ov002Actor;

extern int func_020235d0(int hi, int lo);
extern void func_020235e8(int hi, int lo, int value);

void func_ov002_02076bd8(Ov002Actor *actor, int on)
{
    unsigned short v = func_020235d0(actor->fieldHi, actor->fieldLo) & 0xfffe;
    if (on != 0) v |= 1;
    func_020235e8(actor->fieldHi, actor->fieldLo, v);
}
