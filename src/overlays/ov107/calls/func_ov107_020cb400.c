typedef unsigned char u8;
typedef unsigned short u16;
typedef int fx32;

typedef struct {
    unsigned pad0 : 1;
    int flag1 : 1;
    int flag2 : 1;
    unsigned rest : 29;
} Flags40;

typedef struct {
    u16 lo : 8;
    u16 hi : 8;
} SplitU16;

extern char **func_01fffd70(void *listHead);
extern char **func_01fffd8c(void *listHead);
extern int func_ov107_020cab14(void *node, int *out);
extern void VEC_Subtract(int *a, int *b, int *out);
extern fx32 VEC_Mag(const int *v);

void func_ov107_020cb400(char *self) {
    char *base = *(char **)self;
    char *sub = *(char **)(base + 4);
    char *listHead = sub + 0x80;
    char **iter;
    char *node;

    iter = func_01fffd70(listHead);
    node = (iter == 0) ? 0 : *iter;
    if (node == 0) {
        return;
    }

    do {
        if (((Flags40 *)(node + 0x40))->flag1) {
            if (((Flags40 *)(node + 0x40))->flag2) {
                u16 b = ((SplitU16 *)(node + 0x60))->lo;
                if (b & 1) {
                    int tmp0;
                    if (func_ov107_020cab14(node, &tmp0)) {
                        int diff[3];
                        VEC_Subtract((int *)(self + 0x1c), (int *)(node + 0x74), diff);
                        if (VEC_Mag(diff) > *(int *)(self + 0x28) + *(int *)(node + 0x80)) {
                            void (*cb)(void *, int) = *(void (**)(void *, int))(node + 0x1cc);
                            if (cb != 0) {
                                cb(node, 2);
                            }
                        }
                    }
                }
            }
        }

        iter = func_01fffd8c(listHead);
        node = (iter == 0) ? 0 : *iter;
    } while (node != 0);
}
