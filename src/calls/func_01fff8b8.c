typedef struct {
    int word0;
    int word4;
    int word8;
    unsigned short halfc;
    unsigned short halfe;
    int word10;
} func_01fff8b8_args;

extern void func_01fff7f0(int arg0, func_01fff8b8_args *args);

void func_01fff8b8(int arg0, int arg1, int arg2, int arg3) {
    func_01fff8b8_args args;

    args.word0 = arg1;
    args.word4 = arg2;
    args.halfc = 0;
    args.halfe = 0;
    args.word10 = arg3;
    func_01fff7f0(arg0, &args);
}
