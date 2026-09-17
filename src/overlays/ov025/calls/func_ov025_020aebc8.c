/* func_ov025_020aebc8 -- Ov025_ScrollList_Leave: clear game fields 0x35c5 (8 bits), 0x35d5
 * (10 bits), 0x35cd and 0x35df (8 bits each; GameState_SetField 020235e8) and leave the page:
 * when the context object (02084dd8) is 1 the menu is left entirely (ov002 0206d970 with
 * payload 0) and the target slot becomes -1 / -1 (02084798), otherwise 0 / -1; the cancel sound
 * plays (02033b78 0 / 3). */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef short          s16;

extern void  func_020235e8(int nField, int nBits, int nValue);      /* GameState_SetField */
extern int   func_ov025_02084dd8(void);                             /* Ov008_GetCtxObject95c0 */
extern void  func_ov002_0206d970(int nPayload);
extern void  func_ov025_02084798(int nEntry, int nTarget);          /* Ov008_SetTargetSlot */
extern void  func_02033b78(int nKind, int nSound);                  /* PlaySound */

void func_ov025_020aebc8(void)
{
    func_020235e8(0x35c5, 8, 0);
    func_020235e8(0x35d5, 10, 0);
    func_020235e8(0x35cd, 8, 0);
    func_020235e8(0x35df, 8, 0);
    if (func_ov025_02084dd8() == 1) {
        func_ov002_0206d970(0);
        func_ov025_02084798(-1, -1);
    } else {
        func_ov025_02084798(0, -1);
    }
    func_02033b78(0, 3);
}
