typedef struct Actor Actor;

extern int func_ov107_020c0770(int id, int cnt);
extern int func_ov107_020c0680(int id, int cnt, void *slot);
extern int func_ov107_020c2f94(int id, void *slot);
extern void OS_Terminate(void);

typedef struct { char raw[0x2c]; } Slot44;
typedef struct { char raw[0x6a]; } Slot106;

extern unsigned char data_ov107_020cbb20[];
extern int data_ov107_020cbb04;
extern Slot44 data_ov107_020cbb98[];
extern Slot106 data_ov107_020cbca0[];
extern Actor *(*data_ov107_020cbb08[])(void *);

Actor *func_ov107_020c2ea8(int id)
{
    unsigned char state = data_ov107_020cbb20[id];

    if (state != 0) {
        goto dispatch;
    }

    {
        int cnt = data_ov107_020cbb04;
        int found = 0;

        while (cnt < 6) {
            if (func_ov107_020c0770(id, cnt) != 0) {
                found = 1;
                break;
            }
            cnt = ++data_ov107_020cbb04;
        }

        if (!found) {
            goto terminate;
        }

        cnt = data_ov107_020cbb04;
        data_ov107_020cbb20[id] = (unsigned char)(cnt + 1);
        {
            int delta = func_ov107_020c0680(id, cnt, &data_ov107_020cbb98[cnt]);
            func_ov107_020c2f94(id, &data_ov107_020cbca0[data_ov107_020cbb04]);
            data_ov107_020cbb04 += delta;
        }
    }
    goto dispatch;

terminate:
    OS_Terminate();
    return 0;

dispatch:
    state = data_ov107_020cbb20[id];
    {
        int idx = state - 1;
        return data_ov107_020cbb08[idx](&data_ov107_020cbca0[idx]);
    }
}
