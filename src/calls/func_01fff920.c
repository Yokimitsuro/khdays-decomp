typedef struct {
    int word0;
    int word4;
    int word8;
    unsigned short halfc;
    unsigned short halfe;
    int word10;
} func_01fff920_args;

extern void func_01fff7a4(int arg0, func_01fff920_args *args);

void func_01fff920(int arg0, int arg1, int arg2) {
    func_01fff920_args args;

    args.word0 = arg1;
    args.word4 = arg2;
    args.halfc = 1;
    func_01fff7a4(arg0, &args);
}
