extern int func_ov002_0206b758(void);
extern int func_01fffe14(void);
extern int func_ov022_02088474(int nIndex);
extern int func_ov002_02072754(int nHandle);
extern void func_02033d0c(int a, int b, void *pBlock, int d);

/* Act on a message delivered to an element.
 *
 * Message 1 just moves the element's phase on. Message 2 only does anything for
 * the local player, and only when the message names that player's own slot; it
 * then starts effect 0x5e on the element's block.
 */
void func_ov002_0207b0c8(char *pElement, unsigned char *pMsg)
{
    switch (pMsg[0]) {
    case 1:
        *(unsigned char *)(pElement + 0x1b6) = 2;
        break;

    case 2:
        if (func_ov002_0206b758() == 0) {
            return;
        }
        if (*(short *)(pMsg + 4)
            != func_ov002_02072754(func_ov022_02088474(func_01fffe14()))) {
            return;
        }
        func_02033d0c(0, 0x5e, pElement + 0xe0, 0);
        break;
    }
}
