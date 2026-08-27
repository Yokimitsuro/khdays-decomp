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

void func_01ffa7fc(VecFx32 *first, VecFx32 *second)
{
    s64 firstSquared = (s64)first->x * first->x + (s64)first->y * first->y;
    s64 firstScale;
    fx32 firstMagnitude;
    s64 secondSquared;
    fx32 secondMagnitude;
    s64 secondScale;

    firstSquared += (s64)first->z * first->z;

    REG_DIVCNT = 2;
    REG_DIV_NUMER = 0x0100000000000000ULL;
    REG_DIV_DENOM = firstSquared;
    REG_SQRTCNT = 1;
    REG_SQRT_PARAM = (u64)(firstSquared * 4);

    secondSquared = (s64)second->x * second->x + (s64)second->y * second->y;
    secondSquared += (s64)second->z * second->z;

    while (REG_SQRTCNT & 0x8000) {
    }
    firstMagnitude = (fx32)REG_SQRT_RESULT;
    REG_SQRTCNT = 1;
    REG_SQRT_PARAM = (u64)(secondSquared * 4);

    while (REG_DIVCNT & 0x8000) {
    }
    firstScale = REG_DIV_RESULT;

    REG_DIVCNT = 2;
    REG_DIV_NUMER = 0x0100000000000000ULL;
    firstScale *= firstMagnitude;
    REG_DIV_DENOM = secondSquared;

    first->x = (fx32)((firstScale * first->x + (1LL << 44)) >> 45);
    first->y = (fx32)((firstScale * first->y + (1LL << 44)) >> 45);
    first->z = (fx32)((firstScale * first->z + (1LL << 44)) >> 45);

    while (REG_SQRTCNT & 0x8000) {
    }
    secondMagnitude = (fx32)REG_SQRT_RESULT;
    while (REG_DIVCNT & 0x8000) {
    }
    secondScale = REG_DIV_RESULT;
    secondScale *= secondMagnitude;

    second->x = (fx32)((secondScale * second->x + (1LL << 44)) >> 45);
    second->y = (fx32)((secondScale * second->y + (1LL << 44)) >> 45);
    second->z = (fx32)((secondScale * second->z + (1LL << 44)) >> 45);
}
