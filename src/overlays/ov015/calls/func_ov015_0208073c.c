/* func_ov015_0208073c -- push a 3-word transform through the node's matrix slots, ov015.
 * Copies src into the work slot (@+0x30), then work into the live slot (@+0x1c). */
struct Vec3 { int x, y, z; };
void func_ov015_0208073c(char *node, struct Vec3 *src) {
    *(struct Vec3 *)(node + 0x30) = *src;
    *(struct Vec3 *)(node + 0x1c) = *(struct Vec3 *)(node + 0x30);
}
