typedef int fx32;
typedef unsigned short u16;
typedef struct { fx32 x, y, z; } VecFx32;
typedef struct { fx32 rot[9]; VecFx32 pos; } MtxFx43;

extern void func_0203bc78(void *self);
extern int func_02016320(void *pRenderObj, MtxFx43 *pos, void *nrm, u16 nodeID);
extern void VEC_Subtract(VecFx32 *a, VecFx32 *b, VecFx32 *out);
extern fx32 func_01ff8d18(const VecFx32 *source, VecFx32 *destination);
extern void func_01ffa724(int factor, VecFx32 *src, VecFx32 *dst);
extern int func_02020a9c(void);
extern void func_0203b9fc(void *self, int a, int b, int c);
extern unsigned char data_0204c058;

typedef struct {
    unsigned char bit0 : 1;
    unsigned char bit1 : 1;
    unsigned char bit2 : 1;
    unsigned char bit3 : 1;
    unsigned char rest : 4;
} Flags4;

typedef struct {
    short id;             /* +0 */
    short field_02;        /* +2 */
    union {
        unsigned char field_04; /* +4 */
        Flags4 flags04;
    };
    unsigned char pad05[3];
    VecFx32 f08;             /* +8 */
    VecFx32 f14;               /* +0x14 */
    VecFx32 f20;                 /* +0x20 */
    VecFx32 f2c;                   /* +0x2c */
    unsigned char pad38[0x38 - 0x38];
    int f38;                         /* +0x38 */
} Node;

void func_ov107_020c9c90(char *self)
{
    Node *node = *(Node **)(self + 0x84);

    func_0203bc78(self);

    if (((unsigned)(node->field_04 << 0x1c)) >> 0x1f) {
        node->f38 = 0;
        node->f08 = node->f20;
        node->field_04 = (unsigned char)(node->field_04 & ~8);
    }

    {
        MtxFx43 mtx;
        void *renderObj = (char *)*(void **)(self + 0x88) + 0x20;

        if (func_02016320(renderObj, &mtx, 0, (u16)node->id) != 0) {
            VecFx32 tmpPos = mtx.pos;

            if (node->flags04.bit0) {
                node->field_04 = (unsigned char)(node->field_04 & ~1);
                node->f20 = tmpPos;
                node->f08 = node->f20;
                node->f38 = 0;
                return;
            }

            VEC_Subtract(&tmpPos, &node->f08, &node->f2c);
            node->f38 = func_01ff8d18(&node->f2c, &node->f14);

            if (data_0204c058 == 1) {
                node->f38 = (int)(((long long)node->f38 * 0xaaa + 0x800) >> 12);
                func_01ffa724(node->f38, &node->f14, &node->f2c);
            } else if (func_02020a9c() != 0x2a) {
                if (data_0204c058 == 2) {
                    node->f38 = node->f38 * 2;
                    func_01ffa724(node->f38, &node->f14, &node->f2c);
                }
            }

            node->f08 = tmpPos;
        }
    }

    if (*(unsigned char *)(self + 0xad) != 0) {
        return;
    }

    if (node->flags04.bit2) {
        func_0203b9fc(self, 0, node->field_02, 0);
        node->field_04 = (unsigned char)(node->field_04 | 8);
        return;
    }

    node->field_04 = (unsigned char)(node->field_04 | 2);
}
