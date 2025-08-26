#ifndef DRONE_DECORATOR_H_
#define DRONE_DECORATOR_H_

#include "Drone.h"
#include "IEntityDecorator.h"
#include "PathStrategy.h"

/**
 * @class DroneDecorator
 * @brief Base class decorator for Drone that implements IEntityDecorator Drone template,
 * delegates all work to wrapped Drone class
 */
class DroneDecorator : public IEntityDecorator<Drone> {
   public:
	/**
	 * @brief Constructor for DroneDecorator, calls IEntityDecorator constructor
	 * @param d The pointer to the drone object to be wrapped
	 */
	DroneDecorator(Drone *d) : IEntityDecorator(d) {
	}

	/**
	 * @brief Destructor
	 */
	virtual ~DroneDecorator() {
	}

	/**
	 * @brief Gets the next delivery in the scheduler
	 */
	virtual void getNextDelivery() const {
		return sub->getNextDelivery();
	}

	/**
	 * @brief Gets the pickedUp status of the Drone object
	 */
	virtual bool getPickedUp() const {
		return sub->getPickedUp();
	}

	/**
	 * @brief Gets pointer to the Drone's package
	 */
	virtual Package *getPackage() const {
		return sub->getPackage();
	}

	/**
	 * @brief Returns pointer to toFinalDestination
	 */
	virtual IStrategy *getFinalStrategy() const {
		return sub->getFinalStrategy();
	}

	/**
	 * @brief Sets the Drone's toPackage strategy to a new one
	 * @param s New strategy for drone to get to package
	 */
	virtual void setToPackage(IStrategy *s) const {
		return sub->setToPackage(s);
	}

	/**
	 * @brief Updates the drone's position
	 *
	 * @param dt Delta time
	 */
	virtual void update(double dt) {
		return sub->update(dt);
	}

	/**
	 * @brief Get the Model object
	 *
	 * @return SimulationModel* Simulation model where holds the drones and
	 *                          other entities
	 */
	virtual SimulationModel *getModel() const {
		return sub->getModel();
	}

	/**
	 * @brief Get the To Final Destination Strategy object
	 *
	 * @return IStrategy* to final destination strategy of the drone
	 */
	IStrategy *getToFinalDestinationStrategy() {
		return sub->getToFinalDestinationStrategy();
	}

	/**
	 * @brief Get the To Package Strategy object
	 *
	 * @return IStrategy* to package strategy of the drone
	 */
	IStrategy *getToPackageStrategy() {
		return sub->getToPackageStrategy();
	}
};

#endif
