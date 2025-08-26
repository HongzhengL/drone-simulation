#ifndef PACKAGE_H
#define PACKAGE_H

#include <vector>

#include "IEntity.h"
#include "math/vector3.h"
#include "util/json.h"

class Robot;

/**
 * @class Package
 * @brief Represents a package in a physical system. Packages move using euler
 * integration based on a specified velocity and direction.
 */
class Package : public IEntity {
   public:
	/**
	 * @brief Constructor
	 * @param obj JSON object containing the package's information
	 */
	Package(const JsonObject &obj);

	/**
	 * @brief Gets the Package's destination
	 * @return The Package's destination
	 */
	virtual Vector3 getDestination() const;

	/**
	 * @brief Returns the name of the strategy for this package
	 *
	 * @returns String name of strategy
	 */
	virtual std::string getStrategyName() const;

	/**
	 * @brief Returns the owner of the package
	 *
	 * @return pointer to Robot owning the package
	 */
	virtual Robot *getOwner() const;

	/**
	 * @brief Returns whether or not the package needs to be delivered
	 *
	 * @return boolean value of the above statement
	 */
	virtual bool requiresDelivery() const;

	/**
	 * @brief Set the Strategy Name
	 *
	 * @param strategyName_ Strategy name
	 */
	virtual void setStrategyName(std::string strategyName_);

	/**
	 * @brief Updates the Package
	 *
	 * @param dt difference in time since last update
	 */
	virtual void update(double dt);

	/**
	 * @brief Sets the attributes for delivery
	 *
	 * @param owner Robot for the package to be delivered to
	 */
	virtual void initDelivery(Robot *owner);

	/**
	 * @brief Gives the robot/owner this package
	 */
	virtual void handOff();

   protected:
	bool requiresDelivery_ = true;
	Vector3 destination;
	std::string strategyName;
	Robot *owner = nullptr;
};

#endif  // PACKAGE_H
