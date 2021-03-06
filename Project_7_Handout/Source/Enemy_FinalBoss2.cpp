﻿#include "Enemy_FinalBoss2.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleAudio.h"
#include "SDL_mixer/include/SDL_mixer.h" 
#include "ModuleRender.h"


Enemy_FinalBoss2::Enemy_FinalBoss2(int x, int y, int _pattern) :Enemy(x, y, _pattern)
{
	//Animation
	lives = 60;
	timerState = new Timer(60);
	timerStateCollision = new Timer(2000);
	timerAnim = new Timer(100);
	timerShotBombs = new Timer(3000);
	timerCadenceBombs = new Timer(90);

	FirsAnim.PushBack({ 0,0,85,32 });
	currentAnim = &FirsAnim;

	Inclined.PushBack({ 85,0,86,40 });

	Down.PushBack({ 171,0,85,53 });

	Hit.PushBack({ 0,56,85,32 });
	HitInclined.PushBack({ 85,56,86,41 });
	HitDown.PushBack({ 171,56,85,53 });


	collider = App->collisions->AddCollider({ 0, 0, 85, 32 }, Collider::Type::BOSS2, (Module*)App->enemies);
	App->audio->PlayMusic("Assets/sounds/Boss2.ogg", 0);
	if(pattern==1)position.x -= SCREEN_WIDTH + 100;
}

void Enemy_FinalBoss2::Update() {

	timerState->update();
	timerShotBombs->update();
	timerCadenceBombs->update();

	if (timerShotBombs->check()) 
		if (App->player->position.x > position.x) misilShoted = false;
		else limitBombs = 0;
	

	if (timerState->check()) stateEnemy = status_Enemies::STATE_ENEMY_IDLE;

	timerStateCollision->update();
	if (timerStateCollision->check()) stateEnemy = status_Enemies::STATE_ENEMY_IDLE;
	
	timerAnim->update();
	//if (timerAnim->check())currentAnim = &FirsAnim;
	move();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}

void Enemy_FinalBoss2::Anim1()
{
	if (timerAnim->check())
	{
		if (radio * cos(radianes) < 0)currentAnim = &FirsAnim;
		else currentAnim = &Down;
	}
}
void Enemy_FinalBoss2::Anim2()
{
	if (timerAnim->check())
	{
		if (radio * cos(radianes) > 0)currentAnim = &FirsAnim;
		else  currentAnim = &Down;
	}
}
void Enemy_FinalBoss2::AnimHit()
{
	if (currentAnim == &FirsAnim)currentAnim = &Hit;
	if (currentAnim == &Inclined)currentAnim = &HitInclined;
	if (currentAnim == &Down)currentAnim = &HitDown;
}
void Enemy_FinalBoss2::OnCollision(Collider* collider)
{
	if (collider->type == Collider::PLAYER_SHOT && stateEnemy != status_Enemies::STATE_ENEMY_HIT)lives--, stateEnemy = status_Enemies::STATE_ENEMY_HIT, AnimHit();
	else if (collider->type == Collider::PLAYER && stateEnemy != status_Enemies::STATE_ENEMY_HIT_COLLISION)lives--, stateEnemy = status_Enemies::STATE_ENEMY_HIT_COLLISION, AnimHit();
	if (collider->type == Collider::SW_BOMB && stateEnemy != status_Enemies::STATE_ENEMY_HIT)lives--, stateEnemy = status_Enemies::STATE_ENEMY_HIT, AnimHit();
	if (collider->type == Collider::SW_CEILING && stateEnemy != status_Enemies::STATE_ENEMY_HIT)lives--, stateEnemy = status_Enemies::STATE_ENEMY_HIT, AnimHit();
	if (collider->type == Collider::SW_GUNPOD && stateEnemy != status_Enemies::STATE_ENEMY_HIT)lives--, stateEnemy = status_Enemies::STATE_ENEMY_HIT, AnimHit();
	if (collider->type == Collider::SW_S_SHELL && stateEnemy != status_Enemies::STATE_ENEMY_HIT)lives--, stateEnemy = status_Enemies::STATE_ENEMY_HIT, AnimHit();
	if (lives == 0 && App->player->destroyed == false) App->level2->Win();
}

