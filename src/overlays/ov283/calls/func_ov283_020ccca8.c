typedef signed int fx32;
typedef struct { fx32 x, y, z; } VecFx32;

extern void VEC_Subtract(fx32 *a, fx32 *b, fx32 *out);
extern fx32 func_01ff8d18(const VecFx32 *source, VecFx32 *destination);

int func_ov283_020ccca8(void *self) {
    char *mover = *(char **)self;
    char *state = *(char **)((char *)self + 4);
    int accum = *(int *)(state + 0x64) + *(int *)(mover + 0x2c);
    *(int *)(state + 0x64) = accum;

    if (accum >= 0x2a8) {
        char *target = *(char **)state;
        VecFx32 diff;
        VEC_Subtract((fx32 *)(state + 0x28), (fx32 *)(target + 0xb0), (fx32 *)&diff);

        fx32 distance = func_01ff8d18(&diff, &diff);

        target = *(char **)state;
        *(VecFx32 *)(state + 0x28) = *(VecFx32 *)(target + 0xb0);
        *(int *)(state + 0x64) = 0;

        if (distance < 0x300) {
            return 0;
        }
    }
    return 1;
}
