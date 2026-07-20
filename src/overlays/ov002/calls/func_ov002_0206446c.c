typedef struct {
    void *owner;      /* +0x00 */
    char pad04[4];
    void *bufA;       /* +0x08 */
    void *bufB;       /* +0x0c */
    void *bufC;       /* +0x10 */
    void *bufD;       /* +0x14 */
    void *bufE;       /* +0x18 */
    void *bufF;       /* +0x1c */
} Ov002Block;

typedef struct {
    char pad00[8];
    int active;       /* +0x08 */
} Ov002Handle;

extern Ov002Block *data_ov002_0207f634;
extern Ov002Handle *func_ov002_020636ac(void);
extern void func_02033bb4(int a, int b, int c);
extern void NNSi_FndFreeFromDefaultHeap(void *p);
extern void WM_EndKeySharing_0x02023ad0(void *p);

void func_ov002_0206446c(void) {
    Ov002Block *b = data_ov002_0207f634;
    Ov002Handle *h = func_ov002_020636ac();

    if (h->active != 0) {
        func_02033bb4(0, 0x32, 0);
        h->active = 0;
    }
    if (b->bufA != 0) NNSi_FndFreeFromDefaultHeap(b->bufA);
    if (b->bufB != 0) NNSi_FndFreeFromDefaultHeap(b->bufB);
    if (b->bufE != 0) NNSi_FndFreeFromDefaultHeap(b->bufE);
    if (b->bufF != 0) NNSi_FndFreeFromDefaultHeap(b->bufF);
    if (b->bufC != 0) NNSi_FndFreeFromDefaultHeap(b->bufC);
    if (b->bufD != 0) NNSi_FndFreeFromDefaultHeap(b->bufD);
    WM_EndKeySharing_0x02023ad0(b->owner);
    data_ov002_0207f634 = 0;
}
