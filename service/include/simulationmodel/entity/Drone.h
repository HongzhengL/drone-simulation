#ifndef DRONE_H_
#define DRONE_H_

#include <vector>

#include "IEntity.h"
#include "IStrategy.h"
#include "Package.h"
#include "PathStrategy.h"
#include "math/vector3.h"

class Package;

/**
 * @class Drone
 * @brief Represents a drone in a physical system. Drones move using euler
 * integration based on a specified velocity and direction.
 */
class Drone : public IEntity {
   public:
	/**
	 * @brief Drones are created with a name
	 * @param obj JSON object containing the drone's information
	 */
	Drone(const JsonObject &obj);

	/**
	 * @brief Destructor
	 */
	~Drone();

	/**
	 * @brief Gets the next delivery in the scheduler
	 */
	void getNextDelivery();

	/**
	 * @brief Gets the pickedUp status of the Drone object
	 */
	bool getPickedUp() {
		return pickedUp;
	}

	/**
	 * @brief Gets pointer to the Drone's package
	 */
	Package *getPackage() {
		return package;
	}

	/**
	 * @brief Returns pointer to toFinalDestination
	 */
	IStrategy *getFinalStrategy() {
		return toFinalDestination;
	}

	/**
	 * @brief Updates the drone's position
	 * @param dt Delta time
	 */
	void update(double dt);

	/**
	 * @brief Removing the copy constructor operator
	 * so that drones cannot be copied.
	 */
	Drone(const Drone &drone) = delete;

	/**
	 * @brief Removing the assignment operator
	 * so that drones cannot be copied.
	 */
	Drone &operator=(const Drone &drone) = delete;

	/**
	 * @brief Getter method for toPackage
	 */
	virtual IStrategy *getToPackageStrategy();

	/**
	 * @brief Getter method for toFinalDestination
	 */
	virtual IStrategy *getToFinalDestinationStrategy();

	/**
	 * @brief Checks if drone is available for a delivery
	 * @return true if drone is available, false otherwise
	 */
	bool isAvailable();

	/**
	 * @brief Checks if drone is currently picked up
	 * @return true if drone is picked upp, false otherwise
	 */
	bool isPickedUp();

	/**
	 * @brief Sets the Drone's toPackage strategy to a new one
	 * @param s New strategy for drone to get to package
	 */
	void setToPackage(IStrategy *s) {
		toPackage = s;
	}

   private:
	bool available = false;
	bool pickedUp = false;
	Package *package = nullptr;
	IStrategy *toPackage = nullptr;
	IStrategy *toFinalDestination = nullptr;
	int portionNum = 1;
};

#endif
