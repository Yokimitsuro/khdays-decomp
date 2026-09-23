/* Per-frame update of the ov258 actor: the five body segments (+0x3d8) take the transform of their
 * joint (+0x430 .. +0x444 chain) and point toward the next joint (length into +0x70); the first segment
 * sits 12.0 up and its +0x3d4 shadow rig copies it with a 3.375 (moves 3, 5, 7, 8) or 1.875 radius.
 * The three effect parts (+0x3ec..+0x3f4) sit on the +0x43c, +0x448 and +0x42c joints (the last 3.0
 * higher). With a +0x454 target the +0x430 head looks at it; then the base update runs. */
typedef struct { int x, y, z; } Vec3;
typedef struct { int m[9]; } Mtx33;
typedef struct { int w[4]; Vec3 t; int s[4]; } SrtTransform;
struct Xf10 { char pad[0x10]; SrtTransform srt; };
struct Ov258Body { char pad[0x3d8]; int parts[8]; };

extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_0203cd7c(Mtx33 *out, const Vec3 *target, const Vec3 *from, const Vec3 *up);
extern void func_0202ea48(void *srt, const Mtx33 *rot);
extern void func_ov107_020c7ca4(char *self);
extern const Vec3 data_02042264;

void func_ov258_020ccaf4(char *self)
{
    Vec3 d;
    SrtTransform srt;
    Mtx33 look;
    Vec3 pos;
    signed char i;
    int len;

    for (i = 0; i < 5; i++) {
        int part = ((struct Ov258Body *)self)->parts[i];

        switch (i) {
        case 0:
            srt = *(SrtTransform *)(*(int *)(self + 0x430) + 4);
            srt.t.y = 0xc000;
            VEC_Subtract((Vec3 *)(*(int *)(self + 0x42c) + 0x14), &srt.t, &d);
            len = func_01ff8d18(&d, &d);
            break;
        case 1:
            srt = *(SrtTransform *)(*(int *)(self + 0x434) + 4);
            VEC_Subtract((Vec3 *)(*(int *)(self + 0x438) + 0x14), &srt.t, &d);
            len = func_01ff8d18(&d, &d);
            break;
        case 2:
            srt = *(SrtTransform *)(*(int *)(self + 0x438) + 4);
            VEC_Subtract((Vec3 *)(*(int *)(self + 0x43c) + 0x14), &srt.t, &d);
            len = func_01ff8d18(&d, &d);
            break;
        case 3:
            srt = *(SrtTransform *)(*(int *)(self + 0x440) + 4);
            VEC_Subtract((Vec3 *)(*(int *)(self + 0x444) + 0x14), &srt.t, &d);
            len = func_01ff8d18(&d, &d);
            break;
        case 4:
            srt = *(SrtTransform *)(*(int *)(self + 0x444) + 4);
            VEC_Subtract((Vec3 *)(*(int *)(self + 0x448) + 0x14), &srt.t, &d);
            len = func_01ff8d18(&d, &d);
            break;
        }
        *(Vec3 *)(part + 0x64) = d;
        *(int *)(part + 0x70) = len;
        if (i == 0) {
            if (*(signed char *)(self + 0x1c6) == 3 || *(signed char *)(self + 0x1c6) == 5 ||
                *(signed char *)(self + 0x1c6) == 7 || *(signed char *)(self + 0x1c6) == 8) {
                *(int *)(**(int **)(self + 0x3d4) + 0x74) = 0x3600;
            } else {
                *(int *)(**(int **)(self + 0x3d4) + 0x74) = 0x1e00;
            }
            *(Vec3 *)(**(int **)(self + 0x3d4) + 0x64) = d;
            *(int *)(**(int **)(self + 0x3d4) + 0x70) = len;
        }
        ((struct Xf10 *)((struct Ov258Body *)self)->parts[i])->srt = srt;
        if (i == 0) {
            ((struct Xf10 *)**(int **)(self + 0x3d4))->srt = srt;
        }
    }
    for (; i < 8; i++) {
        int part = ((struct Ov258Body *)self)->parts[i];

        pos = i == 5 ? *(Vec3 *)(*(int *)(self + 0x43c) + 0x14)
                     : (i == 6 ? *(Vec3 *)(*(int *)(self + 0x448) + 0x14) : *(Vec3 *)(*(int *)(self + 0x42c) + 0x14));
        *(Vec3 *)(part + 0x58) = pos;
        if (i == 7) {
            *(int *)(part + 0x5c) += 0x3000;
        }
    }
    if (*(int *)(self + 0x454) != 0) {
        func_0203cd7c(&look, (Vec3 *)(*(int *)(self + 0x454) + 0x190), (Vec3 *)(*(int *)(self + 0x430) + 0x14),
                      &data_02042264);
        func_0202ea48((void *)(*(int *)(self + 0x430) + 4), &look);
    }
    func_ov107_020c7ca4(self);
}
