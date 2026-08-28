typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    char pad00[4];
    char *pContext;                 /* +0x04 */
} Ov002SceneRef;

extern Ov002SceneRef data_ov002_0207fa20;
extern u8 data_0204be04;

extern int func_02030788(void);                       /* local player index */
extern int func_02031384(int nKind, void *pPacket, int nSize);
extern int func_ov002_0207285c(int nList);
extern int func_020235d0(int wId, int bSlot);
extern void func_ov002_02078288(void);

/* Step the session menu's scene once.
 *
 * Nothing runs while the scene is shutting down, or while the global at
 * data_0204be04 is raised.  The host alone drains the pending mask at +0x1fc,
 * announcing one bit at a time and clearing each bit the announcement accepts;
 * a mask of all ones is announced once as the wildcard.  An announcement the
 * far side rejects with 0xffff stops the drain for this step.
 *
 * Then every one of the twenty-four node lists the context heads is walked, and
 * each node whose request the query admits is given its turn: its own handler
 * while the scene runs, or its object's shutdown entry once the scene is going
 * down.  A handler that returns a successor replaces itself with it.
 */
void *func_ov002_020761d8(void)
{
    char *pCtx;
    char *pNode;
    char *pNext;
    void *(*pfnStep)(char *pNode);
    void (*pfnStop)(char *pNode, int nKind);
    void *pResult;
    char *pState;
    unsigned int nMask;
    int bTake;
    int nBit;
    int nList;
    u8 aPacket[8];

    pCtx = data_ov002_0207fa20.pContext;
    if ((*(u8 *)(pCtx + 0x68) & 1) != 0) {
        return 0;
    }
    if (data_0204be04 != 0) {
        return 0;
    }

    if (func_02030788() == 0) {
        pState = data_ov002_0207fa20.pContext;
        if (*(unsigned int *)(pState + 0x1fc) != 0) {
            aPacket[0] = 1;
            aPacket[1] = 0xff;
            *(u16 *)(aPacket + 2) = 0xffff;

            if (*(unsigned int *)(pState + 0x1fc) == 0xffffffff) {
                *(u16 *)(aPacket + 4) = 0xffff;
                if (func_02031384(5, aPacket, 6) != 0xffff) {
                    *(unsigned int *)(data_ov002_0207fa20.pContext + 0x1fc) = 0;
                }
            } else {
                nMask = *(unsigned int *)(pState + 0x1fc);
                for (nBit = 0; nBit < 0x20; nBit++) {
                    if ((nMask & (1u << nBit)) != 0) {
                        *(u16 *)(aPacket + 4) = (u16)nBit;
                        if (func_02031384(5, aPacket, 6) == 0xffff) {
                            break;
                        }
                        *(unsigned int *)(data_ov002_0207fa20.pContext + 0x1fc) &=
                            ~(1u << nBit);
                    }
                    nMask = *(unsigned int *)(data_ov002_0207fa20.pContext + 0x1fc);
                    if (nMask == 0) {
                        break;
                    }
                }
            }
        }
    }

    for (nList = 0; nList < 0x18; nList++) {
        pNode = ((char **)pCtx)[nList];
        if (func_ov002_0207285c(nList) < 0) {
            continue;
        }
        if (pNode == 0) {
            continue;
        }
        while (pNode != 0) {
            pNext = *(char **)(pNode + 4);
            bTake = (func_020235d0(*(u16 *)(pNode + 0x14),
                                   *(u8 *)(pNode + 0x16)) & 1) != 0;
            if (bTake) {
                if ((*(u8 *)(data_ov002_0207fa20.pContext + 0x68) & 1) == 0) {
                    pfnStep = *(void *(**)(char *))(pNode + 0xc);
                    pResult = pfnStep(pNode);
                    if (pResult != 0) {
                        *(void **)(pNode + 0xc) = pResult;
                    }
                } else {
                    pfnStop = *(void (**)(char *, int))(*(char **)(pNode + 8) + 0x3c);
                    if (pfnStop != 0) {
                        pfnStop(pNode, 2);
                    }
                }
            }
            pNode = pNext;
        }
    }

    func_ov002_02078288();
    return 0;
}
