#pragma once
#include "GameGlobal.h"
#include "SceneManager.h"
#include "MapFactory.h"
#include "SpriteFactory.h"
#include "TextureFactory.h"
#include "PlayScene.h"
#include <WinUser.h>
#include "GameDefined.h"

class Game
{
private:
	LPDIRECTINPUT8 di;										// The DirectInput object         
	LPDIRECTINPUTDEVICE8 didv;								// The keyboard device
	BYTE  keyStates[256];									// DirectInput keyboard state buffer 
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		// Buffered keyboard data
	
public:
	Game(HWND hWnd);				
	void Init(HWND hWnd);			
	void LoadResources();
	void Run();						
	void Update(float dt);			
	void Render();					
	void ProcessKeyboard();
};