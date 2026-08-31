typedef struct Tween {
    int mode,duration,from,to;
    long long startTick;
    unsigned int flags;
} Tween;
typedef struct Ov005Context { char opaque00[0x4c70]; Tween statusTween; } Ov005Context;
extern Ov005Context *data_ov005_0205b80c;
extern void func_02035fb0(Tween *,int,int,int,int);
extern void func_02035ffc(Tween *);
void func_ov005_020538ec(int step) {
    int from,duration,to;
    switch(step) {
    case 1: from=115;to=115;duration=1000;break;
    case 2: from=115;to=0;duration=200;break;
    case 3: from=0;to=0;duration=2000;break;
    case 4: from=0;to=-115;duration=200;break;
    case 0:default:return;
    }
    func_02035fb0(&data_ov005_0205b80c->statusTween,0,from*4096,to*4096,duration);
    func_02035ffc(&data_ov005_0205b80c->statusTween);
}
