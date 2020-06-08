#include "Enemy_FinalBoss1.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"

Enemy_FinalBoss1::Enemy_FinalBoss1(int x, int y, int _pattern) :Enemy(x, y, _pattern)
{
	//Animation
	FirsAnim.PushBack({ 7,10,261,160 });
	currentAnim = &FirsAnim;
	FirsAnim.speed = 0.1;

	ShootBack.PushBack({7,178,261,160});
	ShootBack.PushBack({ 7,346,261,160 });
	ShootBack.PushBack({ 7,513,261,160 });
	ShootBack.loop = true;
	ShootBack.speed = 0.5;
	//currentAnim = &ShootBack;

	ShootBombs.PushBack({ 285,10,261,160 });
	ShootBombs.PushBack({ 285,178,261,160 });
	ShootBombs.PushBack({ 285,346,261,160 });
	ShootBombs.PushBack({ 285,513,261,160 });
	ShootBombs.PushBack({ 285,178,261,160 });
	ShootBombs.PushBack({ 285,10,261,160 });
	ShootBombs.loop = false;
	ShootBombs.speed = 0.08;
	//currentAnim = &ShootBombs;

	Hit.PushBack({562,513,261,160});
	Hit.loop = false;
	Hit.speed = 0.1;

	collider = App->collisions->AddCollider({ 0, 0, 261, 60 }, Collider::Type::ENEMY, (Module*)App->enemies);

	position.x -= SCREEN_WIDTH+280;
	//App->audio->PlayMusic("Assets/Boss 1.ogg", 6);
}


void Enemy_FinalBoss1::Update() {
	move();
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Draw();
}
void Enemy_FinalBoss1::OnCollision(Collider* collider){
	//App->particles->AddParticle(App->particles->explosion, position.x, position.y);
	SetToDelete();
	App->level1->Win();
	isDead = true;
}


void Enemy_FinalBoss1::move() {

	float vecX[4] = { 0.75 ,SCREEN_SPEED ,1.25 ,SCREEN_SPEED };
	float vecY[4] = { 0.55, 0, -0.55, 0 };
	if (collider->pendingToDelete != true){
	collider->SetPos(position.x, position.y + ((*currentAnim).GetCurrentFrame().h / 3) - (collider->rect.h / 3));
}
	switch (pattern) {
	case 0:
		if (xRecorrido < SCREEN_WIDTH + 90)
		{
			xRecorrido += 1;
			position.y -= 0.15f;
			position.x += 1.8f;
		}
		else pattern = 1;
		break;

	case 1:
		//Quedarse quieto un momento
		if (xRecorrido < SCREEN_WIDTH + 115)
		{
			xRecorrido += SCREEN_SPEED;
			position.y = position.y;
			position.x += SCREEN_SPEED;
		}
		else pattern = 2;
		break;
	case 2:
		if (xRecorrido < SCREEN_WIDTH + 360)
		{
			xRecorrido += 1;
			position.y -= 0.55;
			position.x += 0.75;
		}
		else pattern = 3, xRecorrido = 0;
		break;
	case 3:
		//Quedarse quieto un momento
		if (xRecorrido < 25)
		{
			xRecorrido += SCREEN_SPEED;
			position.y = position.y;
			position.x += SCREEN_SPEED;
		}
		else
		{
			xRecorrido = 0;
			if (change == false)pattern = 4;
			else pattern = 5;
		}
		break;
	case 4:		
		if (xRecorrido < 190)
		{
			xRecorrido += 1;
			position.y += 0.55;
			position.x += 0.75;
		}
		else xRecorrido = 0, change = true, pattern = 3;
		break;
	case 5:
		if (xRecorrido < 190)
		{
			xRecorrido += 1;
			position.y -= 0.55;
			position.x += 1.25;
		}
		else xRecorrido = 0, change=false,pattern = 3;
		break;
	}
}