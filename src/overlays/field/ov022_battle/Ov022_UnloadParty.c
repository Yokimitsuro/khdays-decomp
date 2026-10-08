extern char *NNSi_FndGetCurrentRootHeap(void);
extern void Ov022_CleanupEntry(int slot);
extern void func_ov022_02087298(int slot);
extern void SNDi_ProcessEntry(int id);
extern void VeneerTo_Obj_Destroy(int h);
extern void Ov029_ReleaseOverlaySlot(int h);
extern int LoadGlobalU16At0(void);
extern void Ov022_FreeResourceSubLists(char *p);
extern void func_ov022_020b1484(void);
extern void func_ov022_02090160(void);
extern void func_ov022_02094c20(void);
extern void ConstReturn1_2(char *p);
extern void UnloadOverlaySync(int a, int b);
extern int data_ov022_020b2e78;

/* Unloads every loaded party member (one extra slot in the 0x2a language), then drops the shared
 * blocks, the two animation banks and the field handle.
 * The loop is written with an explicit goto because the ROM tests before the first pass. */
void Ov022_UnloadParty(void) {
    char *heap = NNSi_FndGetCurrentRootHeap();
    int i = 0;
    char *slot = heap;
    int extra;
    goto test;
body:
    {
        char *obj = *(char **)(*(char **)(slot + 4) + 0x20);
        Ov022_CleanupEntry(i);
        func_ov022_02087298(i);
        SNDi_ProcessEntry(*(signed char *)(obj + 0x4bc));
        VeneerTo_Obj_Destroy(*(int *)(slot + 4));
        Ov029_ReleaseOverlaySlot(*(int *)(slot + 8));
    }
    slot += 0xc;
    i++;
test:
    extra = LoadGlobalU16At0() == 0x2a ? 1 : 0;
    if (i < *(unsigned char *)(heap + 0x34) + extra) {
        goto body;
    }
    if (*(int *)(heap + 0x38) != -1) {
        VeneerTo_Obj_Destroy(*(int *)(heap + 0x38));
    }
    Ov022_FreeResourceSubLists(heap + 0x68);
    Ov022_FreeResourceSubLists(heap + 0xa4);
    func_ov022_020b1484();
    func_ov022_02090160();
    func_ov022_02094c20();
    ConstReturn1_2(heap + 0x4c);
    UnloadOverlaySync(0, *(int *)(heap + 0x44));
    *(int *)((char *)&data_ov022_020b2e78 + 4) = 0;
}
