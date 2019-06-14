#include "Game.h"
#include "GameDefined.h"

Game::Game(HWND hWnd)
{
	this->Init(hWnd);
	this->LoadResources();
}

void Game::LoadResources()
{
	TextureFactory::GetInstance()->LoadResources();
	SpriteFactory::GetInstance()->LoadResources();
	MapFactory::GetInstance()->LoadResources();
	SceneManager::GetInstance()->ReplaceScene(new PlayScene(1));
}

void Game::Init(HWND hWnd)
{
	auto d3d = Direct3DCreate9(D3D_SDK_VERSION);
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;
	
	//get  back bffer info
	RECT r;
	GetClientRect(hWnd, &r);
	d3dpp.BackBufferHeight = r.bottom + 1;
	d3dpp.BackBufferWidth = r.right + 1;

	// get Device
	d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &d3ddev);

	// get BackBuffer
	d3ddev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);

	// get Sprite Handler
	D3DXCreateSprite(d3ddev, &spriteHandler);

	// get Keyboard
	DirectInput8Create((HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID * *)& di, NULL);

	di->CreateDevice(GUID_SysKeyboard, &didv, NULL);
	didv->SetDataFormat(&c_dfDIKeyboard);
	didv->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	DIPROPDWORD dipdw;
	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = KEYBOARD_BUFFER_SIZE; // Arbitary buffer size

	didv->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
	didv->Acquire();
}

void Game::ProcessKeyboard()
{
	//checking keyboard
	auto hr = didv->GetDeviceState(sizeof(keyStates), keyStates);

	if (FAILED(hr))
	{
		if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED))
		{
			auto hr = didv->Acquire();
			if (hr != DI_OK)
				return;
		}
		else
		{
			return;
		}
	}

	DWORD dwElements = KEYBOARD_BUFFER_SIZE;
	hr = didv->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), keyEvents, &dwElements, 0);

	for (DWORD i = 0; i < dwElements; ++i)
	{
		int KeyCode = keyEvents[i].dwOfs;
		int KeyState = keyEvents[i].dwData;
		auto CurScene = SceneManager::GetInstance()->CurScene;
		if ((KeyState & 0x80) > 0)
			CurScene->OnKeyDown(KeyCode);
		else CurScene->OnKeyUp(KeyCode);
	}
}

void Game::Run()
{
	MSG msg;
	auto frameStart = GetTickCount();
	auto tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (isGameRunning)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				isGameRunning = false;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		auto now = GetTickCount();
		auto dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;
			Update(dt);
			ProcessKeyboard();
			Render();
		}
		else
		{
			Sleep(tickPerFrame - dt);
		}
	}
}

void Game::Update(float dt)
{
	SceneManager::GetInstance()->CurScene->Update(dt);
}

void Game::Render()
{
	if (d3ddev->BeginScene())
	{
		d3ddev->ColorFill(backBuffer, NULL, BACK_COLOR);
		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
		SceneManager::GetInstance()->CurScene->Render();
		spriteHandler->End();
		d3ddev->EndScene();
	}
	d3ddev->Present(NULL, NULL, NULL, NULL);
}