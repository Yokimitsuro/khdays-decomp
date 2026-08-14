typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    u8 raw[0x108];
} Ov003AnimObject;

typedef struct {
    u8 raw[0x24];
} Ov003AnimBinding;

typedef struct {
    u16 nPlayerCount;                       /* +0x0000 */
    u8 pad0002[0x2a];
    int aRankGroups[4];                     /* +0x002c */
    u8 pad003c[0x18];
    int nLayerMode;                         /* +0x0054 */
    u8 pad0058[0x9f8];
    Ov003AnimObject aMainAnims[4];          /* +0x0a50, stride 0x108 */
    Ov003AnimObject aExtraAnims[4];         /* +0x0e70, stride 0x108 */
    int aHasExtraAnim[4];                   /* +0x1290 */
    u8 pad12a0[0x420];
    Ov003AnimBinding aAnimBindings[4];      /* +0x16c0, stride 0x24 */
    int aAnimTimers[4];                     /* +0x1750 */
    u8 pad1760[4];
    int aAnimFinished[4];                   /* +0x1764 */
    int nAllRanksFinished;                  /* +0x1774 */
    u8 pad1778[0x698];
    int nVariantMode;                       /* +0x1e10 */
    int nVariantValue;                      /* +0x1e14 */
} Ov003SceneContext;

extern int data_ov003_0204f724[];
extern int func_ov003_0204eb84(void);

extern Ov003SceneContext *NNSi_FndGetCurrentRootHeap(void);
extern int func_ov105_020bd7c4(void);
extern void func_ov003_0204e91c(Ov003SceneContext *pContext);
extern void func_0202accc(int nObject, int nTrack, int nBinding, int nAnim);
extern unsigned int func_0202a928(int nObject, int nMask);
extern void func_0202a818(void *pObject, int nMask);

int func_ov003_0204e9d8(void)
{
    Ov003SceneContext *root;
    int *pThresholds;
    int nNextState;
    int nTimer;
    int nRankGroup;
    int i;
    unsigned int nMask;
    Ov003AnimBinding *pBinding;
    Ov003AnimObject *pMainAnim;
    Ov003AnimObject *pExtraAnim;

    root = NNSi_FndGetCurrentRootHeap();
    nNextState = 0;
    if (root->nVariantMode == 0) {
        root->nVariantValue = func_ov105_020bd7c4();
    }
    func_ov003_0204e91c(root);

    if (root->nLayerMode == 1 &&
        (i = 0, 0 < (int)(unsigned int)root->nPlayerCount)) {
        pThresholds = data_ov003_0204f724;
        pBinding = &root->aAnimBindings[0];
        pMainAnim = &root->aMainAnims[0];
        pExtraAnim = &root->aExtraAnims[0];
        do {
            if (root->aAnimFinished[i] == 0) {
                nTimer = root->aAnimTimers[i];
                root->aAnimTimers[i] = nTimer + 300;
                nRankGroup = root->aRankGroups[i];
                if (nTimer + 300 >= pThresholds[nRankGroup]) {
                    if (nRankGroup == 0) {
                        root->aAnimFinished[i] = 1;
                        root->nAllRanksFinished = 0;
                        nNextState = (int)func_ov003_0204eb84;
                    } else if (nRankGroup != 3) {
                        root->aAnimFinished[i] = 1;
                        func_0202accc((int)pMainAnim, 0, (int)pBinding, 4);
                        if (root->aHasExtraAnim[i] != 0) {
                            func_0202accc((int)pExtraAnim, 0,
                                          (int)((u8 *)pExtraAnim + 0xe0), 4);
                        }
                    }
                }
            } else {
                nMask = func_0202a928((int)pMainAnim, 0x1000);
                if ((nMask & 1) != 0) {
                    func_0202accc((int)pMainAnim, 0, (int)pBinding, 5);
                    if (root->aHasExtraAnim[i] != 0) {
                        func_0202accc((int)pExtraAnim, 0,
                                      (int)((u8 *)pExtraAnim + 0xe0), 5);
                    }
                }
            }

            func_0202a818(pMainAnim, 0x1000);
            if (root->aHasExtraAnim[i] != 0) {
                func_0202a818(pExtraAnim, 0x1000);
            }

            pBinding++;
            pMainAnim++;
            pExtraAnim++;
            i++;
        } while (i < root->nPlayerCount);
    }
    return nNextState;
}

