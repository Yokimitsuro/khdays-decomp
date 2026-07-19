typedef struct { int x, y, z; } Vec3;

/* Records the requested move: phase 2, the two parameters, and the target vector (passed by
 * value, which is why the caller's four argument registers get spilled on entry). */
void func_ov259_020d1bf8(int *self, int a, int b, Vec3 target) {
    *(char *)(*self + 0x1c7) = 2;
    self[0xf] = a;
    self[0x10] = b;
    *(Vec3 *)((char *)self + 0x18) = target;
}
