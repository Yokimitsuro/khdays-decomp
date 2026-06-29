typedef struct {
    int word0;
    int word4;
    int word8;
    unsigned short halfc;
    unsigned short halfe;
    int word10;
} func_0202c268_args;

extern char *data_0204c208;
extern void func_01fff7a4(void *ptr, func_0202c268_args *args);

void func_0202c268(int index, int arg1, int arg2, int arg3) {
    func_0202c268_args args;

    args.word0 = arg1;
    args.word4 = arg2;
    args.halfc = 0;
    args.halfe = 0;
    args.word10 = arg3;
    func_01fff7a4(data_0204c208 + 4 + index * 8, &args);
}
