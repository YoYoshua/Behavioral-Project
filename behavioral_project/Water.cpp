#include "Water.h"



Water::Water()
{
}


Water::~Water()
{
}

void Water::update(Time dt)
{
	//Updating parameters
	updateParameters(dt);

	//Changing object according to parameters
	m_Sprite.setScale(m_Scale, m_Scale);
	m_VisionCircle.setScale(m_Scale, m_Scale);
}
