/* Samples the pad once per frame: keeps the previous state, reads the buttons (REG_KEYINPUT plus
 * the ARM7-shared X/Y/debug bits, active-low, masked to 0x2fff) unless the lid is closed, derives
 * the newly pressed set and stamps the change time (vblank count) of every button that changed.
 * Always returns 1. */
typedef unsigned short u16;

typedef struct {
    u16 cont;       /* 0x00 */
    u16 prev;       /* 0x02 */
    u16 trig;       /* 0x04 */
} PadState;

extern PadState data_0204c18c;
extern unsigned int data_0204c194[];
extern unsigned int OS_IsThreadAvailable(void);   /* GetVBlankCount */

int func_02023f78(void)
{
    u16 bit = 1;
    u16 prev;
    u16 cont;
    unsigned int now;
    int i;

    data_0204c18c.prev = data_0204c18c.cont;
    if ((*(volatile u16 *)0x027fffa8 & 0x8000) >> 15) {
        cont = 0;
    } else {
        cont = ((*(volatile u16 *)0x04000130 | *(volatile u16 *)0x027fffa8) ^ 0x2fff) & 0x2fff;
    }
    data_0204c18c.cont = cont;
    prev = data_0204c18c.prev;
    cont = (u16)data_0204c18c.cont;     /* the cast gives the reloaded state its own value, allocated after prev */
    data_0204c18c.trig = ~prev & cont;
    now = OS_IsThreadAvailable();
    for (i = 0; i < 12; i++) {
        if ((u16)(prev ^ cont) & bit) {
            data_0204c194[i] = now;
        }
        bit = bit << 1;
    }
    return 1;
}
