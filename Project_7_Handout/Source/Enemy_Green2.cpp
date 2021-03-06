#include "Enemy_Green2.h"

#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleCollisions.h"
#include <math.h>

Enemy_Green2::Enemy_Green2(int x, int y, int _pattern) :Enemy(x, y, _pattern)
{
	//Animation
	lives = 5;
	timerState = new Timer(60);
	timerStateCollision = new Timer(2000);
	timerAnim = new Timer(100);

	FirsAnim.PushBack({ 891,421,54,14 });
	currentAnim = &FirsAnim;

	Up.PushBack({ 1011,421,54,19});
	Up.speed = 0.08;
	Up.loop = false;

	Down.PushBack({951, 421, 54, 21});
	Down.speed = 0.08;
	Down.loop = false;

	Hit.PushBack({951,447,54,21});
	Hit.loop = false;

	collider = App->collisions->AddCollider({ 0, 0, 54, 14 }, Collider::Type::ENEMY, (Module*)App->enemies);
	if (pattern == 0)position.x += -220;
}


void Enemy_Green2::Update() {
	if (stateEnemy == status_Enemies::STATE_ENEMY_HIT)timerState->update();
	if (timerState->check()) stateEnemy = status_Enemies::STATE_ENEMY_IDLE;

	if (stateEnemy == status_Enemies::STATE_ENEMY_HIT_COLLISION)timerStateCollision->update();
	if (timerStateCollision->check()) stateEnemy = status_Enemies::STATE_ENEMY_IDLE;

	timerAnim->update();
	//if (timerAnim->check())currentAnim = &FirsAnim;
	move();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}

