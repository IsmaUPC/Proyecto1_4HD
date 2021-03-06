#ifndef _SCENESHOP_H_
#define _SCENESHOP_H_

#include "Module.h"
#include "Animation.h"
#include"Path.h"

struct SDL_Texture;

struct WeaponsPrice{
	bool selected = false;
	int ammo;
	int priceWeapon;
};

class SceneShop : public Module
{
public:
	//Constructor
	SceneShop(bool startEnabled);

	//Destructor
	~SceneShop();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	void resetAnim();

	update_status PreUpdate()override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	update_status Update() override;
	bool CleanUp();

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	update_status PostUpdate() override;
	void printTextAnimation();

	void lowMoney();
	void select();
	void activeSelected(int _weapon);


	void loadInfo();
	void saveInfo();

public:
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* bgTexture = nullptr;
	SDL_Texture* selectorTexture = nullptr;
	int tiendaX = 0, tiendaY = 0;
	int weaponsition = 0;
	uint OptionSelection = 0;
	uint SelectWeapon = 0;
	uint InsuficientMoney = 0;
	uint caching = 0;

	bool keyDownPad = false;
	int hudfont1 = 0;
	
	bool begin = false;
	bool newGame = false;

	//info
	int money=30000;
	int score=0;
	int level=1;
	int pow=3;
	int total=0;
	int lives=2;
	int damage = 1;

	bool infiniteMoney = false;
	bool maxMoney = false;

	WeaponsPrice weapons[11];

	char moneyText[10] = { "\0" };

	//solved
	SDL_Texture* WeaponsSold = nullptr;

	enum SHOP_SLOT {
		CLUSTER,
		PHOENIX,
		FALCON,
		BULLPUP,
		S_SHELL,
		T_LASER,
		BOMB,
		NAPALM,
		GUNPOD,
		CEILING,
		MEGACRUSH,
		EXIT,

	};
	//talk text
	SDL_Texture* currentTextureText = nullptr;
	SDL_Texture* Thankstexture		= nullptr;
	SDL_Texture* BombTtexture		= nullptr;
	SDL_Texture* sShellTtexture		= nullptr;
	SDL_Texture* gunPodTtexture		= nullptr;
	SDL_Texture* CeilingTtexture	= nullptr;
	SDL_Texture* cantBuyTtexture	= nullptr;
	SDL_Texture* exitTtexture		= nullptr;
	SDL_Texture* byeTtexture		= nullptr;
	SDL_Texture* lowMoneyTtexture	= nullptr;

	Animation* currentextAnimation = nullptr;
	Animation lowMoneyText;
	Animation cantBuyText;
	Animation exitText;
	Animation byeText;
	Animation thanksText;
	Animation bombText;
	Animation sShellText;
	Animation gunPodText;
	Animation ceilingText;


	//shopkeeper 
	SDL_Texture* shopkeeperTexture = nullptr;
	Animation* currentAnimationshopkeeper = nullptr;
	Animation shopkeeperTalking;

	bool changeScene = false;
	int block = 0;
	int thaksShopKeeprCount;
};
#endif // !_SCENESHOP_H_
