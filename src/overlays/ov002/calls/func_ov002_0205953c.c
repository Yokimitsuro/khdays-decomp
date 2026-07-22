/* Open the confirmation prompt: latch the pending flag and its two payload words
 * at +0x178..+0x184, seed both scroll halves at +0x180/+0x182 from the current
 * row height at +0x3a, disarm the tag-tracker node for tag 0x1a and raise scene
 * event 0x4f. The row height is read TWICE rather than cached. */
extern int func_ov002_020536bc(int tag);
extern void func_ov002_020536dc(int node, int armed);
extern void func_ov002_02053558(int event);
extern void func_ov002_020535a4(void);

extern char *data_ov002_0207f618;

void func_ov002_0205953c(int a, int b) {
    char *ctx = data_ov002_0207f618;

    *(int *)(ctx + 0x178) = 1;
    *(int *)(ctx + 0x17c) = b;
    *(int *)(ctx + 0x184) = a;
    *(short *)(ctx + 0x180) = *(unsigned short *)(ctx + 0x3a);
    *(short *)(ctx + 0x182) = *(unsigned short *)(ctx + 0x3a);

    func_ov002_020536dc(func_ov002_020536bc(0x1a), 0);
    func_ov002_02053558(0x4f);
    func_ov002_020535a4();
}
