/* NONMATCHING: semantically complete, stack-layout residue. Body/relocs match; the ROM
 * spills the operand value to sp+0 and leaves an 8-byte gap before the 0x100 sprintf buffer
 * (frame 0x128), while mwcc keeps it in a callee-saved reg (frame 0x120). Register-pressure
 * driven; no source form tried forced the spill. Also: ldrsb obj/offset load order.
 * Behaviour: format a number/name (self[0x4a] name field at +0x4a4) into text, widen it, and
 * submit it via func_ov002_02057300 as a 7-field draw item {text,0,0,0,value,-1,0}. */
typedef unsigned char u8;

typedef struct {
    void *pText;
    int nUnk04;
    int nUnk08;
    int nUnk0c;
    int nValue;
    int nUnk14;
    int nUnk18;
} TextDrawItem;

extern int func_02021980(int self, unsigned short *operand);
extern int func_02021948(int self, unsigned short *operand);
extern void func_ov002_02075528(char *buf, void *name);
extern int OS_SPrintf(char *buf, const char *fmt, ...);
extern int strlen(const char *s);
extern void *NNSi_FndAllocFromDefaultExpHeap(int size);
extern int OS_SNPrintf(char *buf, int size, const char *fmt, ...);
extern void func_0202fcb8(char *narrow, void *wide);
extern void NNSi_FndFreeFromDefaultHeap(void *ptr);
extern void func_ov002_02057300(TextDrawItem *item, int arg);
extern const char data_ov002_0207f404[];

void func_ov002_02075578(int self, unsigned short *operand) {
    int value = func_02021980(self, operand + 8);
    char buf[0x100];
    TextDrawItem item;
    char *narrow;
    void *wide;
    int obj;
    int len;

    obj = *(int *)(self + 0x128);
    if (*(signed char *)(obj + 0x4a4) != 0) {
        OS_SPrintf(buf, data_ov002_0207f404, obj + 0x4a4);
    } else {
        OS_SPrintf(buf, data_ov002_0207f404,
                   func_02021948(self, operand));
    }
    func_ov002_02075528(buf, (void *)(*(int *)(self + 0x128) + 0x4a4));

    len = strlen(buf);
    narrow = (char *)NNSi_FndAllocFromDefaultExpHeap(len * 2);
    wide = NNSi_FndAllocFromDefaultExpHeap(len * 4);
    OS_SNPrintf(narrow, len * 2, buf, *(int *)(*(int *)(self + 0x128) + 0x10));
    func_0202fcb8(narrow, wide);
    NNSi_FndFreeFromDefaultHeap(narrow);

    item.pText = wide;
    item.nUnk04 = 0;
    item.nUnk08 = 0;
    item.nUnk0c = 0;
    item.nValue = value;
    item.nUnk14 = -1;
    item.nUnk18 = 0;
    func_ov002_02057300(&item, 0);
    NNSi_FndFreeFromDefaultHeap(wide);
}
