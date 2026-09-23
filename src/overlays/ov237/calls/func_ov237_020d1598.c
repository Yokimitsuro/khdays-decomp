/* Emit one ov237 particle from a ring emitter: the next record (0x38 bytes) of the owner's +0x90 ring
 * takes kind 0x10, the position and the given +0x1c value (+0x18 / +0x20 cleared), the owner's +0x5c
 * bit 1 is cleared and the cursor advances modulo the +0x8c ring size. */
typedef struct { int x, y, z; } Vec3;
typedef struct { int kind; char pad4[0x14]; int a; int value; int c; char pad24[8]; Vec3 pos; } Particle;
typedef struct { char *owner; int next; } Emitter;

extern int func_02023eb4(int bound);

void func_ov237_020d1598(Emitter *emitter, Vec3 *pos, int value)
{
    Particle *p;

    func_02023eb4(10);
    p = (Particle *)(*(int *)(emitter->owner + 0x90) + emitter->next * 0x38);
    *(int *)(emitter->owner + 0x5c) &= ~2;
    p->kind = 0x10;
    p->pos = *pos;
    p->a = 0;
    p->value = value;
    p->c = 0;
    emitter->next = (emitter->next + 1) % *(int *)(emitter->owner + 0x8c);
}
