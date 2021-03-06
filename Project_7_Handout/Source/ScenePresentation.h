#ifndef __SCENE_PRESENTATION_H__
#define __SCENE_PRESENTATION_H__

#include "Module.h"
#include "Animation.h"
#include"Path.h"

struct SDL_Texture;

class ScenePresentation : public Module
{
public:
	//Constructor
	ScenePresentation(bool startEnabled);

	//Destructor
	~ScenePresentation();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	update_status Update() override;
	bool CleanUp();

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	update_status PostUpdate() override;

public:
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* bgTexture = nullptr;
	Animation Presentation_Anim;
	Animation* currentAnim = nullptr;
};

#endif

