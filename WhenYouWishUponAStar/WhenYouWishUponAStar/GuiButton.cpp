#include "stdafx.h"
#include "GuiButton.h"
#include "DrawManager.h"
#include "ServiceLocator.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "Config.h"


GuiButton::GuiButton(int p_x, int p_y, std::string p_name, std::string p_spriteFilePath)
{
	m_drawManager = ServiceLocator<DrawManager>::GetService();
	m_spriteManager = ServiceLocator<SpriteManager>::GetService();
	m_sprite = m_spriteManager->CreateSprite(p_spriteFilePath, 0, 0, 32, 32);
	m_name = p_name;
	int width, height;
	if(m_sprite!=nullptr)
	{
		width = m_sprite->GetClip().w;
		height = m_sprite->GetClip().h;
	}
	m_rect = { p_x,p_y, width, height};

	m_color1 = { 0,255,255,255};
	m_color2 = { 255,255,255,255 };
	m_textHeightOffset = m_rect.h;
}

GuiButton::GuiButton(int p_x, int p_y, std::string p_name)
{
	m_drawManager = ServiceLocator<DrawManager>::GetService();
	m_name = p_name;
	m_sprite = nullptr;
	m_spriteManager = nullptr;
	int width = Config::TILE_SIZE;
	int height = Config::TILE_SIZE;
	m_rect = { p_x,p_y, width, height };
	m_color1 = { 0,255,255,255 };
	m_color2 = { 255,255,255,255 };
	m_textHeightOffset = Config::HALF_TILE;
}

GuiButton::~GuiButton()
{
	m_drawManager = nullptr;
	m_sprite = nullptr;
	m_spriteManager = nullptr;
}

void GuiButton::Draw()
{
	if (m_sprite) {
		m_drawManager->Draw(m_sprite, m_rect.x, m_rect.y, 1);
	}
	m_drawManager->DrawRect(m_rect, m_activeColor.r, m_activeColor.g, m_activeColor.b, m_activeColor.a);
	m_drawManager->DrawText(m_rect.x, m_rect.y+m_textHeightOffset, 12, m_name, m_activeColor);

}

void GuiButton::SetActive(bool p_val)
{
	m_active = p_val;
	if(m_active)
	{
		m_activeColor = m_color1;
	}
	else
	{
		m_activeColor = m_color2;
	}
}

void GuiButton::HandleButtonEvent(SDL_MouseButtonEvent p_mEv)
{
	if(p_mEv.type==SDL_MOUSEBUTTONDOWN&&p_mEv.button==SDL_BUTTON_LEFT)
	{
		SetActive(!m_active);
	}
}

bool GuiButton::IsActive()
{
	return m_active;
}

SDL_Rect* GuiButton::GetRect()
{
	return &m_rect;
}

std::string GuiButton::GetName()
{
	return m_name;
}

