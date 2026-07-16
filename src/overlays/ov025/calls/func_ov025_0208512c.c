typedef int (*Unk0205137cCallback)(int arg0);

typedef struct {
    void *object;
    int unused;
} Unk0205137cEntry;

extern int data_ov025_020b574c[];
extern Unk0205137cEntry data_ov025_020b4ab0[];

int func_ov025_0208512c(int arg0)
{
    int result = 1;
    int index = data_ov025_020b574c[0];

    if (index != -1) {
        result = (*(Unk0205137cCallback *)data_ov025_020b4ab0[index].object)(arg0);
    }

    return result;
}
