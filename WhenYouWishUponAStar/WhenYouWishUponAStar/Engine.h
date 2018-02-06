#pragma once
class DrawManager;
class SpriteManager;
class GridMap;

class Engine
{
public:
	Engine();
	~Engine();
	void Initialise();
	void Destroy();
	void Run();

private:
	void CalculateDelta();
	bool isRunning();
	void LockFrameRate(int p_frameCount);
	float m_delta;

	int m_frameCount;
	int m_frameRate;
	unsigned int m_lastTick;
	unsigned int m_nextTick;

	DrawManager* m_drawManager;
	SpriteManager* m_spriteManager;
	GridMap* m_gridMap;


};

