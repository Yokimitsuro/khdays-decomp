extern int func_020235d0(unsigned short nId, unsigned char nSlot);
extern int func_ov002_020573cc(void);

typedef int (*Ov002NodeHandler)(int pNode, int pEvent);

/* Forward the event to the node's secondary handler, when the node is live,
 * the handler exists and the gate is clear. Returns the handler's result, or 0.
 * The handler is read twice because the gate call sits between the null test
 * and the dispatch. */
int func_ov002_02076e08(int pNode, int pEvent)
{
    int bLive;

    bLive = (func_020235d0(*(unsigned short *)(pNode + 0x14),
                           *(unsigned char *)(pNode + 0x16)) & 1) != 0;
    if (bLive) {
        if (*(Ov002NodeHandler *)(*(int *)(pNode + 8) + 0x20) != 0) {
            if (func_ov002_020573cc() == 0) {
                return (*(Ov002NodeHandler *)(*(int *)(pNode + 8) + 0x20))(pNode, pEvent);
            }
        }
    }

    return 0;
}
