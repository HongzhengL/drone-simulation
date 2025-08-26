#ifndef MULTI_DELIVERY_DECORATOR_H_
#define MULTI_DELIVERY_DECORATOR_H_

#include "BeelineStrategy.h"
#include "Drone.h"
#include "DroneDecorator.h"
#include "Package.h"
#include "PathStrategy.h"
#include "SimulationModel.h"

/**
 * @class MultiDeliveryDecorator
 * @brief Decorator allowing for drones to make multiple deliveries, inherits from IObserver and DroneDecorator
 **/
class MultiDeliveryDecorator : public DroneDecorator, public IObserver {
   public:
	/**
	 * @brief Constructor
	 *
	 * @param Drone* Drone to add functionality onto
	 */
	MultiDeliveryDecorator(Drone *d);

	/**
	 * @brief Destructor
	 */
	~MultiDeliveryDecorator() {
	}

	/**
	 * @brief Updates the child drone's position
	 * @param dt Delta time
	 */
	void update(double dt) override;

	/**
	 * @brief Links decorator to simulation and stores pointer
	 * @param model Simulation model
	 */
	void linkModel(SimulationModel *model);

	/**
	 * @brief Pickups additional package if drone is in range
	 * @param d Location of POI to make pickup at
	 */
	void pickupAdditional(Vector3 d);

	/**
	 * @brief Stores additional packages to packages vector
	 */
	void storeAdditional();

	/**
	 * @brief Notifies observer with specific message
	 * @param message The specific message
	 */
	void notify(const std::string &message) const;

	// Position of the last POI visited by the drone
	Vector3 last = Vector3();

	// Whether user has been prompted for a POI yet
	bool prompted = false;

   private:
	// Locations of all pois on map
	std::vector<Vector3> pois;

	// All packages currently held by drone
	std::vector<Package *> packages;

	SimulationModel *m = nullptr;
	Package *extra_package = nullptr;
};

#endif  // MULTI_DELIVERY_DECORATOR_H_
