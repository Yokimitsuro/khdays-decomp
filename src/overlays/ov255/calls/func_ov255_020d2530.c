/* Draw handler of the ov255 shake entries: the camera-facing turn (from data_0204227c towards the
 * scene's +0x7c direction) is set as the global base rotation; every live entry (0x38 bytes) of
 * the +0x90 table is drawn with the +0x88 model's +0x78 mesh at its +0x2c point, scaled by its
 * offset, with polygon id = its handle, alpha = strength x 31 and a colour fading from white to
 * red with the strength. */
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { int w[4]; } Quat;
struct Shake { int offset; int strength; char pad08[0x10]; int handle; char pad1c[0x10]; Vec3 at; };
struct G3Glb { char pad[0xc4]; Vec3 scale; };

extern int *OS_IsThreadAvailable_0x020c9848(void);
extern void func_0202ed60(Quat *out, const Vec3 *a, const Vec3 *b);
extern void func_0202ec2c(void *mtx, const Quat *q);
extern void func_02015880(const Vec3 *v);
extern void func_0201574c(void);
extern void func_02016cd0(int model, int id);
extern void func_02016bd8(int model, int mat, int alpha);
extern void func_02016c50(int model, u16 rgb);
extern void func_01ffcc1c(int model, int a, int b, int c);
extern const Vec3 data_0204227c;
extern char data_02047428[];
extern struct G3Glb data_02047394;

static inline void VEC_Set(Vec3 *v, int x, int y, int z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}

static inline short ClampColor(short v)
{
    return v > 31 ? 31 : (v < 0 ? 0 : v);
}

static inline int FX_Mul(int a, int b)
{
    return (int)(((long long)a * b + 0x800) >> 12);
}

void func_ov255_020d2530(char *self)
{
    Quat q;
    int i;
    int off;

    func_0202ed60(&q, &data_0204227c, (Vec3 *)(*OS_IsThreadAvailable_0x020c9848() + 0x7c));
    func_0202ec2c(data_02047428, &q);
    i = 0;
    if (*(int *)(self + 0x8c) > 0) {
        do {
            struct Shake *e = &(*(struct Shake **)(self + 0x90))[i];

            if (e->offset != 0) {
                int alpha;
                int c;
                short g;
                short b;

                alpha = (e->strength * 31) >> 12;
                VEC_Set(&data_02047394.scale, e->offset, e->offset, e->offset);
                func_02015880(&e->at);
                func_0201574c();
                func_02016cd0(*(int *)(*(int *)(self + 0x88) + 0x78), e->handle);
                func_02016bd8(*(int *)(*(int *)(self + 0x88) + 0x78), 0, alpha);
                c = (FX_Mul(e->strength, 0x1400) * 31) >> 12;
                g = ClampColor(c);
                b = ClampColor(c - 16);
                func_02016c50(*(int *)(*(int *)(self + 0x88) + 0x78), (u16)((b << 10) | (31 | (g << 5))));
                func_01ffcc1c(*(int *)(*(int *)(self + 0x88) + 0x78), 0, 0, 1);
            }
        } while (++i < *(int *)(self + 0x8c));
    }
}
