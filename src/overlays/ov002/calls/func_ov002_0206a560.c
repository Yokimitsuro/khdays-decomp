extern char *data_ov002_0207fa00;   /* the ov002 root context */
extern int data_0204c270;           /* g_ov002PromptSelector */

extern int func_02023588(int nFlag);    /* GameState_IsFlagSet */

/* Sets the prompt selector for the phase the screen is entering.
 *
 * Only three phases set one; every other phase leaves the selector as the last
 * one left it.  Phase eleven asks two game flags in turn, so its value depends
 * on which of them is set.
 *
 * All five are written as negative literals; mwcc builds each with mvns from
 * the small positive it materialises first, which is why the listing shows
 * 0, 4, 3, 5 and 2.
 *
 * The arms are written 8, 13, 11 because that is the order the ROM lays their
 * blocks down.
 */
void func_ov002_0206a560(void)
{
    char *pRoot;

    pRoot = data_ov002_0207fa00;
    switch (*(int *)(pRoot + 0x8b58)) {
    case 8:
        data_0204c270 = -1;
        break;
    case 13:
        data_0204c270 = -5;
        break;
    case 11:
        if (func_02023588(0x18bd) != 0) {
            data_0204c270 = -4;
        } else if (func_02023588(0x18c9) != 0) {
            data_0204c270 = -6;
        } else {
            data_0204c270 = -3;
        }
        break;
    }
}
