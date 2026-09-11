typedef signed long fx32;

typedef struct VecFx32 {
    fx32 x, y, z;
} VecFx32;

typedef struct MtxFx33 {
    fx32 _00, _01, _02;
    fx32 _10, _11, _12;
    fx32 _20, _21, _22;
} MtxFx33;

extern void VEC_Subtract(int *a, int *b, int *out);
extern fx32 func_01ff8d18(const VecFx32 *source, VecFx32 *destination);
extern void INITi_CpuClear32_0x01ff86fc(unsigned int data, void *dst, unsigned int size);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern void func_01ffa724(int factor, int *src, int *dst);
extern void VEC_CrossProduct(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern VecFx32 data_02042264;
extern VecFx32 data_02042258;

/* Build a look-at rotation matrix: forward = to - from, with up as the
 * preferred reference vector. If up is (near) parallel to forward the
 * reference falls back to the world axis data_02042264, then to
 * data_02042258, before giving up and zeroing the matrix. */
int func_0203cd7c(MtxFx33 *out, VecFx32 *from, VecFx32 *to, VecFx32 *up)
{
    VecFx32 forward;
    VecFx32 ref;
    VecFx32 proj;
    VecFx32 right;

    VEC_Subtract((int *)to, (int *)from, (int *)&forward);
    if (func_01ff8d18(&forward, &forward) == 0) {
        INITi_CpuClear32_0x01ff86fc(0, out, sizeof(MtxFx33));
        return 0;
    }

    func_01ffa724(VEC_DotProduct(up, &forward), (int *)&forward, (int *)&proj);
    VEC_Subtract((int *)up, (int *)&proj, (int *)&ref);
    if (func_01ff8d18(&ref, &ref) == 0) {
        func_01ffa724(forward.y, (int *)&forward, (int *)&proj);
        VEC_Subtract((int *)&data_02042264, (int *)&proj, (int *)&ref);
        if (func_01ff8d18(&ref, &ref) == 0) {
            func_01ffa724(forward.z, (int *)&forward, (int *)&proj);
            VEC_Subtract((int *)&data_02042258, (int *)&proj, (int *)&ref);
            if (func_01ff8d18(&ref, &ref) == 0) {
                INITi_CpuClear32_0x01ff86fc(0, out, sizeof(MtxFx33));
                return 0;
            }
        }
    }

    VEC_CrossProduct(&ref, &forward, &right);
    out->_00 = -right.x;
    out->_10 = ref.x;
    out->_20 = -forward.x;
    out->_01 = -right.y;
    out->_11 = ref.y;
    out->_21 = -forward.y;
    out->_02 = -right.z;
    out->_12 = ref.z;
    out->_22 = -forward.z;
    return 1;
}
