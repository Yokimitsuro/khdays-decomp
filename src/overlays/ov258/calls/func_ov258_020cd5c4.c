/* Vortex pull of the ov258 actor: every active object (+0x40 bit 1, +0x60 low bit 0) of the world's
 * +0xa8 list within 24.0 of the +0x1c point is pushed at 0.28 along its direction swirled by the up
 * axis (cross product added), into its +0xe4 velocity. */
typedef struct { int x, y, z; } Vec3;
typedef struct { int b0 : 1; int b1 : 1; } Bits;
typedef struct { unsigned short lo : 8; unsigned short hi : 8; } Flags16;

extern int *func_01fffd70(void *list);
extern int *func_01fffd8c(void *list);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void VEC_CrossProduct(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern const Vec3 data_02042240;

void func_ov258_020cd5c4(int *node)
{
    int *state = (int *)node[1];
    int world = *(int *)(*state + 4);
    Vec3 d;
    Vec3 push;
    Vec3 swirl;
    int *it;
    char *obj;

    it = func_01fffd70((void *)(world + 0xa8));
    for (obj = it == 0 ? 0 : (char *)*it; obj != 0; obj = it == 0 ? 0 : (char *)*it) {
        if (((Bits *)(obj + 0x40))->b1 && (((Flags16 *)(obj + 0x60))->lo & 1)) {
            VEC_Subtract((Vec3 *)(state + 7), (Vec3 *)(obj + 0x74), &d);
            if (func_01ff8d18(&d, &d) <= 0x18000) {
                VEC_CrossProduct(&data_02042240, &d, &swirl);
                VEC_Add(&d, &swirl, &d);
                func_01ff8d18(&d, &d);
                func_01ffa724(0x470, &d, &push);
                VEC_Add((Vec3 *)(obj + 0xe4), &push, (Vec3 *)(obj + 0xe4));
            }
        }
        it = func_01fffd8c((void *)(world + 0xa8));
    }
}
