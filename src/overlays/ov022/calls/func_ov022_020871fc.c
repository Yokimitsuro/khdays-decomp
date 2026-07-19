extern char *NNSi_FndGetCurrentRootHeap(void);
extern void func_ov022_020883f4(int slot);
extern void func_ov022_02087298(int slot);
extern void SNDi_ProcessEntry(int id);
extern void WM_EndKeySharing_0x02023ad0(int h);
extern void func_ov029_020b2f40(int h);
extern int func_02020a9c(void);
extern void func_ov022_020b1fc4(char *p);
extern void func_ov022_020b1484(void);
extern void func_ov022_02090160(void);
extern void func_ov022_02094c20(void);
extern void func_020362e8(char *p);
extern void func_0201e4a8(int a, int b);
extern int data_ov022_020b2e78;

/* Unloads every loaded party member (one extra slot in the 0x2a language), then drops the shared
 * blocks, the two animation banks and the field handle.
 * The loop is written with an explicit goto because the ROM tests before the first pass. */
void func_ov022_020871fc(void) {
    char *heap = NNSi_FndGetCurrentRootHeap();
    int i = 0;
    char *slot = heap;
    int extra;
    goto test;
body:
    {
        char *obj = *(char **)(*(char **)(slot + 4) + 0x20);
        func_ov022_020883f4(i);
        func_ov022_02087298(i);
        SNDi_ProcessEntry(*(signed char *)(obj + 0x4bc));
        WM_EndKeySharing_0x02023ad0(*(int *)(slot + 4));
        func_ov029_020b2f40(*(int *)(slot + 8));
    }
    slot += 0xc;
    i++;
test:
    extra = func_02020a9c() == 0x2a ? 1 : 0;
    if (i < *(unsigned char *)(heap + 0x34) + extra) {
        goto body;
    }
    if (*(int *)(heap + 0x38) != -1) {
        WM_EndKeySharing_0x02023ad0(*(int *)(heap + 0x38));
    }
    func_ov022_020b1fc4(heap + 0x68);
    func_ov022_020b1fc4(heap + 0xa4);
    func_ov022_020b1484();
    func_ov022_02090160();
    func_ov022_02094c20();
    func_020362e8(heap + 0x4c);
    func_0201e4a8(0, *(int *)(heap + 0x44));
    *(int *)((char *)&data_ov022_020b2e78 + 4) = 0;
}
