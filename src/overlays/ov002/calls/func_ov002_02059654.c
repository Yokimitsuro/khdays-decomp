/* Close the confirmation prompt: clear the pending flag at +0x178 that
 * func_ov002_0205953c latched, re-arm the tag-tracker node for tag 0x1a, and
 * click unless the shutdown hook has already taken over. Raises the +0x28 bit
 * either way, even when the prompt was never open.
 */
extern int func_ov002_020536bc(int tag);
extern void func_ov002_020536dc(int node, int armed);
extern void func_ov002_02058898(void);
extern int func_ov002_0206b7a4(void);
extern void func_02033b24(int nBank, int nSound);

extern char *data_ov002_0207f618;

void func_ov002_02059654(int bClick) {
    char *ctx = data_ov002_0207f618;

    *(int *)(ctx + 0x178) = 0;
    func_ov002_02058898();

    if (*(int *)(ctx + 0x2c) != 0) {
        func_ov002_020536dc(func_ov002_020536bc(0x1a), 1);
        if (func_ov002_0206b7a4() == 0 && bClick != 0) {
            func_02033b24(0, 0x10);
        }
    }

    *(unsigned char *)(ctx + 0x28) = *(unsigned char *)(ctx + 0x28) | 8;
}
