#include "Enemy_GreenShip.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_GreenShip::Enemy_GreenShip(int x, int y, int _pattern) : Enemy(x, y,_pattern)
{
	flyInvers.PushBack({ 497,213,54,16 });
	//currentAnim = &flyInvers;
	flyInvers.speed = 0.01f;

	fly.PushBack({ 557,213,53,16 });
	currentAnim = &fly;
	fly.speed = 0.01f;

	twistToRight.PushBack({ 435,221,54, 20 });
	twistToRight.PushBack({ 373,214,54, 31 });
	twistToRight.PushBack({ 328,214,39, 31 });
	twistToRight.PushBack({ 289,212,29, 35 });
	twistToRight.PushBack({ 264,210,18, 39 });
	twistToRight.PushBack({ 237,212,23, 35 });
	twistToRight.PushBack({ 196,214,37, 31 });
	twistToRight.PushBack({ 134,214,54, 31 });
	twistToRight.PushBack({ 74,219,54, 20 });
	twistToRight.PushBack({ 557,213,53,16 });
	twistToRight.loop = false;
	twistToRight.speed = 0.15f;

	twistToLeft.PushBack({ 619,221,53, 20 });
	twistToLeft.PushBack({ 680,214,54, 31 });
	twistToLeft.PushBack({ 740,214,39, 31 });
	twistToLeft.PushBack({ 790,212,29, 35 });
	twistToLeft.PushBack({ 825,210,18, 39 });
	twistToLeft.PushBack({ 847,212,23, 35 });
	twistToLeft.PushBack({ 874,214,37, 31 });
	twistToLeft.PushBack({ 920,214,53, 31 });
	twistToLeft.PushBack({ 979,219,54, 20 });
	twistToLeft.PushBack({ 497,213,54,16 });
	twistToLeft.loop = false;
	twistToLeft.speed = 0.15f;

	loopToRight.PushBack({ 0,596,54,31 });
	loopToRight.PushBack({ 54,596,54, 31 });
	loopToRight.PushBack({ 108,596,54, 31 });
	loopToRight.PushBack({ 162,596,54, 31 });
	loopToRight.PushBack({ 216,596,54, 31 });
	loopToRight.PushBack({ 270,596,54, 31 });
	loopToRight.PushBack({ 324,596,54, 31 });
	loopToRight.PushBack({ 378,596,54, 31  });
	//loopToRight.PushBack({ 432,596,54, 31 });
	loopToRight.loop = true;
	loopToRight.speed = 0.3f;

	loopToLeft.PushBack({ 1053,596,54,31 });
	loopToLeft.PushBack({ 999,596,54,31 });
	loopToLeft.PushBack({ 945,596,54,31 });
	loopToLeft.PushBack({ 891,596,54,31 });
	loopToLeft.PushBack({ 837,596,54,31 });
	loopToLeft.PushBack({ 783,596,54,31 });
	loopToLeft.PushBack({ 729,596,54,31 });
	//loopToLeft.PushBack({ 675,596,54,31 });
	loopToLeft.loop = true;
	loopToLeft.speed = 0.3f;

	collider = App->collisions->AddCollider({0, 0, 54, 16}, Collider::Type::ENEMY, (Module*)App->enemies);
	if (pattern == 3)init = true;
	else if (pattern == 4)init = true;
	else if (pattern == 6)pattern = 2, MAX += 50, speedPattern2 += 1;
	else if (pattern == 5)pattern = 1, MAX += 50, speedPattern2 += 1;
	else if (pattern == 7)pattern = 2, MAX += 50, speedPattern2 += 1, up = -0.6;
	else if (pattern == 8)pattern = 2, MAX += 50, speedPattern2 += 1, up = -1.3;
	else if (pattern >= 2 && position.x > 3000 && position.x < 3000) multiSpeed = 1.5; //hay que cambiarlo a 3000
	else multiSpeed = 1, MAX = 50, TOP=2.1;
	if (position.y == 260) TOP = 0.8;

}

void Enemy_GreenShip::Update()
{
	move();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}

