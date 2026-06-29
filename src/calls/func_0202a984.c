extern void func_0202ea48(void *dst, void *ptr);
extern void func_0202f4a4(void *dst, void *src);
extern void func_0202ef54(void *dst, void *src, void *arg);
extern void func_0202ec2c(void *ptr, void *src);
extern char data_020420d8;

void func_0202a984(void *ptr) {
    int tmp[4];

    func_0202ea48(tmp, ptr);
    func_0202f4a4(tmp, tmp);
    func_0202ef54(tmp, tmp, &data_020420d8);
    func_0202ec2c(ptr, tmp);
}
