/*
 * func_ov229_020d61d4 -- x3 (ov228/...). Seed the local offset vector, then publish it to the owner.
 * state = self[1]. If the mode byte *(s8)(*state + 0x1c6) == 0, reset the local vec state[2..4] to the
 * const data_02041dc8. Then copy state[2..4] into the owner block at *state + 0xf0.
 */
struct vec3 { int x, y, z; };
extern struct vec3 data_02041dc8;

void func_ov229_020d61d4(int *self) {
    int *state = (int *)self[1];

    if (*(signed char *)(*state + 0x1c6) == 0) {
        *(struct vec3 *)(state + 2) = data_02041dc8;
    }
    *(struct vec3 *)(*state + 0xf0) = *(struct vec3 *)(state + 2);
}
