/* Initialize the result-screen resource tracker and load archive member 3. */
typedef unsigned int u32;
typedef int (*ResourceCallback)(int);
typedef struct Ov000ResourceTrackerConfig {u32 entryCapacity,nodeCapacity,auxiliaryCapacity;ResourceCallback entryCallback,nodeCallback;} Ov000ResourceTrackerConfig;
typedef struct Ov000ResourceTracker {char data[76];} Ov000ResourceTracker;
typedef struct Ov005ResultContext {u32 resultArchive;char pad4[4];Ov000ResourceTracker resourceTracker;} Ov005ResultContext;
extern Ov005ResultContext *data_ov005_0205b810;
extern int func_ov005_02056fb0(int);
extern int func_ov005_02056fc0(int);
extern void func_ov005_0204d098(Ov000ResourceTracker *,Ov000ResourceTrackerConfig *);
extern void func_ov005_0204d160(Ov000ResourceTracker *,u32);
void func_ov005_0205660c(void) {
    Ov000ResourceTrackerConfig config;
    Ov005ResultContext *context=data_ov005_0205b810;
    config.entryCapacity=57;
    config.nodeCapacity=1;
    config.auxiliaryCapacity=26;
    config.entryCallback=func_ov005_02056fb0;
    config.nodeCallback=func_ov005_02056fc0;
    func_ov005_0204d098(&context->resourceTracker,&config);
    func_ov005_0204d160(&context->resourceTracker,(((data_ov005_0205b810->resultArchive+0x8000)&0xfffffc)<<7)|0x80000003);
}
