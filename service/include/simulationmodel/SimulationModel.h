#ifndef SIMULATION_MODEL_H_
#define SIMULATION_MODEL_H_

#include <deque>
#include <map>
#include <set>

#include "CompositeFactory.h"
#include "Drone.h"
#include "Graph.h"
#include "IController.h"
#include "IEntity.h"
#include "IObserver.h"
#include "MultiDeliveryDecorator.h"
#include "POI.h"
#include "Robot.h"

class POI;
class MultiDeliveryDecorator;

//--------------------  Model ----------------------------

/// Simulation Model handling the transit simulation.  The model can communicate
/// with the controller.
/**
 * @class SimulationModel
 * @brief Class SimulationModel handling the transit simulation. it can
 * communicate with the controller
 **/
class SimulationModel : public IObserver {
   public:
	/**
	 * @brief Default constructor that create the SimulationModel object
	 * @param controller The specified Controller to be initialized in the model
	 **/
	SimulationModel(IController &controller);

	/**
	 * @brief Destructor
	 */
	~SimulationModel();

	/**
	 * @brief Set the Graph for the SimulationModel
	 * @param graph Type Graph* contain the new graph for SimulationModel
	 **/
	void setGraph(const routing::Graph *graph);

	/**
	 * @brief Creates a new simulation entity
	 * @param entity Type JsonObject contain the entity's reference to decide
	 *which entity to create
	 **/
	IEntity *createEntity(const JsonObject &entity);

	/**
	 * @brief Removes entity with given ID from the simulation
	 *
	 * @param id of the entity to be removed
	 */
	void removeEntity(int id);

	/**
	 * @brief Schedule a trip for an object in the scene
	 * @param detail Type JsonObject contain the entity's reference to schedule
	 *the detail of the trip being scheduled
	 **/
	void scheduleTrip(const JsonObject &details);

	/**
	 * @brief Update the simulation
	 * @param dt Type double comodel.reRouteClose();ntain the time since update was last called.
	 **/
	void update(double dt);

	/**
	 * @brief Stops the simulation
	 * @return Void
	 **/
	void stop();

	/**
	 * @brief Returns the graph of the map
	 *
	 * @returns Graph* graph pointer
	 */
	const routing::Graph *getGraph() const;

	/**
	 * @brief Notifies observer with specific message
	 *
	 * @param message The specific message
	 */
	void notify(const std::string &message) const;

	/**
	 * @brief Get all the Recharge Station positions
	 *
	 * @return std::vector<Vector3> a vector of recharge station positions
	 */
	std::vector<Vector3> getRechargeStations() const;

	/**
	 * @brief add a recharge station position to the list
	 *        mainly used by recharge drones when they arrive
	 *        near the dead drone
	 *
	 * @param station position of the recharge station to be added
	 */
	void addRechargeStation(Vector3 station);

	/**
	 * @brief remove a recharge station position from the list
	 *        mainly used by recharge drones when they leave
	 *        after dead drone is fully charged
	 *
	 * @param station position of the recharge station to be removed
	 */
	void removeRechargeStation(Vector3 station);

	std::deque<Package *> scheduledDeliveries;

	std::deque<Drone *> deadDrones;

	std::deque<Drone *> functionalDrones;

	std::deque<Drone *> chargingDrones;

	IController &controller;

	std::vector<POI *> pois;

	std::vector<MultiDeliveryDecorator *> drones;

   protected:
	// Keeps track of all pois and drones in the simulation
	std::map<int, IEntity *> entities;
	std::set<int> removed;
	/**
	 * @brief Removes the model from the simulation
	 * @param id The id of the model to be removed
	 */
	void removeFromSim(int id);
	const routing::Graph *graph = nullptr;
	CompositeFactory entityFactory;
	std::vector<Vector3> rechargeStations;
};

#endif
