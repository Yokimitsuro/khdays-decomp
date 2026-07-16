/* func_ov025_0208e184 -- recompute the ov008 cursor's derived positions, ov008.
 * Copies the live cursor (obj+0x18/1c/20) into the shadow slot (obj+0x24/28/2c) with fixed
 * y/z biases (+0x1000, +0x28000), then stores at obj+0x424..: the reciprocals (FX_Inv, k=0x14cd)
 * of the shadow x and y, and the shadow z minus 0x64000. */
extern int FX_Inv(int x, int k);

struct vec3 { int x, y, z; };

void func_ov025_0208e184(int obj) {
    struct vec3 proj;
    *(int *)(obj + 0x24) = *(int *)(obj + 0x18);
    *(int *)(obj + 0x28) = *(int *)(obj + 0x1c) + 0x1000;
    *(int *)(obj + 0x2c) = *(int *)(obj + 0x20) + 0x28000;
    proj.x = FX_Inv(*(int *)(obj + 0x24), 0x14cd);
    proj.y = FX_Inv(*(int *)(obj + 0x28), 0x14cd);
    proj.z = *(int *)(obj + 0x2c) - 0x64000;
    *(struct vec3 *)(obj + 0x424) = proj;
}
