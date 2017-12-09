#include "ObjectLogic.h"



ObjectLogic::ObjectLogic()
{
}


ObjectLogic::~ObjectLogic()
{
}

//Getters
float ObjectLogic::getLength()
{
	return m_Length;
}

/*Main logic function*/
void ObjectLogic::processLogic(std::vector<Herbivore> *h_vector, std::vector<Carnivore> *c_vector,
	std::vector<Water> *w_vector, std::vector<Plant> *p_vector)
{
	//Checking collision herbivore <-> water
	if (!h_vector->empty() && !w_vector->empty())
	{
		bool m_Flag;
		m_ClosestResourceDistance = 4000;
		for (int i = 0; i <= h_vector->size() - 1; i++)
		{
			m_Flag = false;
			for (int j = 0; j <= w_vector->size() - 1; j++)
			{
				m_PositionVector.x = (*h_vector)[i].getPosition().x - (*w_vector)[j].getPosition().x;
				m_PositionVector.y = (*h_vector)[i].getPosition().y - (*w_vector)[j].getPosition().y;
				m_Length = sqrt(m_PositionVector.x * m_PositionVector.x + m_PositionVector.y * m_PositionVector.y);

				if (m_Length < m_ClosestResourceDistance)
				{
					m_ClosestResource = &(*w_vector)[j];
					m_ClosestResourceDistance = m_Length;
				}

				if ((*h_vector)[i].getCircleShape().getRadius() + (*w_vector)[j].getCircleShape().getRadius() >= m_Length)
				{
					m_Flag = true;
				}

				//Handle drinking water
				if ((*w_vector)[j].getCircleShape().getRadius() >= m_Length && (*h_vector)[i].isDrinking())
				{
					//Drinking water
				}
			}
			//Set found water parameter
			if (m_Flag == true)
			{
				(*h_vector)[i].setFoundWater(true);
			}
			else
			{
				(*h_vector)[i].setFoundWater(false);
			}

			//Set next position according to closest water source
			if ((*h_vector)[i].foundWater() && (*h_vector)[i].isThirsty())
			{
				(*h_vector)[i].setNextPosition(m_ClosestResource->getPosition());
			}
		}
	}
}