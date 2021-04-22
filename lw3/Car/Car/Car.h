#include <map>
#include <array>

const int MIN_GEAR = -1;
const int MAX_GEAR = 5;

class Car
{

public:
	Car();
	bool IsTurnedOn() const;
	int GetDirection() const;
	int GetSpeed() const;
	int GetGear() const;
	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int gear);
	bool SetSpeed(int speed);

private:
	int m_gear;
	bool m_engineCondition;
	int m_direction;
	std::map<int, std::array<int, 2>> m_gearSpeedRange;
	int m_speed;

};
