typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;
typedef signed long long s64;
typedef unsigned long long u64;

typedef struct VecFx32 { s32 x; s32 y; s32 z; } VecFx32;
typedef struct VecFx16 { s16 x; s16 y; s16 z; } VecFx16;

#define DIVCNT      (*(volatile u16 *)0x04000280)
#define DIV_RESULT  (*(volatile s64 *)0x040002a0)
#define SQRTCNT     (*(volatile u16 *)0x040002b0)
#define SQRT_RESULT (*(volatile u32 *)0x040002b4)

static inline s16 NormalizeComponent(s32 value, s64 scale)
{
    return (s16)((scale * value + 0x100000000000LL) >> 45);
}

static inline void CP_SetDivImm64_64_NS_(u64 numerator, u64 denominator)
{
    *(u64 *)0x04000290 = numerator;
    *(u64 *)0x04000298 = denominator;
}

static inline void CP_SetDiv64_64(u64 numerator, u64 denominator)
{
    DIVCNT = 2;
    CP_SetDivImm64_64_NS_(numerator, denominator);
}

static inline void CP_SetSqrtImm64_NS_(u64 parameter)
{
    *(u64 *)0x040002b8 = parameter;
}

static inline void CP_SetSqrt64(u64 parameter)
{
    SQRTCNT = 1;
    CP_SetSqrtImm64_NS_(parameter);
}

void func_01ffcfd0(const VecFx32 *input, VecFx16 *output)
{
    s64 squared;
    s64 scale;
    s32 sqrtResult;
    s32 y;
    s32 x;

    y = input->y;
    x = *(volatile const s32 *)&input->x;
    squared = (s64)x * x;
    squared += (s64)y * y;
    squared += (s64)input->z * input->z;

    CP_SetDiv64_64(0x0100000000000000LL, (u64)squared);
    CP_SetSqrt64((u64)(squared * 4));

    while (SQRTCNT & 0x8000) {
    }
    sqrtResult = (s32)SQRT_RESULT;
    while (DIVCNT & 0x8000) {
    }
    scale = DIV_RESULT * (s64)sqrtResult;

    output->x = NormalizeComponent(input->x, scale);
    output->y = NormalizeComponent(input->y, scale);
    output->z = NormalizeComponent(input->z, scale);
}
