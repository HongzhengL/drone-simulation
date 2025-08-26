#ifndef I_STRATEGY_H_
#define I_STRATEGY_H_

#include "IEntity.h"

/**
 * @class IStrategy
 * @brief Strategy interface
 *
 */
class IStrategy {
   public:
	/**
	 * @brief Destructor
	 */
	virtual ~IStrategy() {
	}

	/**
	 * @brief Move toward next position
	 *
	 * @param entity Entity to move
	 * @param dt Delta Time
	 */
	virtual void move(IEntity *entity, double dt) = 0;

	/**
	 * @brief Check if the trip is completed
	 *
	 * @return True if complete, false if not complete
	 */
	virtual bool isCompleted() = 0;

	/**
	 * @brief Get the current distance of the entire path starting from startPosition
	 *        and the current index
	 *
	 * @return double of current distance to final destination of this path
	 *         starting from startPosition and the current index
	 */

	virtual double currentPathDistance(Vector3 startPosition) {
		return 0;
	}

	/**
	 * @brief Get the total distance of the entire path starting from startPosition
	 *        and index 0
	 *
	 * @return double of total distance to final destination of this path
	 *         starting from startPosition
	 */

	virtual double totalPathDistance(Vector3 startPosition) {
		return 0;
	}
};

#endif
