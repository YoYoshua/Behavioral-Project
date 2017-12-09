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
	std::vector<Water> *w_vector, std::vector<Plant> *p_vector, Time dt)
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
				if ((*w_vector)[j].getCircleShape().getRadius() >= m_Length && (*h_vector)[i].getThirst() >= 0)
				{
					(*h_vector)[i].drinkWater(&(*w_vector)[j], dt);
					(*h_vector)[i].setIsThirsty(false);
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

	//Checking collision herbivore <-> plant
	if (!h_vector->empty() && !p_vector->empty())
	{
		bool m_Flag;
		m_ClosestResourceDistance = 4000;
		for (int i = 0; i <= h_vector->size() - 1; i++)
		{
			m_Flag = false;
			for (int j = 0; j <= p_vector->size() - 1; j++)
			{
				m_PositionVector.x = (*h_vector)[i].getPosition().x - (*p_vector)[j].getPosition().x;
				m_PositionVector.y = (*h_vector)[i].getPosition().y - (*p_vector)[j].getPosition().y;
				m_Length = sqrt(m_PositionVector.x * m_PositionVector.x + m_PositionVector.y * m_PositionVector.y);

				if (m_Length < m_ClosestResourceDistance)
				{
					m_ClosestResource = &(*p_vector)[j];
					m_ClosestResourceDistance = m_Length;
				}

				if ((*h_vector)[i].getCircleShape().getRadius() + (*p_vector)[j].getCircleShape().getRadius() >= m_Length)
				{
					m_Flag = true;
				}

				//Handle eating food
				if ((*p_vector)[j].getCircleShape().getRadius() >= m_Length && (*h_vector)[i].getThirst() >= 0)
				{
					(*h_vector)[i].eatFood(&(*p_vector)[j], dt);
					(*h_vector)[i].setIsHungry(false);
				}
			}
			//Set found food parameter
			if (m_Flag == true)
			{
				(*h_vector)[i].setFoundFood(true);
			}
			else
			{
				(*h_vector)[i].setFoundFood(false);
			}

			//Set next position according to closest food source
			if ((*h_vector)[i].foundFood() && (*h_vector)[i].isHungry())
			{
				(*h_vector)[i].setNextPosition(m_ClosestResource->getPosition());
			}
		}
	}

	//Checking collision herbivore <-> carnivore
	if (!h_vector->empty() && !c_vector->empty())
	{
		bool m_Flag;
		m_ClosestEntityDistance = 4000;
		for (int i = 0; i <= h_vector->size() - 1; i++)
		{
			m_Flag = false;
			for (int j = 0; j <= c_vector->size() - 1; j++)
			{
				m_PositionVector.x = (*h_vector)[i].getPosition().x - (*c_vector)[j].getPosition().x;
				m_PositionVector.y = (*h_vector)[i].getPosition().y - (*c_vector)[j].getPosition().y;
				m_Length = sqrt(m_PositionVector.x * m_PositionVector.x + m_PositionVector.y * m_PositionVector.y);

				if (m_Length < m_ClosestEntityDistance)
				{
					m_ClosestEntity = &(*c_vector)[j];
					m_ClosestEntityDistance = m_Length;
					m_RelativePosition = m_PositionVector;
				}

				if ((*h_vector)[i].getCircleShape().getRadius() + (*c_vector)[j].getCircleShape().getRadius() >= m_Length)
				{
					m_Flag = true;
				}
			}
			//Set danger parameter
			if (m_Flag == true)
			{
				(*h_vector)[i].setIsInDanger(true);
			}
			else
			{
				(*h_vector)[i].setIsInDanger(false);
			}

			//Set next position according to closest danger source
			if ((*h_vector)[i].isInDanger())
			{
				/*m_RelativePosition.x = (int)m_RelativePosition.x % VideoMode::getDesktopMode().width;
				m_RelativePosition.y = (int)m_RelativePosition.x % VideoMode::getDesktopMode().height;*/
				(*h_vector)[i].setNextPosition((*h_vector)[i].getPosition() + m_RelativePosition);
			}
		}
	}
}
