typedef int (*Unk0205137cCallback)(int arg0);

typedef struct {
    void *object;
    int unused;
} Unk0205137cEntry;

extern int data_ov008_02090f0c[];
extern Unk0205137cEntry data_ov008_0209009c[];

int func_ov008_0205137c(int arg0)
{
    int result = 1;
    int index = data_ov008_02090f0c[0];

    if (index != -1) {
        result = (*(Unk0205137cCallback *)data_ov008_0209009c[index].object)(arg0);
    }

    return result;
}
