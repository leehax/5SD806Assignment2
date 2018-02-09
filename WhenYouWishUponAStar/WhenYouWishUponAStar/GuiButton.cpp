#include "stdafx.h"
#include "GuiButton.h"
#include "DrawManager.h"
#include "ServiceLocator.h"


GuiButton::GuiButton(int p_x, int p_y, int p_w, int p_h, std::string p_text)
{
	m_drawManager = ServiceLocator<DrawManager>::GetService();
	m_rect = { p_x,p_y,p_w,p_h };
	m_text = p_text;
	m_color = {255,255,255,255};
}

GuiButton::~GuiButton()
{
}

void GuiButton::Draw()
{
	m_drawManager->DrawRect(m_rect, m_color.r, m_color.g, m_color.b, m_color.a);
	m_drawManager->DrawText(m_rect.x, m_rect.y, 12, m_text, m_color);
}

void GuiButton::OnClick()
{
	
}

void GuiButton::HandleButtonEvent(SDL_MouseButtonEvent p_mEv)
{
	if(p_mEv.type==SDL_MOUSEBUTTONDOWN&&p_mEv.button==SDL_BUTTON_LEFT)
	{
		OnClick();
	}
}

SDL_Rect* GuiButton::GetRect()
{
	return &m_rect;
}
