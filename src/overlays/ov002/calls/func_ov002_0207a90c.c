extern int func_ov002_0207285c(int slot);
extern void func_01fffe14(void);
extern char *func_01fffde0(void);
extern int func_01ff8e94(void *a, void *b);

typedef struct { int x, y, z; } Ov002Vec3;

/* True when the player is within this actor's trigger radius and belongs to the same model. */
int func_ov002_0207a90c(char *self) {
    char *player;
    int id;
    Ov002Vec3 pos;
    func_01fffe14();
    player = func_01fffde0();
    if (player == 0) {
        return 0;
    }
    id = *(short *)(player + 0x66);
    if (id != func_ov002_0207285c((unsigned char)self[0x10])) {
        return 0;
    }
    pos = *(Ov002Vec3 *)(player + 0x48c);
    return *(int *)(self + 0x44) >= func_01ff8e94(self + 0x1c, &pos);
}
