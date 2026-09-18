/* Model pose init of the ov163 enemy (x3: ov163/164/165), variant of the matched ov202 sibling:
 * copies the +0x3c0 item's transform into +0x394, then moves its translation 0x800 towards the
 * camera's +0x88 focus (direction normalised from the pose position). */
typedef struct { int x, y, z; } Vec3;

typedef struct {
    int data[11];
} Mat;

typedef struct {
    char pad0[0x394];
    Mat mat;
    char *src;
} Obj;

extern void func_ov107_020c4924(Obj *obj);
extern char *OS_IsThreadAvailable_0x020c9848(void);   /* the game's camera-state getter, named after the byte-identical SDK thunk */
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(Vec3 *v, Vec3 *out);
extern void func_01ffa724(int scale, Vec3 *v, Vec3 *out);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_0203ca30(Mat *mat, Vec3 *translation);

void func_ov164_020cfec0(Obj *obj) {
    Vec3 at;
    Vec3 dir;

    func_ov107_020c4924(obj);

    obj->mat = *(Mat *)(obj->src + 4);

    VEC_Subtract((Vec3 *)(*(char **)OS_IsThreadAvailable_0x020c9848() + 0x88), (Vec3 *)((char *)&obj->mat + 16), &dir);
    func_01ff8d18(&dir, &dir);
    func_01ffa724(0x800, &dir, &at);
    VEC_Add((Vec3 *)((char *)&obj->mat + 16), &at, &at);
    func_0203ca30(&obj->mat, &at);
}
