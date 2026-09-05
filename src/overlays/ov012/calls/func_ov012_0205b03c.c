extern char *NNSi_FndGetCurrentRootHeap(void);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern int WM_EndKeySharing_0x0205bb78(void *renderer);
extern int func_0202f818(void *font);
extern void func_02020aa8(int slot, int value);
extern void func_0201e4a8(int processor, int overlayId);

extern unsigned int OVERLAY_24_ID[1];
#define FS_OVERLAY_ID_ov024 ((unsigned int)&OVERLAY_24_ID)

extern int data_ov012_0205c2a0;
extern char *data_ov012_0205cb20;

void func_ov012_0205b03c(void) {
    char *context;

    context = NNSi_FndGetCurrentRootHeap();
    NNSi_FndFreeFromDefaultHeap(*(void **)(context + 0x8bf8));
    NNSi_FndFreeFromDefaultHeap(*(void **)(context + 0x8bfc));
    WM_EndKeySharing_0x0205bb78(context + 0x8b4c);
    func_0202f818(context + 0x8b40);
    func_02020aa8(3, 0);
    func_0201e4a8(0, FS_OVERLAY_ID_ov024);
    data_ov012_0205c2a0 = -1;
    data_ov012_0205cb20 = 0;
    *(volatile unsigned short *)0x04000304 |= 0x8000;
}
