typedef unsigned short u16;

extern int func_02020a9c(void);                 /* LoadGlobalU16At0 */
extern void func_02033c24(int nArg0, int nArg1);  /* the sound call */
extern int func_02023588(int nFlag);            /* GameState_IsFlagSet */
extern void func_02020a90(u16 nMask);           /* StoreGlobalShortAt0 */

/* Turns a kind into the button mask the prompt should accept, picks the sound
 * that goes with it, and arms the mask.
 *
 * Most kinds map to a fixed mask; kind zero accepts everything, and kind four
 * and anything past thirteen accept nothing.  Bit 1 of the new mask decides
 * which pair of sounds is used: with it set the choice comes from bit 2 of the
 * mask that is still armed, and without it from a game flag.  The two globals
 * are the read and write ends of one halfword, so that read is a look at the
 * previous mask rather than at any input state.
 *
 * The arms are written in the order the ROM lays their blocks down after the
 * jump table, which is why kind ten comes last.
 */
void func_ov002_0206a5d4(int nKind)
{
    int nMask;

    nMask = 0;
    switch (nKind) {
    case 0:
        nMask = -1;
        break;
    case 1:
        nMask = 2;
        break;
    case 2:
        nMask = 4;
        break;
    case 3:
        nMask = 0xa;
        break;
    case 5:
        nMask = 0x2a;
        break;
    case 6:
        nMask = 0xc;
        break;
    case 7:
        nMask = 0x42;
        break;
    case 8:
    case 9:
    case 11:
    case 12:
    case 13:
        nMask = 0x80;
        break;
    case 10:
        nMask = 0x100;
        break;
    }

    if ((nMask & 2) != 0) {
        if ((func_02020a9c() & 4) != 0) {
            func_02033c24(0x7f, 0x19);
        } else {
            func_02033c24(0x7f, 0xa);
        }
    } else if (func_02023588(0x20bf) != 0) {
        func_02033c24(0x60, 0xa);
    } else {
        func_02033c24(0x40, 0xa);
    }
    func_02020a90((u16)nMask);
}
