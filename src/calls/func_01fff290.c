/* Sphere sweep against the shared cylindrical object bounds.
 * Keep per-product Q12 rounding and separate wide-offset lifetimes.
 * Common-expression folding otherwise promotes direction squares to wide multiplies. */
#pragma opt_common_subs off
typedef signed int s32;
typedef signed long long s64;
typedef unsigned char u8;
typedef struct VecFx32 { s32 x,y,z; } VecFx32;
typedef struct CollisionObject {
 u8 pad00[0x2c]; VecFx32 position2c; s32 radius38,height3c;
} CollisionObject;
typedef struct CollCastState {
 u8 pad00[0x10]; VecFx32 vRayStart,vDir;
 u8 pad28[0x54-0x28]; VecFx32 vRayEnd;
 u8 pad60[0x74-0x60]; s32 nRadius,nNearestHit;
} CollCastState;
extern s32 FX_Sqrt(s32);
extern s64 func_01ff8a14(s32,s32);
#define MUL(a,b) ((s32)(((s64)(a)*(b)+0x800)>>12))
s32 func_01fff290(CollisionObject *object,CollCastState *query)
{
 s32 startY,bottom,endY,height,top,dirX,dirZ,fraction;
 bottom=object->position2c.y;
 startY=query->vRayStart.y;
 endY=query->vRayEnd.y;
 if(bottom>startY && bottom>endY) return -4096;
 height=object->height3c;
 top=bottom+height;
 if(top<startY && top<endY) return -4096;
 dirZ=query->vDir.z;
 dirX=query->vDir.x;
 if(dirX|dirZ) {
  s64 dx,dz;
  s32 dot,distance2,radius,radius2,speed2,discriminant,numerator,hitY;
  dx=query->vRayStart.x-object->position2c.x;
  dz=query->vRayStart.z-object->position2c.z;
  dot=MUL((s32)dx,dirX)+MUL((s32)dz,dirZ);
  fraction=0;
  if(dot>=-4) return -4096;
  distance2=MUL(dx,dx)+MUL(dz,dz);
  radius=object->radius38+query->nRadius;
  radius2=MUL(radius,radius);
  if(distance2>radius2) {
   speed2=MUL(dirX,dirX)+MUL(dirZ,dirZ);
   discriminant=MUL(dot,dot)-MUL(speed2,distance2-radius2);
   if(discriminant<0) return -4096;
   numerator=-(dot+FX_Sqrt(discriminant));
   if(numerator<0) return -4096;
   if(numerator>speed2) return -4096;
   fraction=(s32)(func_01ff8a14(numerator,speed2)>>5);
  }
  if(fraction>=query->nNearestHit) return -4096;
  startY=query->vRayStart.y;
  hitY=startY+(s32)(((s64)fraction*query->vDir.y)>>27);
  bottom=object->position2c.y;
  if(hitY<bottom || hitY>bottom+object->height3c) return -4096;
 } else {
  s32 dx,dz,distance2,radius;
  dz=query->vRayStart.z-object->position2c.z;
  dx=query->vRayStart.x-object->position2c.x;
  distance2=MUL(dx,dx)+MUL(dz,dz);
  radius=object->radius38+query->nRadius;
  fraction=0;
  if(distance2<=MUL(radius,radius)) {
   if(query->nNearestHit<=0) return -4096;
   if(startY<bottom || startY>bottom+height) return -4096;
  } else return -4096;
 }
 query->nNearestHit=fraction;
 return fraction;
}
