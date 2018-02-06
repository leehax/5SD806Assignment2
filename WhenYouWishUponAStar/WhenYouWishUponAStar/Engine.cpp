#include "stdafx.h"
#include "Engine.h"
#include <iostream>
#include "GridMap.h"
#include "ServiceLocator.h"
#include "DrawManager.h"
#include "SpriteManager.h"


Engine::Engine()
{
	assert(SDL_Init(SDL_INIT_EVERYTHING) == 0 && "SDL_Init FAILED!"); //SDL_Init returns 0 on success

	assert(IMG_Init(IMG_INIT_PNG) ==IMG_INIT_PNG && "IMG_Init FAILED!"); //IMG_Init returns the flag on success

	assert(TTF_Init() == 0 && "TTF_Init FAILED!");	//TTF_Init returns 0 on success

	isRunning();
}


Engine::~Engine()
{
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void Engine::Initialise()
{
	m_drawManager = new DrawManager();
	
	m_gridMap = new GridMap();
	
	m_drawManager->Initialise();
	m_spriteManager = new SpriteManager(m_drawManager->GetRenderer());

	ServiceLocator<DrawManager>::ProvideService(m_drawManager);
	ServiceLocator<SpriteManager>::ProvideService(m_spriteManager);
	ServiceLocator<GridMap>::ProvideService(m_gridMap);
	m_gridMap->Initialise();
	
}

void Engine::Destroy()

{
	delete m_gridMap;
	m_gridMap = nullptr;
	delete m_spriteManager;
	m_spriteManager = nullptr;
	m_drawManager->Destroy();
	delete m_drawManager;
	m_drawManager = nullptr;

}

void Engine::Run()
{
	while(isRunning()==true)
	{
		m_drawManager->Clear();
		CalculateDelta();

		m_gridMap->DrawGrid(0, 0, 0, 255);
		m_gridMap->Update(m_delta);
		
		m_drawManager->Present();
	}
}

void Engine::CalculateDelta()
{
	m_delta = 0.001f*(SDL_GetTicks() - m_lastTick);
	m_lastTick = SDL_GetTicks();
}


bool Engine::isRunning()
{
	SDL_Event event;
	while (SDL_PollEvent(&event) == 1)
	{
		if (event.type == SDL_QUIT) {
			return false;
		}
	}
	return true;
}

void Engine::LockFrameRate(int p_frameCount)
{
	if(m_delta<30)
	{
		SDL_Delay(30 - m_delta);
	}
	m_frameCount++;
	if (m_nextTick < SDL_GetTicks())
	{
		m_frameCount = p_frameCount / 1.0f;
		m_frameRate = m_frameCount;
		std::cout << "FPS: " << m_frameRate << '\n';
		m_frameCount = 0;
		m_nextTick = SDL_GetTicks() + 1000;
	}
}
