typedef struct {
    int word0;
    int word4;
    int word8;
    unsigned short halfc;
    unsigned short halfe;
    int word10;
} func_01fff8e8_args;

extern void func_01fff83c(int arg0, func_01fff8e8_args *args);

void func_01fff8e8(int arg0, int arg1, int arg2, int arg3, int arg4) {
    func_01fff8e8_args args;

    args.word0 = arg1;
    args.word4 = arg2;
    args.word8 = arg3;
    args.halfc = 0;
    args.halfe = 0;
    args.word10 = arg4;
    func_01fff83c(arg0, &args);
}
