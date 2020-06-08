#ifndef __COLLIDER_H__
#define __COLLIDER_H__
#include "p2Point.h"

#include "SDL/include/SDL_Rect.h"

#define MAX_LISTENERS 7

class Module;
class Enemy;

struct Collider
{
	enum Type
	{
		NONE ,
		WALL,
		PLAYER,
		ENEMY,
		PLAYER_SHOT,
		ENEMY_SHOT,
		M_BOSS1_SHOT,
		BOSS1,
		M_BOSS1,

		MAX
	};

	//Methods
	Collider(SDL_Rect rectangle, Type type, Module* listener = nullptr);
	Collider(SDL_Rect rectangle, Type type, Enemy* listener = nullptr);

	void SetPos(int x, int y);
	void SetPos(fPoint floatPoint);


	bool Intersects(const SDL_Rect& r) const;

	void AddListener(Module* listener);

	void AddListener(Enemy* listener);

	//Variables
	SDL_Rect rect;
	bool pendingToDelete = false;
	Type type;
	Module* listeners[MAX_LISTENERS] = { nullptr };
	Enemy* listenersE[MAX_LISTENERS] = { nullptr };
};


#endif // !__COLLIDER_H__