void Enemy_GreenShip::move() {
	//spawnPos.x += SCREEN_SPEED;
	if (collider->pendingToDelete != true)
		resizeCollider();

	switch (pattern) {
	case 0:
		switch (FASE)
		{
		case 1:
			currentAnim = &flyInvers;
			if (xRecorrido < 100)
			{
				xRecorrido += 2;
				position.y -= 0;
				position.x -= 2;
			}
			else FASE = 2;
			break;
		case 2:
			currentAnim = &flyInvers;
			if (xRecorrido < 300)
			{
				xRecorrido += 2;
				position.y -= 0.85;
				position.x -= 2;
			}
			else FASE = 3;
			break;
		case 3:
			currentAnim = &twistToRight;
			if (yRecorrido < 50)
			{
				yRecorrido += 2;
				position.y += 2.1;
				position.x -= 0.9;
			}
			else FASE = 4;
			break;
		case 4:
			currentAnim = &twistToRight;
			if (yRecorrido < 110)
			{
				yRecorrido += 2;
				position.y += TOP;
				position.x += 1.8;
			}
			else FASE = 5;
			break;
		case 5:
			if (xRecorrido > 315) currentAnim = &loopToRight;
			xRecorrido += 2;
			position.y = position.y;
			position.x += 6;
		}
		break;

	case 1:
		switch (FASE)
		{
		case 1:
			currentAnim = &flyInvers;
			if (xRecorrido < MAX)
			{
				xRecorrido += speedPattern2;
				position.y -= 0;
				position.x -= speedPattern2 + 1;
			}
			else FASE = 2;
			break;
		case 2:
			currentAnim = &flyInvers;
			if (xRecorrido < 200+MAX)
			{
				xRecorrido += speedPattern2;
				position.y -= 0.5;
				position.x -= speedPattern2+1;
			}
			else 
				FASE = 3;
			break;
		case 3:
			currentAnim = &twistToRight;
			if (yRecorrido < 70)
			{
				yRecorrido += 2;
				position.y -= 1.5; 
				position.x += 0.8;
			}
			else FASE = 4;
			break;
		case 4:
			currentAnim = &twistToRight;
			if (yRecorrido < 140)
			{
				yRecorrido += 2;
				position.y -= 1.5; 
				position.x += 1.4;
			}
			else FASE = 5;
			break;
		case 5:
			if (xRecorrido > 250) currentAnim = &loopToRight;
			xRecorrido += 2;								 
			position.y = position.y;
			position.x += 5; 
		}
		break;
	case 2:
		switch (FASE)
		{
		case 1:
			currentAnim = &flyInvers;
			if (xRecorrido < MAX)
			{
				xRecorrido += speedPattern2;
				position.y -= 0;
				position.x -= speedPattern2+1;
			}
			else FASE = 2;
			break;
		case 2:
			currentAnim = &flyInvers;
			if (xRecorrido < 200+MAX)
			{
				xRecorrido += speedPattern2;
				position.y += 0.5;
				position.x -= speedPattern2+1;
			}
			else FASE = 3;
			break;
		case 3:
			currentAnim = &twistToRight;
			if (yRecorrido < 70)
			{
				yRecorrido += 2;
				position.y += up; 
				position.x += 0.8;
			}
			else FASE = 4;
			break;
		case 4:
			currentAnim = &twistToRight;
			if (yRecorrido < 140)
			{
				yRecorrido += 2;
				position.y += up; 
				position.x += 1.4;
			}
			else FASE = 5;
			break;
		case 5:
			if (xRecorrido > 250) currentAnim = &loopToRight;
			xRecorrido += 2;								
			position.y = position.y;
			position.x += multiSpeed*5; 
		}
		break;

	case 3:
		switch (FASE)
		{
		case 1:
			currentAnim = &flyInvers;
			if (xRecorrido < 100)
			{
				xRecorrido += 3;
				position.y -= 0;
				position.x -= 4;
			}
			else FASE = 2;
			break;
		case 2:
			currentAnim = &flyInvers;
			if (xRecorrido < 300)
			{
				xRecorrido += 3;
				position.y -= 1;
				position.x -= 4;
			}
			else
				FASE = 3;
			break;
		case 3:
			currentAnim = &twistToRight;
			if (yRecorrido < 70)
			{
				yRecorrido += 2;
				position.y -= speed;
				position.x += 0.8;
			}
			else FASE = 4;
			break;
		case 4:
			currentAnim = &twistToRight;
			if (yRecorrido < 140)
			{
				yRecorrido += 2;
				position.y -= speed;
				position.x += 1.4;
			}
			else FASE = 5;
			break;
		case 5:
			if (xRecorrido > 300) currentAnim = &loopToRight;
			xRecorrido += 3;								 
			position.y = position.y;
			position.x += multiSpeed*6;
		}
		break;
	case 4:
		switch (FASE)
		{
		case 1:
			currentAnim = &flyInvers;
			if (xRecorrido < 100)
			{
				xRecorrido += 3;
				position.y -= 0;
				position.x -= 4;
			}
			else FASE = 2;
			break;
		case 2:
			currentAnim = &flyInvers;
			if (xRecorrido < 300)
			{
				xRecorrido += 3;
				position.y += 1;
				position.x -= 4;
			}
			else FASE = 3;
			break;
		case 3:
			currentAnim = &twistToRight;
			if (yRecorrido < 70)
			{
				yRecorrido += 2;
				position.y += speed;
				position.x += 0.8;
			}
			else FASE = 4;
			break;
		case 4:
			currentAnim = &twistToRight;
			if (yRecorrido < 140)
			{
				yRecorrido += 2;
				position.y += speed;
				position.x += 1.4;
			}
			else FASE = 5;
			break;
		case 5:
			if (xRecorrido > 300) currentAnim = &loopToRight;
			xRecorrido += 3;								 
			position.y = position.y;
			position.x += multiSpeed*6;
		}
		break;

	}
}