void Enemy_Green2::OnCollision(Collider* collider)
{
	if (collider->type == Collider::PLAYER_SHOT && stateEnemy != status_Enemies::STATE_ENEMY_HIT)lives--, stateEnemy = status_Enemies::STATE_ENEMY_HIT, currentAnim = &Hit;
	else if (collider->type == Collider::PLAYER && stateEnemy != status_Enemies::STATE_ENEMY_HIT_COLLISION)lives--, stateEnemy = status_Enemies::STATE_ENEMY_HIT_COLLISION, currentAnim = &Hit;
	if (collider->type == Collider::SW_BOMB && stateEnemy != status_Enemies::STATE_ENEMY_HIT)lives--, stateEnemy = status_Enemies::STATE_ENEMY_HIT, currentAnim = &Hit;
	if (collider->type == Collider::SW_CEILING && stateEnemy != status_Enemies::STATE_ENEMY_HIT)lives--, stateEnemy = status_Enemies::STATE_ENEMY_HIT, currentAnim = &Hit;
	if (collider->type == Collider::SW_GUNPOD && stateEnemy != status_Enemies::STATE_ENEMY_HIT)lives--, stateEnemy = status_Enemies::STATE_ENEMY_HIT, currentAnim = &Hit;
	if (collider->type == Collider::SW_S_SHELL && stateEnemy != status_Enemies::STATE_ENEMY_HIT)lives--, stateEnemy = status_Enemies::STATE_ENEMY_HIT, currentAnim = &Hit;

}
bool Enemy_Green2::upDown(bool _Do)
{
	if (_Do == false)
	{
		if (position.y < App->player->position.y) UpDown = false;
		else UpDown = true;
		Do = true;
	}
	return UpDown;
}
void Enemy_Green2::move() {
	switch (pattern) {
	case 0:
		
		if (yRecorrido < 75)
		{
			if (timerAnim->check()) currentAnim = &FirsAnim;
			yRecorrido++;
			position.x += SCREEN_SPEED;
			position.y += 2;
		}
		else
		{
			jump = true, xRecorrido = 110, yRecorrido = 0;
			if (position.y<App->player->position.y + 30 && position.y>App->player->position.y - 30)skip = true;
			else skip = false;
			if (skip == false)pattern = 2;
			else pattern = 7;
		}
		break;
	case 1:
		if (xRecorrido < 110)
		{
			if (timerAnim->check()) currentAnim = &FirsAnim;
			xRecorrido++;
			position.x += -2;
		}
		else
		{
			if (position.y<App->player->position.y + 30 && position.y>App->player->position.y - 30)skip = true;
			else skip = false;
			if (skip == false)pattern = 2;
			else pattern = 7;
		}
		break;
	case 2:
		if (yRecorrido < 25)
		{
			if(yRecorrido < 10 && timerAnim->check())currentAnim = &Down;
			else if (timerAnim->check()) currentAnim = &FirsAnim;
			yRecorrido++;
			position.y += 2;
			position.x += SCREEN_SPEED;
		}
		else
		{
			if (roundThree == true)angulo = 700;
			pattern = 3;
		}
		break;
	case 3:
		if (yRecorrido < 75)
		{
			if (yRecorrido < 55 && timerAnim->check())currentAnim = &Up;
			else if (timerAnim->check())currentAnim = &FirsAnim;
			yRecorrido++;
			position.y -= 2;
			position.x += 1;
		}
		else
		{
			if (jump == false)pattern = 4;
			else pattern = 7;
		}
		break;
	case 4:
		if (yRecorrido < 125)
		{
			if (yRecorrido < 105 && timerAnim->check())currentAnim = &Down;
			else if (timerAnim->check()) currentAnim = &FirsAnim;
			yRecorrido++;
			position.y += 2;
			position.x += 1;
		}
		else pattern = 5;
		break;
	case 5:
		if (yRecorrido < 175)
		{
			if (yRecorrido < 155 && timerAnim->check())currentAnim = &Up;
			else if (timerAnim->check())currentAnim = &FirsAnim;
			yRecorrido++;
			position.y -= 2;
			position.x += 1;
		}
		else pattern = 6;
		break;
	case 6:
		if (yRecorrido < 200)
		{
			if (yRecorrido < 185 && timerAnim->check())currentAnim = &Down;
			else if (timerAnim->check())currentAnim = &FirsAnim;
			yRecorrido++;
			position.y += 2;
			position.x += 1;
		}
		else pattern = 7;
		break;
	case 7:
		if (grados != 90)
		{
			radianes = grados * PI / 180;
			position.x -= radio * sin(radianes);
			if (Do == false)upDown(Do);
			if (UpDown == false && timerAnim->check())currentAnim = &Down;
			else if (UpDown == true && timerAnim->check())currentAnim = &Up;
			if(UpDown==false) position.y += radio * cos(radianes);
			else position.y -= radio * cos(radianes);

			grados += 2.5;
			if (grados == 360)grados = 0;
		}
		else
		{
			if (roundThree == true) angulo = 700;
			grados = 270, pattern = 8;
			Do = false;
		}
		break;
	case 8:///////////////////////////////////
		if (xRecorrido < 155)
		{
			if (timerAnim->check())currentAnim = &FirsAnim;
			xRecorrido++;
			position.x -= 3;
		}
		else
		{
			pattern = 9;
			radio = 1.7;
		}
		break;
	case 9:
		
		if (grados != 90)
		{
			radianes = grados * PI / 180;
			position.x += radio * sin(radianes);
			if (Do == false)upDown(Do);
			if (UpDown == false && timerAnim->check())currentAnim = &Down;
			else if (UpDown == true && timerAnim->check())currentAnim = &Up;
			if (UpDown==false) position.y += radio * cos(radianes);
			else position.y -= radio * cos(radianes);
			grados += 2.5;
			if (grados == 360)grados = 0;
		}
		else
		{
			xRecorrido = 0, Do = false, pattern = 11;
		}
		break;
	case 10:
		radio = 2.5;
		if (grados != angulo)
		{
			if (radio * cos(radianes) < 0 && timerAnim->check())currentAnim = &Down;
			else if (timerAnim->check())currentAnim = &Up;
			radianes = grados * PI / 180;
			position.x += 2.6;
			position.y -= radio * cos(radianes);
			grados += 2.5;
		}
		else
		{
			xRecorrido = 110, yRecorrido = 0, grados = 270, radio = 4.8, roundThree = true;
			if (position.y<App->player->position.y + 30 && position.y>App->player->position.y - 30)skip = true;
			else skip = false;
			if (skip == false)pattern = 2;
			else pattern = 7;
		}
		break;
	case 11:
		
		if (xRecorrido < 40)
		{
			xRecorrido++;
			position.x += 3.5;
			if (Do == false)upDown(Do);
			if (UpDown == false && timerAnim->check())currentAnim = &Down;
			else if (UpDown == true && timerAnim->check())currentAnim = &Up;
			if (UpDown==false) position.y += 3;
			else position.y -= 3;
		}
		else Do = false, pattern = 10;
	}
}