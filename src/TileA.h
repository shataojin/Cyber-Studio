#pragma once
#ifndef _TILE_A_
#define _TILE_A_
#include "SpriteA.h"


class TileA : public SpriteA
{
public:
	TileA(SDL_Rect s, SDL_FRect d, SDL_Renderer* r, SDL_Texture* t, const bool o, const bool h)
		:SpriteA(s, d, r, t), m_obstacleA(o), m_hazardA(h){}
	bool IsObstacle() { return m_obstacleA; }
	bool IsHazard() { return m_hazardA; }
	TileA* Clone() { return new TileA(m_src, m_dst, m_pRend, m_pText, m_obstacleA, m_hazardA); }
private:
	bool m_obstacleA,
		m_hazardA;
};
#endif
