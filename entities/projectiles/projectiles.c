#include "projectiles.h"
#include "raylib.h"
#include "raymath.h"
#include "stdio.h"  

void Init_ProjectileSystem(ProjectileSystem *sys){
    sys->count = 0;
}

Projectile* instantiate_projectile(ProjectileSystem* sys,Vector2 pos){
    if(sys->count >= MAX_PROJECTILES)return NULL;
    Projectile p;
    p.pos = pos;
    sys->projectiles[sys->count++] = p;
    return &sys->projectiles[sys->count];
    
}

bool bullet_hit( Capsule circle, Rectangle rect){
    return CheckCollisionCircleRec(circle.center,circle.radius,rect);
}

void move_projectile(Projectile* p, Vector2 normalized_pos){
    Vector2Add(p->pos,normalized_pos);
}

bool laser_hit(Laser laser, Vector2 target_pos){
    float dist = Vector2Distance(target_pos,laser.init_pos);
        if(dist <= laser.max_range){
            return true;
        }
}


void Projectile_Draw(ProjectileSystem* sys){
    if(!sys)return;

    for (int i = 0; i < sys->count; i++)
    {
        Projectile *p = &sys->projectiles[i];
        DrawCircle(p->pos.x,p->pos.y,16.f,BLACK);
    }
    
}