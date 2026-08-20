typedef void (*Ov002NodeStep)(int pNode);

extern void func_ov002_02076af0(int pNode);
extern void func_ov002_02076b48(int pNode);
extern void func_ov002_020764a4(int pNode);
extern void func_ov002_02076a74(int pNode);

/* Run one update pass over the node, skipping it entirely while it is
 * inactive. The two optional stages are gated on their own flag bits, then
 * the fixed stage runs, the class step is invoked if present, and the node
 * is committed. */
void func_ov002_02076a90(int pNode)
{
    Ov002NodeStep pfnStep;

    if ((*(unsigned short *)(pNode + 0x12) & 1) == 0) {
        return;
    }

    if ((*(unsigned short *)(pNode + 0x12) & 4) != 0) {
        func_ov002_02076af0(pNode);
    }

    if ((*(unsigned short *)(pNode + 0x12) & 2) != 0) {
        func_ov002_02076b48(pNode);
    }

    func_ov002_020764a4(pNode);

    pfnStep = *(Ov002NodeStep *)(*(int *)(pNode + 8) + 4);
    if (pfnStep != 0) {
        pfnStep(pNode);
    }

    func_ov002_02076a74(pNode);
}
