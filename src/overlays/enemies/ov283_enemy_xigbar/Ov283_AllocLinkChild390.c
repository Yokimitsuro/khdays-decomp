/* Allocate a 0x390-byte object, link it back to this owner (+0x388),
 * install the 020cedd0 callback (+0x18c), init via 020c6624 and return it. */
extern int CallocInstance(int a);
extern void Ov107_AiState_Init(int a, int b);
extern void Ov283_BuildHelper(int);
int Ov283_AllocLinkChild390(int param_1) {
    int obj = CallocInstance(0x390);
    *(int *)(obj + 0x388) = param_1;
    *(int *)(obj + 0x18c) = (int)&Ov283_BuildHelper;
    Ov107_AiState_Init(obj, 0);
    return obj;
}
