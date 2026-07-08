typedef struct Vec3 {
    int x;
    int y;
    int z;
} Vec3;

extern void func_01ffa724(int factor, void *src, void *dst);
extern void func_0203c634(void *node, int idx, void *value);

void func_ov220_020d3404(int node)
{
    int *state = *(int **)(node + 4);

    *(Vec3 *)((int)state + 0x24) = *(Vec3 *)((int)state + 0x30);
    func_01ffa724(0xb00, (void *)((int)state + 0x30), (void *)((int)state + 0x30));
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }

    *(signed char *)(*state + 0x1c7) = 9;
    func_0203c634((void *)node, *(signed char *)(node + 0x20), 0);
}
