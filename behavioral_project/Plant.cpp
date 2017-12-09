#include "Plant.h"



Plant::Plant()
{
}


Plant::~Plant()
{
}

void Plant::update(Time dt)
{
	//Updating parameters
	updateParameters(dt);

	//Changing object according to parameters
	m_Sprite.setScale(m_Scale, m_Scale);
}
