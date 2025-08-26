#ifndef POI_H
#define POI_H

#include "IEntity.h"
#include "MultiDeliveryDecorator.h"

class MultiDeliveryDecorator;

/**
 * @class POI
 * @brief Represents a point of interest in a physical
 * system. Drones are able to make pitstops at these
 * POIs if they are nearby.
 */
class POI : public IEntity {
   public:
	/**
	 * @brief Constructor
	 * @param obj JSON object containing the POI's information
	 */
	POI(const JsonObject &obj);

	/**
	 * @brief Constructor
	 * @param e MultiDeliveryDecorator associated with observer to POI
	 * @param o Observer object to POI
	 */
	void addEntityObserverCombo(MultiDeliveryDecorator *e, IObserver *o) {
		entity_observers[e] = o;
	}

	/**
	 * @brief Updates the POI, checks for proximity of observers
	 * @param dt difference in time since last update
	 */
	void update(double dt);

	/**
	 * @brief Prompts the user to make an additional stop
	 * @param d Drone that can be rerouted to POI
	 */
	void promptUser(MultiDeliveryDecorator *d);

	/**
	 * @brief Facilitates drone pitstop at POI
	 * @param d Drone that reroutes to POI
	 */
	void pitStopHere(MultiDeliveryDecorator *d);

   private:
	// Stores pair of drones and their accompanying observe models
	std::map<MultiDeliveryDecorator *, IObserver *> entity_observers;
};

#endif  // POI_H
