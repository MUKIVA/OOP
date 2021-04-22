#include "Car.h"

const int MAX_SPEED_INDEX = 1;
const int MIN_SPEED_INDEX = 0;

Car::Car()
	: m_speed(0)
	, m_engineCondition(false)
	, m_direction(0)
	, m_gear(0)
	, m_gearSpeedRange({ { -1, { 0, 20 } },
		  { 0, { 0, INT_MAX } },
		  { 1, { 0, 30 } },
		  { 2, { 20, 50 } },
		  { 3, { 30, 60 } },
		  { 4, { 40, 90 } },
		  { 5, { 50, 150 } } })
{
}

bool Car::IsTurnedOn() const
{
	if (m_engineCondition)
	{
		return true;
	}
	return false;
}

int Car::GetDirection() const
{
	return m_direction;
}

int Car::GetSpeed() const
{
	return m_speed;
}

int Car::GetGear() const
{
	return m_gear;
}

bool Car::TurnOnEngine()
{
	m_engineCondition = true;
	return true;
}

bool Car::TurnOffEngine()
{
	if (!m_engineCondition)
	{
		return true;
	}
	if (m_engineCondition && !m_direction && !m_gear)
	{
		m_engineCondition = false;
		return true;
	}
	return false;
}

bool SpeedInRange(int speed, int gear, std::map<int, std::array<int, 2>> range)
{
	return (speed <= range[gear][MAX_SPEED_INDEX]
			&& speed >= range[gear][MIN_SPEED_INDEX]);
}

bool Car::SetGear(int gear)
{
	if (!m_engineCondition)
	{
		return false;
	}
	if (m_gearSpeedRange.find(gear) != m_gearSpeedRange.end()
		&& SpeedInRange(m_speed, gear, m_gearSpeedRange))
	{
		m_gear = gear;
		return true;
	}
	return false;
}

bool Car::SetSpeed(int speed)
{
	if (!m_engineCondition
		|| speed < 0
		|| (!m_gear && speed > m_speed))
	{
		return false;
	}
	if (SpeedInRange(speed, m_gear, m_gearSpeedRange))
	{
		if (speed == 0)
		{
			m_direction = 0;
			m_speed = 0;
			return true;
		}
		if (m_speed == 0)
		{
			if (m_gear > 0)
			{
				m_direction = 1;
			}
			if (m_gear < 0)
			{
				m_direction = -1;
			}
		}
		m_speed = speed;
		return true;
	}
	return false;
}
