/* Dispatch a draw/transform call for one of param_1's sub-objects: pick the source
 * pointer by param_2 (case 3 -> +0x10, case 4 -> +0x14, else -> +0xc), then hand the
 * glyph/handle (+0x94 struct, field +0xc) plus that object's 0x18-stride transform
 * block (offsets 0x18..0x2c) to func_02013484. */
#pragma thumb on
extern void func_02013484(int a, unsigned short *b, int c, int d, int e, int f,
                          unsigned int g, unsigned int h, unsigned int i, unsigned int j);
void func_020233b0(int param_1, int param_2) {
    unsigned short *puVar1 = *(unsigned short **)(param_1 + 0x94);
    unsigned short *puVar3;
    int iVar2;
    switch (param_2) {
    case 3:  puVar3 = *(unsigned short **)(param_1 + 0x10); break;
    case 4:  puVar3 = *(unsigned short **)(param_1 + 0x14); break;
    default: puVar3 = *(unsigned short **)(param_1 + 0xc); break;
    }
    iVar2 = param_1 + param_2 * 0x18;
    func_02013484((int)(puVar1 + 6), puVar3,
                  *(int *)(iVar2 + 0x18), *(int *)(iVar2 + 0x1c),
                  *(int *)(iVar2 + 0x20), *(int *)(iVar2 + 0x24),
                  (unsigned int)*puVar1, (unsigned int)puVar1[1],
                  *(unsigned int *)(iVar2 + 0x28), *(unsigned int *)(iVar2 + 0x2c));
}
