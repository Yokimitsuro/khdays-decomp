typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Ov022Candidate {
    u16 field00;
    u16 outputId02;
    u8 pad04[0x228];
    u8 list22c[4];
} Ov022Candidate;

typedef struct Ov022Actor {
    u8 pad00[9];
    u8 slot09;
} Ov022Actor;

typedef struct Ov022SelectionResult {
    u32 selectionFlags00;
    int type04;
    Ov022Candidate *candidate08;
    void *comparison0c;
    u32 field10;
    void *source14;
    Ov022Actor *actor18;
    int scanDistance1c;
    int selectedIndex20;
    int selectedValue24;
} Ov022SelectionResult;

extern void *func_01fffd70(void *list);
extern void *func_01fffd8c(void *list);
extern void func_ov002_02076770(void *source, u8 *output,
                                u16 *resolvedValue);

void func_ov022_02086748(u8 *output, Ov022SelectionResult *selection)
{
    int index;
    Ov022Candidate *candidate;
    void *node;
    u16 resolvedValue;

    switch (selection->type04) {
    case 0:
        output[0] = 0;
        output[1] = 0;
        output[2] = 0;
        return;

    case 1:
        output[0] = 1;
        index = 0;
        output[1] = (u8)selection->candidate08->outputId02;
        candidate = selection->candidate08;
        node = func_01fffd70(candidate->list22c);
        if (node == 0) {
            return;
        }
        do {
            if (node == selection->comparison0c) {
                output[2] = index;
                return;
            }
            index++;
            node = func_01fffd8c(candidate->list22c);
        } while (node != 0);
        return;

    case 2:
        output[0] = 2;
        func_ov002_02076770(selection->source14, &output[2],
                            &resolvedValue);
        output[1] = (u8)resolvedValue;
        return;

    case 3:
        output[0] = 3;
        output[1] = selection->actor18->slot09;
        return;
    }
}
