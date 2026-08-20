extern void func_0202ba18(int pSub);
extern void func_0201ef58(void);
extern void func_020339b0(int nA, int nB);
extern void func_020235bc(int nId);

/* Tear down the scene's transient state: stop the sub-object when its owner
 * still has one, then release the two resources flagged in the state byte. */
void func_ov002_0207b1c0(int pScene)
{
    if (*(signed char *)(*(int *)(pScene + 8) + 0x58) != 0) {
        func_0202ba18(pScene + 0x2c);
    }

    if ((*(unsigned char *)(pScene + 0x1b5) & 4) != 0) {
        func_0201ef58();
        func_020339b0(-1, 0x2be);
        *(unsigned char *)(pScene + 0x1b5) &= ~4;

        if ((*(unsigned char *)(pScene + 0x1b5) & 0x10) != 0) {
            *(unsigned char *)(pScene + 0x1b5) &= ~0x10;
            func_020235bc(0x20e0);
        }
    }
}
