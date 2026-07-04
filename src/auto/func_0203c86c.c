struct flags_5c { int b0:1; int b1:1; };

void func_0203c86c(int this_, int arg1) {
    if (((struct flags_5c *)(this_ + 0x5c))->b1) {
        return;
    }
    {
        void (*cb6c)(int, int) = *(void (**)(int, int))(this_ + 0x6c);
        if (cb6c != 0) {
            cb6c(this_, arg1);
        }
    }
    {
        void (*cb74)(int, int) = *(void (**)(int, int))(this_ + 0x74);
        if (cb74 == 0) {
            return;
        }
        cb74(this_, *(int *)(this_ + 0x84));
    }
}
