/* Ground-probe helper of the ov156 enemy (and its byte-identical twins): takes the pool's node position
 * (+0x14 of +0x398) raised by 0x200, hands it back through `out`, casts a 0x3000 ray straight
 * down from it through the actor's +0x7c collision world and, on a hit, moves the point onto
 * the surface (the hit's +0xc fraction of the ray, plus 0x200); the result is pushed to the
 * render hook (cmd 2) and effect 0x13d (7) is spawned at the node position. */
typedef struct { int x, y, z; } Vec3;

extern void *func_01fff888(void *world, Vec3 *from, Vec3 *ray, void *arg);   /* Collision_CastRayEx */
extern void func_01ffd144(int scale, Vec3 *in, Vec3 *out);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_ov107_020c0b90(int obj, int cmd, Vec3 v, int flag);
extern void func_ov107_020c5af8(int obj, int effect, int kind, void *pos);

void func_ov156_020cc9c4(int *node, Vec3 *out)
{
    Vec3 at;
    Vec3 ray;
    int actor = *(int *)(*node + 4);
    void *hit;

    at = *(Vec3 *)(*(int *)(*node + 0x398) + 0x14);
    at.y += 0x200;
    *out = at;
    ray.x = 0;
    ray.y = -0x3000;
    ray.z = 0;
    hit = func_01fff888(*(void **)(actor + 0x7c), &at, &ray, 0);
    if (hit != 0) {
        func_01ffd144(*(int *)((char *)hit + 0xc), &ray, &ray);
        ray.y += 0x200;
        VEC_Add(&at, &ray, &at);
    }
    func_ov107_020c0b90(*node, 2, at, 0);
    func_ov107_020c5af8(*node, 0x13d, 7, (void *)(*(int *)(*node + 0x398) + 0x14));
}
