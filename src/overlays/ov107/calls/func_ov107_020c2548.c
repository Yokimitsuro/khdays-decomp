typedef unsigned short u16;
typedef unsigned char u8;

typedef struct Node2 {
    struct Node2 *prev;
    struct Node2 *next;
    int key;
    void *data;
} Node2;

typedef struct GameObj {
    u16 flags;
    char pad2[0x44 - 2];
    void (*onAttach)(struct GameObj *self);
    void (*onTrigger)(struct GameObj *self, void *param1);
    void (*onPair)(struct GameObj *a, struct GameObj *b);
    char pad50[0x60 - 0x50];
    u16 flags60;
} GameObj;

extern void *func_01fffd70(int list);
extern void *func_01fffd8c(int list);
extern unsigned int func_02030788(void);
extern void func_ov107_020c2c94(void *self, void *param1);
extern void func_0203c7ac(int *ptr, int arg);

void func_ov107_020c2548(char *self, void *param1) {
    void *node;
    Node2 *outer, *inner;

    node = func_01fffd70((int)(self + 0x44));
    if (node != 0) {
        do {
            GameObj *obj = *(GameObj **)node;
            if (obj->flags & 0x20) {
                if (obj->onAttach) obj->onAttach(obj);
            }
            node = func_01fffd8c((int)(self + 0x44));
        } while (node != 0);
    }

    if (func_02030788() == 0) {
        for (outer = *(Node2 **)(self + 0x48);
             outer != (Node2 *)(self + 0x54) && outer->next != (Node2 *)(self + 0x54);
             outer = outer->next) {
            GameObj *a = *(GameObj **)outer->data;
            if (a->flags & 0x20) {
                unsigned int aByte = (unsigned int)(a->flags60 << 24) >> 24;
                if ((aByte & 1) && !(aByte & 2)) {
                    for (inner = outer->next; inner != (Node2 *)(self + 0x54); inner = inner->next) {
                        GameObj *b = *(GameObj **)inner->data;
                        if (b->flags & 0x20) {
                            unsigned int bByte = (unsigned int)(b->flags60 << 24) >> 24;
                            if ((bByte & 1) && !(bByte & 2)) {
                                if (!(a->flags & 0x80) || !(b->flags & 0x80)) {
                                    if (a->onPair) a->onPair(a, b);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    if (func_02030788() == 0) {
        node = func_01fffd70((int)(self + 0x44));
        if (node != 0) {
            do {
                GameObj *obj = *(GameObj **)node;
                if (obj->flags & 0x20) {
                    unsigned int byte = (unsigned int)(obj->flags60 << 24) >> 24;
                    if (byte & 1) {
                        if (obj->onTrigger) obj->onTrigger(obj, param1);
                    }
                }
                node = func_01fffd8c((int)(self + 0x44));
            } while (node != 0);
        }
    }

    func_ov107_020c2c94(self, param1);
    func_0203c7ac(*(int **)(self + 0x104), (int)param1);
}
