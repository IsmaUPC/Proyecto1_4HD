#include "ModuleScene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"

ModuleScene::ModuleScene(bool startEnabled) : Module(startEnabled)
{

}

ModuleScene::~ModuleScene()
{

}

// Load assets
bool ModuleScene::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTextures[0] = App->textures->Load("Assets/centro_1_2.png");
	bgTextures[1] = App->textures->Load("Assets/centro_2_2.png");
	bgTextures[2] = App->textures->Load("Assets/centro_3_2.png");
	bgTextures[3] = App->textures->Load("Assets/centro_4_2.png");

	App->audio->PlayMusic("Assets/EnemyAirforce.ogg", 6);

	//Bottomside collider
	//App->collisions->AddCollider({ 0, 224, 3930, 16 }, Collider::Type::WALL);
	
	// Enemies ---	
	//App->enemies->spawningEnemies(4, ENEMY_TYPE::REDSHIP, 600, 130, 100, 0);

	App->enemies->spawningEnemies(4, ENEMY_TYPE::REDSHIP, 800, 380, 50, 1);
	App->enemies->spawningEnemies(4,ENEMY_TYPE::BROWNSHIP, 600, 180, 30, 0);
	App->enemies->spawningEnemies(4, ENEMY_TYPE::GREENSHIP, 1200, 300, 90, 0);
	App->enemies->spawningEnemies(4, ENEMY_TYPE::YELLOWSHIP, 1200, 150, 90, 0);
	App->enemies->spawningEnemies(2, ENEMY_TYPE::BLUESHIP, 1200, 350, 90, 0);

	App->player->Enable();
	App->enemies->Enable();

	return ret;
}

update_status ModuleScene::Update(){


	App->render->camera.x += SCREEN_SPEED;
	updateBackground();

	//if (cen) {
	//}

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background

update_status ModuleScene::PostUpdate(){
	
	// Draw everything --------------------------------------
	//App->render->Blit(bgTexture, 0, 0, NULL);
	
	for (int i = 0; i < 4; i++){
		App->render->Blit(bgTextures[i], SCREEN_WIDTH * cont[i], 0, NULL, i+1);
		App->render->Blit(bgTextures[i], SCREEN_WIDTH * (cont[i] + 1), 0, NULL, i+1);
		App->render->Blit(bgTextures[i], SCREEN_WIDTH * (cont[i] + 2), 0, NULL, i+1);
	}
	
	return update_status::UPDATE_CONTINUE;
}


void ModuleScene::updateBackground() {
	
	for (int i = 0; i < 4; i++){
		if (((App->render->camera.x) % ((SCREEN_WIDTH / (i+1)) + 1)) == 0) {
			cont[i]++;
		}
	}
}
bool ModuleScene::CleanUp()
{
//Enable (and properly disable) the player module
	App->player->Disable();
	App->enemies->Disable();



	return true;
}


