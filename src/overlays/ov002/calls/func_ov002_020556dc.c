/* Switch the help message, remembering which one is up.
 *
 * Asking for the mode that is already showing does nothing. Otherwise the current message is
 * dismissed with code 0x8f, and a non-negative mode looks its own code up in a halfword table and
 * shows that one; a negative mode means no help at all. Either way the mode is stored at 0x1bc of
 * the panel context, which Ghidra carries as nHelpMode.
 */

typedef unsigned short u16;

extern char *data_ov002_0207f614;
extern u16 data_ov002_0207db78[];
extern int func_ov002_02053558(int code);
extern void func_ov002_020535f0(int handle);
extern void func_ov002_020535a4(int handle);

void func_ov002_020556dc(int mode) {
    char *ctx = data_ov002_0207f614;

    if (*(int *)(ctx + 0x1bc) == mode) {
        return;
    }
    func_ov002_020535f0(func_ov002_02053558(0x8f));
    if (mode >= 0) {
        func_ov002_020535a4(func_ov002_02053558(data_ov002_0207db78[mode]));
    }
    *(int *)(ctx + 0x1bc) = mode;
}
