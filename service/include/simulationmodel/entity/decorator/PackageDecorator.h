#ifndef PACKAGE_DECORATOR_H_
#define PACKAGE_DECORATOR_H_

#include "IEntityDecorator.h"
#include "Package.h"
#include "Robot.h"

/**
 * @class PackageDecorator
 * @brief Base class decorator for Package that implements IEntityDecorator Package template,
 * delegates all work to wrapped Package class
 */
class PackageDecorator : public IEntityDecorator<Package> {
   public:
	/**
	 * @brief Constructor for PackageDecorator, calls IEntityDecorator constructor
	 * @param p The pointer to the package object to be wrapped
	 */
	PackageDecorator(Package *p) : IEntityDecorator(p) {
	}

	/**
	 * @brief Gets the Package's destination
	 * @return The Package's destination
	 */
	virtual Vector3 getDestination() const {
		return sub->getDestination();
	}

	/**
	 * @brief Returns the name of the strategy for this package
	 *
	 * @returns String name of strategy
	 */
	virtual std::string getStrategyName() const {
		return sub->getStrategyName();
	}

	/**
	 * @brief Returns the owner of the package
	 *
	 * @return pointer to Robot owning the package
	 */
	virtual Robot *getOwner() const {
		return sub->getOwner();
	}

	/**
	 * @brief Returns whether or not the package needs to be delivered
	 *
	 * @return boolean value of the above statement
	 */
	virtual bool requiresDelivery() const {
		return sub->requiresDelivery();
	}

	/**
	 * @brief Set the Strategy Name
	 *
	 * @param strategyName_ Strategy name
	 */
	virtual void setStrategyName(std::string strategyName_) {
		return sub->setStrategyName(strategyName_);
	}

	/**
	 * @brief Sets the attributes for delivery
	 *
	 * @param owner Robot for the package to be delivered to
	 */
	virtual void initDelivery(Robot *owner) {
		return sub->initDelivery(owner);
	}

	/**
	 * @brief Gives the robot/owner this package
	 */
	virtual void handOff() {
		if (getOwner()) getOwner()->receive(this);
	}
};

#endif
