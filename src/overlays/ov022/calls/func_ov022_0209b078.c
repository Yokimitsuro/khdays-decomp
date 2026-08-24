extern void func_0202accc(void *arg0, unsigned short arg1, void *arg2, short arg3);

struct Ov022AnimSlot {
    unsigned char anim[0xe0];
    unsigned char block[0x28];
};

struct Ov022BattleState {
    unsigned char _pad0000[0x278c];
    struct Ov022AnimSlot slots[3];
};

void func_ov022_0209b078(struct Ov022BattleState *arg0, int arg1, int arg2)
{
    unsigned int i;
    struct Ov022AnimSlot *e;

    e = &arg0->slots[arg1];

    for (i = 0; (int)i < 5; i++) {
        func_0202accc(e->anim, i, e->block, arg2);
    }
}
