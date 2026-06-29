typedef struct {
    int word0;
    int word4;
    int word8;
    unsigned short halfc;
    unsigned short halfe;
    int word10;
} func_0202c33c_args;

extern char *data_0204c208;
extern void func_01fff83c(void *ptr, func_0202c33c_args *args);

void func_0202c33c(int index, int arg1, int arg2, int arg3) {
    func_0202c33c_args args;

    args.word0 = arg1;
    args.word4 = arg2;
    args.word8 = arg3;
    args.halfc = 1;
    func_01fff83c(data_0204c208 + 4 + index * 8, &args);
}
