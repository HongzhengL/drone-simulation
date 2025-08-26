#ifndef Helicopter_H_
#define Helicopter_H_

#include "IEntity.h"
#include "IStrategy.h"

/**
 * @class Helicopter
 * @brief Represents a helicopter in a physical system. Helicopters move using euler
 * integration based on a specified velocity and direction.
 */
class Helicopter : public IEntity {
   public:
	/**
	 * @brief Helicopters are created with a name
	 * @param obj JSON object containing the helicopter's information
	 */
	Helicopter(const JsonObject &obj);

	/**
	 * @brief Destructor
	 */
	~Helicopter();

	/**
	 * @brief Updates the helicopter's position
	 * @param dt Delta time
	 */
	void update(double dt);

   private:
	IStrategy *movement = nullptr;
	double distanceTraveled = 0;
	unsigned int mileCounter = 0;
	Vector3 lastPosition;
};

#endif
