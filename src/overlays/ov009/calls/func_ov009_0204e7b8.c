typedef int (*Unk02051458Callback)(int arg0);

typedef struct {
    void *object;
    int unused;
} Unk02051458Entry;

extern int data_ov009_020563ec[];
extern Unk02051458Entry data_ov009_020562d4[];

int func_ov009_0204e7b8(int arg0)
{
    int result = 1;
    int index = data_ov009_020563ec[1];

    if (index != -1) {
        result = (*(Unk02051458Callback *)data_ov009_020562d4[index].object)(arg0);
    }

    return result;
}
