typedef struct {
    char pad00[0x18];
    int nodeId;     /* +0x18, -1 when none */
    char pad1c[0x28];
    void *bufA;     /* +0x44 */
    char pad48[4];
    void *bufB;     /* +0x4c */
} Ov002Res;

typedef struct {
    char pad00[0x74];
    int f74;
    int f78;
} Ov107Node;

extern Ov107Node *OS_IsThreadAvailable_0x020c9848(void);
extern void func_ov107_020c9c1c(int nodeId);
extern void func_02035d90(void);
extern void NNSi_FndFreeFromDefaultHeap(void *p);
extern void func_ov002_02072cdc(void);

extern Ov002Res *data_ov002_0207fa14;

void func_ov002_020736c0(void) {
    Ov002Res *r = data_ov002_0207fa14;

    if (r->nodeId != -1) {
        OS_IsThreadAvailable_0x020c9848()->f74 = 0;
        OS_IsThreadAvailable_0x020c9848()->f78 = 0;
        func_ov107_020c9c1c(r->nodeId);
        func_02035d90();
        r->nodeId = -1;
    }
    if (r->bufA != 0) {
        NNSi_FndFreeFromDefaultHeap(r->bufA);
        r->bufA = 0;
    }
    if (r->bufB != 0) {
        NNSi_FndFreeFromDefaultHeap(r->bufB);
        r->bufB = 0;
    }
    func_ov002_02072cdc();
}
