/* Slot-2 tick of the second ov255 helper: while armed (+8), every live, solid object of the
 * world's +0xa8 list within 12.0 of the helper's +0xc point is swirled: its direction to the point
 * is bent by the cross with data_02042240, normalised and scaled to 0.28 by how close it is, then
 * added to its +0xe4 push. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { void *item; } ListNode;
struct Bits40 { int b0 : 1, b1 : 1; };
struct Flags60 { u16 lo : 8; u16 hi : 8; };

extern ListNode *func_01fffd70(void *list);
extern ListNode *func_01fffd8c(void *list);
extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern int FX_Inv(int num, int den);
extern void VEC_CrossProduct(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void VEC_Add(const void *a, const void *b, void *out);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern const Vec3 data_02042240;

static inline int FX_Mul(int a, int b)
{
    return (int)(((long long)a * b + 0x800) >> 12);
}

void func_ov255_020d14ec(int *node)
{
    int *h = (int *)node[1];
    Vec3 d;
    Vec3 push;
    Vec3 c;
    ListNode *link;
    char *obj;
    int world;
    int dist;
    int t;

    if (h[2] == 0) {
        return;
    }
    world = *(int *)(h[0] + 4);
    link = func_01fffd70((void *)(world + 0xa8));
    obj = link == 0 ? 0 : (char *)link->item;
    while (obj != 0) {
        if (((struct Bits40 *)(obj + 0x40))->b1 && (((struct Flags60 *)(obj + 0x60))->lo & 1) != 0) {
            VEC_Subtract(h + 3, obj + 0x74, &d);
            dist = func_01ff8d18(&d, &d);
            if (dist <= 0xc000) {
                t = FX_Inv(dist, 0xc000);
                if (t < 0) {
                    t = 0;
                }
                if (t > 0x1000) {
                    t = 0x1000;
                }
                VEC_CrossProduct(&data_02042240, &d, &c);
                VEC_Add(&d, &c, &d);
                func_01ff8d18(&d, &d);
                func_01ffa724(FX_Mul(0x1000 - t, 0x480), &d, &push);
                VEC_Add(obj + 0xe4, &push, obj + 0xe4);
            }
        }
        link = func_01fffd8c((void *)(world + 0xa8));
        obj = link == 0 ? 0 : (char *)link->item;
    }
}
