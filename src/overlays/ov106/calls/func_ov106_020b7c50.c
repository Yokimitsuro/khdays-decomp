/* Choose the ov106 screen layers: while field 0x248c is clear, layer 0 shows unless +0x8e48 is set and
 * layer 1 hides (plus layer 1 of the second group); otherwise the layer selected by +0x8e48 shows and
 * the other hides. */
extern char *data_ov106_020b8b60;
extern int func_02023588(int flag);
extern void func_ov002_02074024(int index, int flag);
extern void func_ov002_02073ffc(int nA, int nB);

void func_ov106_020b7c50(void)
{
    if (func_02023588(0x248c) == 0) {
        func_ov002_02074024(0, *(int *)(data_ov106_020b8b60 + 0x8e48) == 0);
        func_ov002_02074024(1, 0);
        func_ov002_02073ffc(1, 0);
    } else {
        func_ov002_02074024(*(int *)(data_ov106_020b8b60 + 0x8e48) != 0, 1);
        func_ov002_02074024(*(int *)(data_ov106_020b8b60 + 0x8e48) == 0, 0);
    }
}
