typedef int (*Unk02051458Callback)(int arg0);

typedef struct {
    void *object;
    int unused;
} Unk02051458Entry;

extern int data_ov025_020b574c[];
extern Unk02051458Entry data_ov025_020b4a78[];

int func_ov025_02085208(int arg0)
{
    int result = 1;
    int index = data_ov025_020b574c[1];

    if (index != -1) {
        result = (*(Unk02051458Callback *)data_ov025_020b4a78[index].object)(arg0);
    }

    return result;
}
