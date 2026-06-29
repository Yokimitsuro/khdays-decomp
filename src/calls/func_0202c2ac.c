typedef struct {
    int word0;
    int word4;
    int word8;
    unsigned short halfc;
    unsigned short halfe;
    int word10;
} func_0202c2ac_args;

extern char *data_0204c208;
extern void func_01fff83c(void *ptr, func_0202c2ac_args *args);

void func_0202c2ac(int index, int arg1, int arg2, int arg3, int arg4) {
    func_0202c2ac_args args;

    args.word0 = arg1;
    args.word4 = arg2;
    args.word8 = arg3;
    args.halfc = 0;
    args.halfe = 0;
    args.word10 = arg4;
    func_01fff83c(data_0204c208 + 4 + index * 8, &args);
}
