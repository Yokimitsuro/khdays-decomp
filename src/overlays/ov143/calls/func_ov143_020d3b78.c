/* Handle type-5 commands for this enemy, then forward every command to the common
 * handler, exactly like func_ov281_020cc440.
 *
 * Action 1 re-binds two render nodes onto the shared transform and opens effect 7;
 * action 2 re-binds a third; action 0 sweeps the scene's actor list, collecting up
 * to sixteen ids of live actors whose surface distance is within 0x8000, halving
 * their stagger timer when this enemy is in mode 1, firing reaction 0x11e at each,
 * and handing the collected list to func_ov143_020d5fec. */
typedef unsigned char u8;
typedef unsigned short u16;

struct Ov143Vec3 {
    int x;
    int y;
    int z;
};

struct Ov143Cmd {
    u8 pad00[2];
    u8 type02;
    u8 action03;
};

struct Ov143Slots {
    int field00;
    int field04;
    int field08;
    int field0c;
    char pad10[8];
    int field18;
    int field1c;
    int field20;
    int field24;
};

struct Ov143Other {
    char pad00[2];
    u16 id02;
    char pad04[0x5c];
    struct Ov143Hw60 { u16 lo : 8, hi : 8; } flags60;
    char pad62[0x12];
    struct Ov143Vec3 vPos74;
    int nRadius80;
    char pad84[0x17c];
    u16 flags200_18;
    char pad202[0x16];
    short nStaggerMax218;
    short nStagger21a;
};

struct Ov143Self {
    char pad00[4];
    int pScene04;
    char pad08[0x34];
    int nResource3c;
    char pad40[0x10];
    int nMode50;
    char pad54[0x20];
    struct Ov143Vec3 vPos74;
    int nRadius80;
    char pad84[0x30c];
    struct Ov143Slots *pSlots390;
    int *pTransform394;
    char pad398[4];
    int aTransform39c[11];
    char pad3c8[8];
    int nEffect3d0;
};

extern int func_ov107_020c09a0(int resource, int node, int kind, void *transform,
                               int flags, int enabled);
extern int func_ov107_020cb040(struct Ov143Self *self, int id, int kind, int enabled,
                               void *transform);
extern void **func_01fffd70(void *list);
extern void **func_01fffd8c(void *list);
extern void VEC_Subtract(const struct Ov143Vec3 *a, const struct Ov143Vec3 *b,
                         struct Ov143Vec3 *dst);
extern int VEC_Mag(const struct Ov143Vec3 *v);
extern void func_ov107_020c5af8(struct Ov143Self *self, int id, int kind,
                                struct Ov143Vec3 *at);
extern int func_ov143_020d5fec(struct Ov143Self *self, short *ids);
extern void func_ov107_020c7500(struct Ov143Self *self, struct Ov143Cmd *cmd, int arg2);

void func_ov143_020d3b78(struct Ov143Self *self, struct Ov143Cmd *cmd, int arg2)
{
    struct Ov143Other *other;
    void **it;
    int count;
    int n;
    int cap;

    if (cmd->type02 == 5) {
        switch (cmd->action03) {
        case 1:
            self->pSlots390->field0c =
                func_ov107_020c09a0(self->nResource3c, self->pSlots390->field08,
                                    0x17, self->pTransform394 + 1, 0, 0);
            self->pSlots390->field1c =
                func_ov107_020c09a0(self->nResource3c, self->pSlots390->field18,
                                    0x17, self->aTransform39c, 0, 0);
            self->nEffect3d0 =
                func_ov107_020cb040(self, 0x11e, 5, 0,
                                    self->pTransform394 + 1);
            break;
        case 2:
            self->pSlots390->field24 =
                func_ov107_020c09a0(self->nResource3c, self->pSlots390->field20,
                                    0x17, self->pTransform394 + 1, 0, 0);
            break;
        case 0: {
            int list = self->pScene04;
            short ids[16] = {0};
            struct Ov143Vec3 delta;

            count = 0;
            it = func_01fffd70((void *)(list + 0x80));
            other = (it == 0) ? 0 : (struct Ov143Other *)*it;
            while (other != 0) {
                if ((other->flags60.lo & 1) != 0
                    && (*(u16 *)((char *)other + 0x1ac) & 4) == 0) {
                    VEC_Subtract(&other->vPos74, &self->vPos74, &delta);
                    if (VEC_Mag(&delta) - (other->nRadius80 + self->nRadius80)
                        <= 0x8000) {
                        ids[count++] = other->id02;
                        if (self->nMode50 == 1) {
                            cap = other->nStaggerMax218;
                            n = other->nStagger21a + cap / 2;
                            if (n < 0) {
                                cap = 0;
                            } else if (n <= cap) {
                                cap = n;
                            }
                            other->nStagger21a = (short)cap;
                            func_ov107_020c5af8(self, 0x11e, 6, &other->vPos74);
                        }
                        if (count >= 0x10) {
                            break;
                        }
                    }
                }
                it = func_01fffd8c((void *)(list + 0x80));
                other = (it == 0) ? 0 : (struct Ov143Other *)*it;
            }
            self->pSlots390->field04 = func_ov143_020d5fec(self, ids);
            break;
        }
        }
    }

    func_ov107_020c7500(self, cmd, arg2);
}
