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
	//Getting sizes of every vector
	m_cVectorSize = c_vector->size();
	m_hVectorSize = h_vector->size();
	m_wVectorSize = w_vector->size();
	m_pVectorSize = p_vector->size();

	/*HERBIVORE LOGIC*/
	//Checking collision herbivore <-> water
	if (!h_vector->empty() && !w_vector->empty())
	{
		bool m_Flag;
		m_ClosestResourceDistance = 4000;
		for (int i = 0; i <= m_hVectorSize - 1; i++)
		{
			m_Flag = false;
			for (int j = 0; j <= m_wVectorSize - 1; j++)
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
		for (int i = 0; i <= m_hVectorSize - 1; i++)
		{
			m_Flag = false;
			for (int j = 0; j <= m_pVectorSize - 1; j++)
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
				if ((*p_vector)[j].getCircleShape().getRadius() >= m_Length && (*h_vector)[i].getHunger() >= 0)
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
		for (int i = 0; i <= m_hVectorSize - 1; i++)
		{
			m_Flag = false;
			for (int j = 0; j <= m_cVectorSize - 1; j++)
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
				(*h_vector)[i].setNextPosition((*h_vector)[i].getPosition() + m_RelativePosition);
			}
		}
	}
	else if (!h_vector->empty() && c_vector->empty())
	{
		for (int i = 0; i <= m_hVectorSize - 1; i++)
		{
			(*h_vector)[i].setIsInDanger(false);
		}
	}

	/*CARNIVORE LOGIC*/
	//Checking collision carnivore <-> water
	if (!c_vector->empty() && !w_vector->empty())
	{
		bool m_Flag;
		m_ClosestResourceDistance = 4000;
		for (int i = 0; i <= m_cVectorSize - 1; i++)
		{
			m_Flag = false;
			for (int j = 0; j <= m_wVectorSize - 1; j++)
			{
				m_PositionVector.x = (*c_vector)[i].getPosition().x - (*w_vector)[j].getPosition().x;
				m_PositionVector.y = (*c_vector)[i].getPosition().y - (*w_vector)[j].getPosition().y;
				m_Length = sqrt(m_PositionVector.x * m_PositionVector.x + m_PositionVector.y * m_PositionVector.y);

				if (m_Length < m_ClosestResourceDistance)
				{
					m_ClosestResource = &(*w_vector)[j];
					m_ClosestResourceDistance = m_Length;
				}

				if ((*c_vector)[i].getCircleShape().getRadius() + (*w_vector)[j].getCircleShape().getRadius() >= m_Length)
				{
					m_Flag = true;
				}

				//Handle drinking water
				if ((*w_vector)[j].getCircleShape().getRadius() >= m_Length && (*c_vector)[i].getThirst() >= 0)
				{
					(*c_vector)[i].drinkWater(&(*w_vector)[j], dt);
					(*c_vector)[i].setIsThirsty(false);
				}
			}
			//Set found water parameter
			if (m_Flag == true)
			{
				(*c_vector)[i].setFoundWater(true);
			}
			else
			{
				(*c_vector)[i].setFoundWater(false);
			}

			//Set next position according to closest water source
			if ((*c_vector)[i].foundWater() && (*c_vector)[i].isThirsty())
			{
				(*c_vector)[i].setNextPosition(m_ClosestResource->getPosition());
			}
		}
	}

	//Checking collision carnivore <-> herbivore
	if (!c_vector->empty() && !h_vector->empty())
	{
		bool m_Flag;
		m_ClosestEntityDistance = 4000;
		for (int i = 0; i <= m_cVectorSize - 1; i++)
		{
			m_Flag = false;
			for (int j = 0; j <= m_hVectorSize - 1; j++)
			{
				m_PositionVector.x = (*c_vector)[i].getPosition().x - (*h_vector)[j].getPosition().x;
				m_PositionVector.y = (*c_vector)[i].getPosition().y - (*h_vector)[j].getPosition().y;
				m_Length = sqrt(m_PositionVector.x * m_PositionVector.x + m_PositionVector.y * m_PositionVector.y);

				if (m_Length < m_ClosestEntityDistance)
				{
					m_ClosestEntity = &(*h_vector)[j];
					m_ClosestEntityDistance = m_Length;
					m_RelativePosition = m_PositionVector;
				}

				if ((*c_vector)[i].getCircleShape().getRadius() + (*h_vector)[j].getCircleShape().getRadius() >= m_Length)
				{
					m_Flag = true;
				}

				if ((*h_vector)[j].getCircleShape().getRadius() / 10 >= m_Length && (*c_vector)[i].getHunger() >= 0)
				{
					(*c_vector)[i].eatFood(&(*h_vector)[j], dt);
					(*c_vector)[i].setIsHungry(false);
				}
			}
			//Set hunting parameter
			if (m_Flag == true)
			{
				(*c_vector)[i].setIsHunting(true);
			}
			else
			{
				(*c_vector)[i].setIsHunting(false);
			}

			//Set next position according to closest herbivore
			if ((*c_vector)[i].isHunting() && (*c_vector)[i].isHungry())
			{
				(*c_vector)[i].setNextPosition(m_ClosestEntity->getPosition());
			}
		}
	}
}
