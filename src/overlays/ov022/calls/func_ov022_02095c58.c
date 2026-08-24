struct LinkedState_02095c58 {
    unsigned char pad000[2];
    unsigned char state002;
};

struct LinkedObject_02095c58 {
    unsigned char pad000[0x14];
    struct LinkedState_02095c58 *state014;
};

struct Obj_02095c58 {
    unsigned long long flags000;
    unsigned char pad008;
    unsigned char kind009;
    unsigned char pad00a[8];
    unsigned short hp012;
    unsigned char pad014[2];
    unsigned short maxHp016;
    unsigned char pad018[0xd80 - 0x18];
    struct LinkedObject_02095c58 *linkedD80;
};

extern void func_ov002_0206cd60(int a, int b);
extern int func_020358f4(int kind, int b);
extern void func_ov022_020acc94(struct Obj_02095c58 *obj, int v);
extern unsigned char data_0204c240;

void func_ov022_02095c58(struct Obj_02095c58 *obj) {
    struct LinkedObject_02095c58 *p = obj->linkedD80;
    unsigned long long f;
    int maxHp, prod;
    unsigned short hp;
    if (p != 0 && p->state014->state002 == 2) return;
    f = obj->flags000;
    if ((f & 0x400000LL) != 0) return;
    if ((*(unsigned char *)&data_0204c240 & 4) == 0) {
        if (((unsigned int)f & 0x10000) == 0 && obj->kind009 == 0)
            func_ov002_0206cd60(1, 2);
    }
    if (func_020358f4(obj->kind009, 0x34) == 0) return;
    maxHp = obj->maxHp016;
    hp = obj->hp012;
    prod = maxHp * 0xcd;
    if (hp > (prod >> 12)) func_ov022_020acc94(obj, hp - (prod >> 12));
    else func_ov022_020acc94(obj, 1);
}
