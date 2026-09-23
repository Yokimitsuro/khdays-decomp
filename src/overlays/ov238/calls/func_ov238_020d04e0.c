/* Teardown hook of the ov238 actor's carrier: its +0x3dc model takes the +0x3ec anchor's transform and
 * mirrors it onto the +0x38c set's first model; the data_ov238_020d3668 offset turned by the +0x3f8
 * part's rotation is added to that part's +0x14 position. Outside move 8 the +0x438 effect stops; then
 * the base teardown runs. */
typedef struct { int x, y, z; } Vec3;
typedef struct { int w[11]; } SrtTransform;
struct Posed { char pad[0x10]; SrtTransform srt; };
struct Anchor { char pad[4]; SrtTransform srt; };

extern void func_0202f384(Vec3 *out, void *rotation, const Vec3 *in);
extern void func_0203c650(int model, int handle);
extern void func_ov107_020c7ca4(char *self);
extern const Vec3 data_ov238_020d3668;

void func_ov238_020d04e0(char *self)
{
    Vec3 off;

    (*(struct Posed **)(self + 0x3dc))->srt = (*(struct Anchor **)(self + 0x3ec))->srt;
    (**(struct Posed ***)(self + 0x38c))->srt = (*(struct Posed **)(self + 0x3dc))->srt;
    off = data_ov238_020d3668;
    func_0202f384(&off, (void *)(*(int *)(self + 0x3f8) + 4), &off);
    *(int *)(*(int *)(self + 0x3f8) + 0x1c) += off.z;
    *(int *)(*(int *)(self + 0x3f8) + 0x14) += off.x;
    *(int *)(*(int *)(self + 0x3f8) + 0x18) += off.y;
    if (*(signed char *)(self + 0x1c6) != 8 && *(int *)(self + 0x438) != 0) {
        func_0203c650(*(int *)(self + 0x3c), *(int *)(self + 0x438));
        *(int *)(self + 0x438) = 0;
    }
    func_ov107_020c7ca4(self);
}
