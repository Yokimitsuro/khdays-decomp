typedef unsigned char u8;
typedef unsigned short u16;

extern char data_0204c300[];
extern int data_0204be18;     /* an address kept as an integer */

extern char *NNSi_FndGetCurrentRootHeap(void);               /* the overlay root */
extern void func_ov002_02069724(void *pReport);  /* Ov002_BuildWrapUpReport */
extern void func_02020a78(int nKind, int nArg); /* request a scene */
extern int func_02030694(void);                 /* is the session ready */
extern int func_01fff974(void);                 /* the local peer mask */
extern void MIi_CpuClear16(int nValue, void *pDst, int nSize);
extern int func_ov002_0206fb84(int nKind, void *pCmd);  /* send, kind 8 */

/* Builds the seat tally and sends it, once every seat has reported.
 *
 * A roster already flagged done -- bit 4 of the seat mask -- asks for the
 * wrap-up report instead, pushes the scene request, and answers -2 so the
 * caller stops stepping.  Otherwise nothing happens unless the session is
 * ready, the last command's answer at root +0x8da2 is still 0xffff, and every
 * seat the local peer waits on has its bit up in the mask.
 *
 * The command is 0x22 bytes, cleared first.  Each of the four seats
 * contributes its own figure and, for all but the first, the three words after
 * it.  Then each of the three columns has three rows from the shared tally
 * source added into it, 8 bytes apart from +0x1974, and each summed column
 * goes back into the roster before the command is sent as kind 8.
 *
 * The tally source is held as an integer address, and the ROM adds the column
 * offset to it in that order; writing it as pointer arithmetic the other way
 * round costs two instructions.
 */
int func_ov002_02068918(void)
{
    int nOff;
    int i;
    char *pRoot;
    char *pCol;
    int nSrc;
    int j;
    u16 aCmd[0x11];
    char *pRec;
    char *pRoster;
    int k;
    char *pOut;
    char *p;
    int t;
    char *q;
    int nMask;
    int m;

    pRoot = NNSi_FndGetCurrentRootHeap();
    pRoster = pRoot + 0x8bcc;

    if ((*(u8 *)(pRoster + 0xb8) & 0x10) != 0) {
        func_ov002_02069724(data_0204c300);
        func_02020a78(3, 0);
        return -2;
    }

    if (func_02030694() != 0 && *(u16 *)(pRoot + 0x8da2) == 0xffff) {
        nMask = (int)(((unsigned int)(func_01fff974() & 0xfffe) << 28) >> 24);
        if (nMask != (*(u8 *)(pRoster + 0xb8) & nMask)) {
            return 0;
        }

        MIi_CpuClear16(0, aCmd, 0x22);

        pRec = pRoster;
        pOut = (char *)aCmd;
        for (i = 0; i < 4; i++) {
            *(u16 *)(pOut + 2) = (u16)*(int *)(pRec + 0x24);
            if (i != 0) {
                j = 0;
                p = pRec;
                q = pOut;
                do {
                    *(u16 *)(q + 4) = (u16)*(int *)(p + 0x28);
                    j++;
                    p += 4;
                    q += 2;
                } while (j < 3);
            }
            pRec += 0x2c;
            pOut += 8;
        }

        for (k = 0, nOff = 0, pCol = (char *)aCmd; k < 3; k++) {
            m = 0;
            t = 0;
            nSrc = nOff + data_0204be18;
            do {
                *(u16 *)(pCol + 4) = (u16)(*(u16 *)(pCol + 4)
                                        + *(u16 *)(t + nSrc + 0x1974));
                m++;
                t += 8;
            } while (m < 3);
            *(int *)(pRoster + 0x28) = *(u16 *)(pCol + 4);
            pRoster += 4;
            nOff += 2;
            pCol += 2;
        }

        *(u16 *)(pRoot + 0x8da2) = (u16)func_ov002_0206fb84(8, aCmd);
    }
    return 0;
}
