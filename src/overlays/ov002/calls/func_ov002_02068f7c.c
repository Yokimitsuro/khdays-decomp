extern char *NNSi_FndGetCurrentRootHeap(void);
extern void func_0202b73c(void);
extern void func_ov002_02076924(void);
extern void func_ov002_0206da28(void);
extern void func_ov002_0206e718(int mode);
extern void func_ov002_0206b910(int a, void *b);
extern void func_ov002_02069c04(void);
extern void func_ov002_02068fc4(void);
extern void func_ov002_02067f78(void);
extern int data_ov002_0207efc0;

/* Finishes the save step and picks the next screen: the error page when the slot index went
 * negative, otherwise the normal follow-up. */
void *func_ov002_02068f7c(void) {
    char *heap = NNSi_FndGetCurrentRootHeap();
    func_0202b73c();
    func_ov002_02076924();
    func_ov002_0206da28();
    if (*(short *)(heap + 0x8baa) < 0) {
        func_ov002_0206e718(0);
        return (void *)&func_ov002_02068fc4;
    }
    func_ov002_0206b910(0, &data_ov002_0207efc0);
    func_ov002_02069c04();
    return (void *)&func_ov002_02067f78;
}
