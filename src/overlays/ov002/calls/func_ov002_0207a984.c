extern int func_ov002_020573cc(void);
extern int func_ov002_0206b828(void);
extern int func_ov002_0206b7a4(void);
extern int func_ov002_0206b88c(int bOn);
extern int func_ov002_020766e0(void *pEntry, void *pReq, int nKind);
extern void func_ov022_020888ec(int nIndex, int bOn);
extern void func_ov002_020767bc(int arg0, int arg1);
extern int func_ov002_0206b78c(void);
extern int func_ov022_02083f0c(void);
extern int func_ov022_02083f5c(void);
extern void func_ov022_02086818(int nHandle, int nMode);
extern void func_ov002_0204cee0(int nHandle, int nMode);

/* Try to start a spare entry from a message.
 *
 * Nothing happens if the entry is already past its first phase or if any of the
 * three global guards refuses. The request is built on the stack from the index
 * the message carries and handed to the queue; if the queue takes it the entry
 * moves to phase one and the index is published, and the extra step below only
 * runs in the one mode that asks for it. The result is always zero.
 */
int func_ov002_0207a984(char *pEntry, unsigned char *pMsg)
{
    unsigned char aReq[8];
    int nHandle;

    if (*(unsigned char *)(pEntry + 0x2c) != 0) {
        return 0;
    }

    if (func_ov002_020573cc() != 0 || func_ov002_0206b828() != 0
        || func_ov002_0206b7a4() != 0) {
        return 0;
    }

    if (func_ov002_0206b88c(1) != 0) {
        aReq[0] = 1;
        aReq[4] = pMsg[0];

        if (func_ov002_020766e0(pEntry, aReq, 6) != 0) {
            *(unsigned char *)(pEntry + 0x2c) = 1;
            func_ov022_020888ec(pMsg[0], 1);
            func_ov002_020767bc((int)pEntry, pMsg[0]);

            if (func_ov002_0206b78c() == 1) {
                nHandle = func_ov022_02083f0c();
                func_ov022_02086818(func_ov022_02083f5c(), 0);
                func_ov002_0204cee0(nHandle, 1);
            }
        } else {
            func_ov002_0206b88c(0);
        }
    }

    return 0;
}
