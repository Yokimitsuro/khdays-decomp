typedef signed long s32;
typedef unsigned long u32;
typedef signed long long s64;
typedef unsigned long long u64;
typedef volatile unsigned short vu16;
typedef volatile unsigned long vu32;
typedef volatile signed long long vs64;
typedef volatile unsigned long long vu64;

typedef s32 fx32;

typedef struct VecFx32 {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

#define REG_DIVCNT          (*(vu16 *)0x04000280)
#define REG_DIV_NUMER       (*(vu64 *)0x04000290)
#define REG_DIV_DENOM       (*(vs64 *)0x04000298)
#define REG_DIV_RESULT      (*(vs64 *)0x040002a0)
#define REG_SQRTCNT         (*(vu16 *)0x040002b0)
#define REG_SQRT_RESULT     (*(vu32 *)0x040002b4)
#define REG_SQRT_PARAM      (*(u64 *)0x040002b8)

fx32 func_01ff8d18(const VecFx32 *source, VecFx32 *destination)
{
    s64 squaredMagnitude = (s64)source->x * source->x;
    fx32 magnitude;

    squaredMagnitude += (s64)source->y * source->y;
    squaredMagnitude += (s64)source->z * source->z;

    REG_DIVCNT = 2;
    REG_DIV_NUMER = 0x0100000000000000ULL;
    REG_DIV_DENOM = squaredMagnitude;
    REG_SQRTCNT = 1;
    REG_SQRT_PARAM = (u64)(squaredMagnitude * 4);

    while (REG_SQRTCNT & 0x8000) {
    }
    magnitude = (fx32)REG_SQRT_RESULT;
    while (REG_DIVCNT & 0x8000) {
    }

    squaredMagnitude = REG_DIV_RESULT;
    squaredMagnitude *= magnitude;
    destination->x = (fx32)((squaredMagnitude * source->x + (1LL << 44)) >> 45);
    destination->y = (fx32)((squaredMagnitude * source->y + (1LL << 44)) >> 45);
    destination->z = (fx32)((squaredMagnitude * source->z + (1LL << 44)) >> 45);

    return (magnitude + 1) >> 1;
}
