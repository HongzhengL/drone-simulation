#ifndef ENTITY_H_
#define ENTITY_H_

#include <vector>

#include "Graph.h"
#include "IPublisher.h"
#include "math/vector3.h"
#include "util/json.h"

class SimulationModel;

/**
 * @class IEntity
 * @brief Represents an entity in a physical system.
 *
 * An IEntity object has a unique ID, a position, a direction, a destination,
 * and details. It also has a speed, which determines how fast the entity moves
 * in the physical system. Subclasses of IEntity can override the `Update`
 * function to implement their own movement behavior.
 */
class IEntity : public IPublisher {
   public:
	/**
	 * @brief Constructor that assigns a unique ID to the entity.
	 */
	IEntity();

	/**
	 * @brief Constructor with JsonObject details to define the entity
	 * @param details The JsonObject to define the entity
	 */
	IEntity(const JsonObject &details);

	/**
	 * @brief Virtual destructor for IEntity.
	 */
	virtual ~IEntity();

	/**
	 * @brief Links this entity to a simulation model,
	 * giving it access to the model's public variables
	 * and functions.
	 * @param[in] model The simulation model to link.
	 */
	virtual void linkModel(SimulationModel *model);

	/**
	 * @brief Gets the ID of the entity.
	 * @return The ID of the entity.
	 */
	virtual int getId() const;

	/**
	 * @brief Gets the position of the entity.
	 * @return The position of the entity.
	 */
	virtual Vector3 getPosition() const;

	/**
	 * @brief Gets the direction of the entity.
	 * @return The direction of the entity.
	 */
	virtual Vector3 getDirection() const;

	/**
	 * @brief Gets the details of the entity.
	 * @return The details of the entity.
	 */
	virtual const JsonObject &getDetails() const;

	/**
	 * @brief Gets the color of the entity
	 * @return The color of the entity
	 */
	virtual std::string getColor() const;

	/**
	 * @brief Gets the name of the entity
	 * @return The name of the entity
	 */
	virtual std::string getName() const;

	/**
	 * @brief Gets the speed of the entity.
	 * @return The speed of the entity.
	 */
	virtual double getSpeed() const;

	/**
	 * @brief Sets the position of the entity.
	 * @param pos_ The desired position of the entity.
	 */
	virtual void setPosition(Vector3 pos_);

	/**
	 *@brief Set the direction of the entity.
	 *@param dir_ The new direction of the entity.
	 */
	virtual void setDirection(Vector3 dir_);

	/**
	 * @brief Sets the color of the entity
	 * @param col_ The new color of the entity
	 */
	virtual void setColor(std::string col_);

	/**
	 * @brief Rotate the entity around y axis.
	 * @param angle The angle to rotate the entity by.
	 */
	virtual void rotate(double angle);

	/**
	 * @brief Updates the entity's position in the physical system.
	 * @param dt The time step of the update.
	 */
	virtual void update(double dt) = 0;

	virtual SimulationModel *getModel() const;

   protected:
	SimulationModel *model = nullptr;
	int id = -1;
	JsonObject details;
	Vector3 position;
	Vector3 direction;
	std::string color;
	std::string name;
	double speed = 0;
};

#endif