bool Enemy_FinalBoss2::upDown(bool _Do)
{
	if (_Do == false){
		if (position.y < App->player->position.y) UpDown = false;
		else UpDown = true;
		Do = true;
	}
	return UpDown;
}

void Enemy_FinalBoss2::move() {

	if (collider->pendingToDelete != true) {
		collider->SetPos(position.x, position.y + ((*currentAnim).GetCurrentFrame().h / 3) - (collider->rect.h / 3));
	}
	switch (pattern) {
	case 0:
		switch (FASE) {
		case 0:
			if (grados != angulo)
			{
				if (timerAnim->check())
				{
					if (radio * cos(radianes) < 0)currentAnim = &FirsAnim;
					else currentAnim = &Down;
				}
				radianes = grados * PI / 180;
				position.x -= 2;
				position.y += radio * cos(radianes);
				grados += 2;
			}
			else FASE = 1, grados = 0, angulo = 180;
			break;
		case 1:
			radio = 3;
			if (Do == false)upDown(Do);
			if (grados <= angulo)
			{
				shots();
				radianes = grados * PI / 180;
				position.x += 3.2;
				if (UpDown == false)position.y += radio * cos(radianes), Anim1();
				else position.y -= radio * cos(radianes), Anim2();
				grados += 1.2;
			}
			else FASE = 2, grados = 0, Do = false;
			break;
		case 2:
			radio = 3;
			if (Do == false)upDown(Do);
			if (grados <= angulo)
			{
				radianes = grados * PI / 180;
				position.x -= 1.2;
				if (UpDown == false)position.y += radio * cos(radianes), Anim1();
				else position.y -= radio * cos(radianes), Anim2();
				grados += 1.2;
			}
			else FASE = 3, Do = false;
			break;
		case 3:
			if (Do == false)upDown(Do);
			if (xRecorrido < 60)
			{
				shots();

				xRecorrido++;
				position.x += 4;
				if (UpDown == false) position.y += 2, Anim1();
				else position.y -= 2, Anim2();
			}
			else FASE = 4, Do = false;
			break;
		case 4:
			if (xRecorrido < 120)
			{
				shots();
				if (timerAnim->check())currentAnim = &Inclined;
				xRecorrido++;
				position.x += 3;
			}
			else FASE = 5, angulo = 300, grados = 90;
			break;
		case 5:
			radio = 3;
			if (grados <= angulo)
			{
				radianes = grados * PI / 180;
				position.x += radio * sin(radianes);
				if (UpDown == false)position.y += radio * cos(radianes), Anim1();
				else position.y -= radio * cos(radianes), Anim2();
				grados += 2.5;
			}
			else FASE = 6, Do = false;
			break;
		case 6:
			if (xRecorrido < 165)
			{
				xRecorrido++;
				position.x -= 2.9;
				if (UpDown == false)position.y += 2.2, Anim1();
				else position.y -= 2.2, Anim2();

			}
			else FASE = 7, Do = false;
			break;
		case 7:
			if (xRecorrido < 320)
			{
				shots();
				xRecorrido++;
				position.x += 3;
				if (UpDown == false)position.y -= 1, Anim1();
				else position.y += 1, Anim2();

			}
			else FASE = 8, Do = false;
			break;
		case 8:
			if (position.y > 221)
			{
				shots();
				position.x += 3;
				position.y -= 2;
				if (timerAnim->check()) currentAnim = &FirsAnim;
			}
			else if (position.y < 219)
			{
				position.x += 3;
				position.y += 2;
				if (timerAnim->check()) currentAnim = &Down;
			}
			else FASE = 9;
			break;
		case 9:
			if (position.x > App->render->camera.x + 20)
			{
				xRecorrido++;
				position.x -= 3;
				if (timerAnim->check()) currentAnim = &Inclined;
			}
			else FASE = 1, xRecorrido = 0, angulo = 180, grados = 0;
			break;
		}
		break;
	case 1:
		switch (FASE) {
		case 0:
			if (xRecorrido < 30)
			{
				xRecorrido++;
				position.x += 3;
				if (timerAnim->check()) currentAnim = &Inclined;
			}
			else FASE = 1;
			break;
		case 1:
			if (xRecorrido < 135)
			{
				shots();
				xRecorrido++;
				position.x += 3.1;
				position.y -= 2;
				if (timerAnim->check()) currentAnim = &FirsAnim;
			}
			else FASE = 2, angulo = 250, grados = 90;
			break;
		case 2:
			radio = 4;
			if (grados <= angulo)
			{
				if (timerAnim->check())currentAnim = &Down;
				radianes = grados * PI / 180;
				position.x += (radio + 2) * sin(radianes);
				position.y -= radio * cos(radianes);
				grados += 2;
			}
			else FASE = 3;
			break;
		case 3:
			if (position.y > 220)
			{
				position.x -= 3;
				position.y -= 2;
				if (timerAnim->check()) currentAnim = &FirsAnim;
			}
			else FASE = 4, angulo = 270, grados = 180;
			break;
		case 4:
			shots();
			radio = 5;
			if (Do == false)upDown(Do);
			if (grados <= angulo)
			{
				radianes = grados * PI / 180;
				position.x -= (radio + 1) * sin(radianes);
				if (UpDown == false)position.y -= radio * cos(radianes), Anim2();
				else position.y += radio * cos(radianes), Anim1();
				grados += 2;
			}
			else FASE = 5, Do = false;
			break;
		case 5:
			shots();
			if (position.x < App->render->camera.x + SCREEN_WIDTH - 100)
			{
				position.x += 3;
				if (UpDown == false)position.y -= 2, Anim1();
				else position.y += 2, Anim2();
			}
			else FASE = 6;
			break;
		case 6:
			if (position.x > App->render->camera.x)
			{
				position.x -= 2.5;
				if (UpDown == false)position.y += 2, Anim2();
				else position.y -= 2, Anim1();
			}
			else FASE = 7;
			break;
		case 7:
			shots();

			if (position.x < App->render->camera.x + (SCREEN_WIDTH / 2) - 60)
			{
				position.x += 3;
				if (UpDown == true)position.y += 2.5, Anim2();
				else position.y -= 2.5, Anim1();
			}
			else FASE = 8;
			break;
		case 8:
			shots();

			if (position.y<App->player->position.y + 3 && position.y > App->player->position.y - 3) FASE = 9;
			else if (position.y < App->player->position.y)
			{
				position.x += 3;
				position.y += 2.5;
				if (timerAnim->check())currentAnim = &Down;
			}
			else
			{
				position.x += 3;
				position.y -= 2.5;
				if (timerAnim->check())currentAnim = &FirsAnim;
			}
			break;
		case 9:
			shots();

			if (position.x < App->render->camera.x + SCREEN_WIDTH - 100) position.x += 5;
			else FASE = 10;
		case 10:
			if (position.x > App->render->camera.x)
			{
				position.x -= 2;
				if (timerAnim->check()) currentAnim = &Inclined;
			}
			else FASE = 11;
			break;
		case 11:
			if (position.y < 220 + 3 && position.y > 220 - 3) FASE = 3;
			else if (position.y < 220)
			{
				position.x += SCREEN_SPEED;
				position.y += 2.5;
				if (timerAnim->check())currentAnim = &Down;
			}
			else
			{
				position.x += SCREEN_SPEED;
				position.y -= 2.5;
				if (timerAnim->check())currentAnim = &FirsAnim;
			}
			break;
		}
		break;
	case 2:
		switch (FASE)
		{
		case 0:
			if (xRecorrido < 30)
			{
				xRecorrido++;
				position.x -= 3;
				if (timerAnim->check()) currentAnim = &Inclined;
			}
			else FASE = 1;
			break;
		case 1:
			if (position.y<App->player->position.y + 3 && position.y > App->player->position.y - 3) FASE = 2;
			else if (position.y < App->player->position.y)
			{
				position.x -= 3;
				position.y += 2;
				if (timerAnim->check())currentAnim = &Down;
			}
			else
			{
				position.x -= 3;
				position.y -= 2;
				if (timerAnim->check())currentAnim = &FirsAnim;
			}
			break;
		case 2:
			if (position.x > App->render->camera.x)
			{
				position.x -= 2;
				if (timerAnim->check()) currentAnim = &Inclined;
			}
			else FASE = 3;
			break;
		case 3:
			shots();

			if (xRecorrido < 110)
			{
				xRecorrido++;
				position.x += 3;
				if (timerAnim->check()) currentAnim = &Inclined;
			}
			else FASE = 4;
			break;
		case 4:
			shots();

			if (position.y < 220 + 3 && position.y > 220 - 3) FASE = 5, grados = 270, radio = 3;
			else if (position.y < 220)
			{
				position.x += 3;
				position.y += 1.5;
				if (timerAnim->check())currentAnim = &Down;
			}
			else
			{
				position.x += 3;
				position.y -= 1.5;
				if (timerAnim->check())currentAnim = &FirsAnim;
			}
			break;
		case 5:
			angulo = 450;
			if (Do == false)upDown(Do);
			if (grados <= angulo && !(position.y < App->player->position.y + 3 && position.y > App->player->position.y - 3))
			{
				radianes = grados * PI / 180;
				position.x -= radio * sin(radianes);
				if (UpDown == false)position.y += radio * cos(radianes), Anim1();
				else position.y -= radio * cos(radianes), Anim2();
				grados += 2.5;
			}
			else FASE = 6, Do = false;
			break;
		case 6:
			if (position.x > App->render->camera.x + 200)
			{
				position.x -= 2;
				if (timerAnim->check()) currentAnim = &Inclined;

			}
			else FASE = 7, grados = 90, angulo = 180;
			break;
		case 7:
			radio = 5;
			if (grados <= angulo && !(position.y < 220 + 3 && position.y > 220 - 3))
			{
				radianes = grados * PI / 180;
				position.x -= (radio)*sin(radianes);
				if (UpDown == true)position.y -= radio * cos(radianes), Anim2();
				else position.y += radio * cos(radianes), Anim1();
				grados += 2;
			}
			else FASE = 8, Do = false, grados = 0;
			break;
		case 8:
			shots();
			radio = 3;
			if (Do == false)upDown(Do);
			if (grados <= angulo)
			{
				radianes = grados * PI / 180;
				position.x += 3.2;
				if (UpDown == false)position.y -= radio * cos(radianes), Anim2();
				else position.y += radio * cos(radianes), Anim1();
				grados += 1.2;
			}
			else FASE = 9;
			break;
		case 9:
			shots();
			if (xRecorrido < 120)
			{
				xRecorrido++;
				position.x += 3;
				if (timerAnim->check()) currentAnim = &Inclined;
			}
			else FASE = 1, xRecorrido = 0, grados = 0, Do = false;
			break;
		}
		break;
	}
}

void Enemy_FinalBoss2::shotSmallBombs(){

	randPos = (rand() % 50)-25;
	if (limitBombs<8) {
		App->particles->AddParticle(App->particles->pBoss2ShotBombs, position.x , position.y + randPos, Collider::Type::BOSS2_BOMBS);
		++limitBombs;
	}
}
void Enemy_FinalBoss2::shots(){
	if (timerCadenceBombs->check()) shotSmallBombs(), shotMisile();

}
void Enemy_FinalBoss2::shotMisile(){

	if(!misilShoted) App->particles->AddParticle(App->particles->pBoss2ShotMisile, position.x , position.y, Collider::Type::BOSS2_MISILE);
	misilShoted = true;
}

