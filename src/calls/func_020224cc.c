extern int func_02021980(void *a, void *b);
extern int func_0203355c(int x);

int func_020224cc(void *p, char *buf)
{
    int saved;
    saved = func_02021980(p, buf);
    func_02021980(p, buf + 8);
    func_0203355c(saved);
    return 1;
}
