typedef unsigned short u16;
typedef unsigned int u32;

typedef union Ov008DisplayFlags {
    u32 raw;
    struct {
        u32 bits_0_1 : 2;
        u32 skipBrightnessUpdate : 1;
        u32 rest : 29;
    } bits;
} Ov008DisplayFlags;

typedef struct Ov008UpdateNode {
    int (*update)(void);
} Ov008UpdateNode;

extern int data_ov008_02090f04[];

#define CTXV (*(volatile int *)((char *)data_ov008_02090f04 + 4))

extern void CP_SaveContext(void *context);
extern void CPi_RestoreContext(void *context);
extern void func_0203602c(void *value, void *state);
extern int func_ov008_0204ee40(void);
extern void func_0201e3cc(int brightness);
extern int func_ov008_020511b0(void);
extern void func_0201e374(int brightness);
extern void *NNS_FndGetNextListObject(void *list, void *previous);
extern void func_ov008_02050d50(void *node);

#define REG_DIV_CNT (*(volatile u16 *)0x04000280)

void func_ov008_0204f038(void)
{
    u32 cpContext[7];
    volatile u16 *divControl;
    int brightness;
    Ov008UpdateNode *node;
    Ov008UpdateNode *next;

    *(int *)(CTXV + 0x95f4) = 0;

    if (((Ov008DisplayFlags *)(CTXV + 0x95f0))->bits.skipBrightnessUpdate == 0) {
        int tweenContext;

        CP_SaveContext(cpContext);
        tweenContext = CTXV;
        func_0203602c((void *)(tweenContext + 0x95d8),
                      (void *)(tweenContext + 0x95d4));
        CPi_RestoreContext(cpContext);

        divControl = &REG_DIV_CNT;
        while ((*divControl & 0x8000) != 0) {
        }

        brightness = *(int *)(CTXV + 0x95d4) >> 12;
        if (func_ov008_0204ee40() == 6 ||
            func_ov008_0204ee40() == 7) {
            func_0201e3cc(brightness);
        } else {
            if (*(int *)(CTXV + 0x95f8) != 0) {
                func_0201e3cc(brightness);
            }
            if (func_ov008_020511b0() != 0 &&
                *(int *)(CTXV + 0x974c) == 0 && brightness > -8) {
                brightness = -8;
            }
            func_0201e374(brightness);
        }
    }

    node = NNS_FndGetNextListObject((void *)(CTXV + 0x9660), 0);
    if (node == 0) {
        return;
    }

    do {
        next = NNS_FndGetNextListObject((void *)(CTXV + 0x9660), node);
        if (node->update() == 0) {
            func_ov008_02050d50(node);
        }
        node = next;
    } while (next != 0);
}
