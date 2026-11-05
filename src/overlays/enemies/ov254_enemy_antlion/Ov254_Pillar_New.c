/* Allocate a 0x394-byte object, link it back to this owner (+0x390),
 * install the 020d20bc callback (+0x18c), init via 020c6624 and return it. */
extern int CallocInstance(int a);
extern void Ov107_AiState_Init(int a, int b);
extern void Ov254_PillarSetup(int);
int Ov254_Pillar_New(int param_1) {
    int obj = CallocInstance(0x394);
    *(int *)(obj + 0x390) = param_1;
    *(int *)(obj + 0x18c) = (int)&Ov254_PillarSetup;
    Ov107_AiState_Init(obj, 0);
    return obj;
}
