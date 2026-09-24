/* Sub-scene state after 020829b4: stays put while bit 0 of the root flags is set; otherwise, when
 * 0208cc58 reports a pending request, 02082b10(0) handles it, and once bit 2 is set the game-state
 * field 0x2080 (5 bits) becomes 0x1b and the scene moves on to 02082a3c. */
extern unsigned int *NNSi_FndGetCurrentRootHeap(void);
extern int func_ov026_0208cc58(void);
extern void func_ov026_02082b10(int a);
extern void func_020235e8(int field, int width, int value);
extern void func_ov026_02082a3c(void);

int func_ov026_020829e0(void)
{
    unsigned int *h = NNSi_FndGetCurrentRootHeap();

    if ((*h & 1) != 0) {
        return 0;
    }
    if (func_ov026_0208cc58() != 0) {
        func_ov026_02082b10(0);
    }
    if ((*h & 4) == 0) {
        return 0;
    }
    func_020235e8(0x2080, 5, 0x1b);
    return (int)func_ov026_02082a3c;
}
