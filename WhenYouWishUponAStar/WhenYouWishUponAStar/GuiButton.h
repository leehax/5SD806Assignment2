#pragma once
#include <string>

class DrawManager;
class GuiButton
{
public:
	GuiButton(int p_x, int p_y, int p_w, int p_h, std::string p_text);
	~GuiButton();
	void Draw();
	void OnClick();
	void HandleButtonEvent(SDL_MouseButtonEvent p_mEv);
	SDL_Rect* GetRect();

private:
	DrawManager * m_drawManager;
	SDL_Rect m_rect;
	std::string m_text;
	SDL_Color m_color;
};

