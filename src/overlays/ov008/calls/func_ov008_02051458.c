typedef int (*Unk02051458Callback)(int arg0);

typedef struct {
    void *object;
    int unused;
} Unk02051458Entry;

extern int data_ov008_02090f0c[];
extern Unk02051458Entry data_ov008_02090064[];

int func_ov008_02051458(int arg0)
{
    int result = 1;
    int index = data_ov008_02090f0c[1];

    if (index != -1) {
        result = (*(Unk02051458Callback *)data_ov008_02090064[index].object)(arg0);
    }

    return result;
}
