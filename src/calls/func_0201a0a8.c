extern void *NNS_FndGetNextListObject(void *list, void *prev);
extern char data_0204a314[];

typedef struct Obj {
    char pad[0x34];
    unsigned short kind;
    unsigned short field_36;
    unsigned short player;
} Obj;

int func_0201a0a8(int player_id) {
    int count = 0;
    Obj *p = (Obj *)NNS_FndGetNextListObject(data_0204a314, 0);
    while (p != 0) {
        if (p->kind == 1 && p->player == player_id) count++;
        p = (Obj *)NNS_FndGetNextListObject(data_0204a314, p);
    }
    return count;
}
