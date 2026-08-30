/* Downward ray intersection with the flat upper cylinder cap.
 * The hardware divider is drained on every path after the asynchronous start. */
typedef signed int s32;
typedef unsigned int u32;
typedef signed long long s64;
typedef unsigned long long u64;
typedef unsigned short u16;
typedef unsigned char u8;
typedef struct VecFx32 { s32 x,y,z; } VecFx32;
typedef struct CollisionObject { u8 pad00[0x2c]; VecFx32 position2c; s32 radius38,height3c; } CollisionObject;
typedef struct CollCastState {
 u8 pad00[0x10]; VecFx32 vRayStart,vDir;
 u8 pad28[0x54-0x28]; VecFx32 vRayEnd;
 u8 pad60[0x74-0x60]; s32 nRadius,nNearestHit;
} CollCastState;
extern s64 func_01ff8ab0(void);
extern void func_01ffd0e8(s32,const VecFx32*,const VecFx32*,VecFx32*);
#define MUL(a,b) ((s32)(((s64)(a)*(b)+0x800)>>12))
static inline void WaitDivider(void) { while(*(volatile u16*)0x04000280&0x8000) {} }
static inline void StartDivide(s32 numerator,s32 denominator) {
 *(u64*)0x04000290=(u64)(u32)numerator<<32;
 *(u64*)0x04000298=(u32)denominator;
}
s32 func_01fff0e0(CollisionObject *object,CollCastState *query)
{
 VecFx32 hitPoint;
 s32 startY,endY,top,distance,denominator,fraction,dx,dz,radius;
 startY=query->vRayStart.y;
 endY=query->vRayEnd.y;
 top=object->position2c.y+object->height3c;
 if(startY<=endY) return -4096;
 distance=startY-top;
 if(distance < -128) return -4096;
 if(endY-top > 128) return -4096;
 denominator=startY-endY;
 StartDivide(distance,denominator);
 if(distance>=(s32)(((s64)query->nNearestHit*denominator)>>27)) { WaitDivider(); return -4096; }
 if(distance<0) {
  hitPoint=query->vRayStart;
  fraction=0;
  WaitDivider();
 } else if(distance>=denominator) {
  hitPoint=query->vRayEnd;
  fraction=1<<27;
  WaitDivider();
 } else {
  fraction=(s32)(func_01ff8ab0()>>5);
  func_01ffd0e8(fraction,&query->vDir,&query->vRayStart,&hitPoint);
 }
 dz=hitPoint.z-object->position2c.z;
 dx=hitPoint.x-object->position2c.x;
 radius=object->radius38;
 if(MUL(dx,dx)+MUL(dz,dz)>MUL(radius,radius)) return -4096;
 query->nNearestHit=fraction;
 return fraction;
}
