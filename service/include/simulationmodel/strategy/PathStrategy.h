#ifndef PATH_STRATEGY_H_
#define PATH_STRATEGY_H_

#include "IStrategy.h"

/**
 * @class PathStrategy
 * @brief this class inhertis from the IStrategy class and is represents
 * a movement strategy where the entity simply moves along the given path
 */
class PathStrategy : public IStrategy {
   protected:
	std::vector<Vector3> path;
	int index;

   public:
	/**
	 * @brief Construct a new PathStrategy Strategy object
	 *
	 * @param path the path to follow
	 */
	PathStrategy(std::vector<Vector3> path = {});

	/**
	 * @brief Move toward next position in the path
	 *
	 * @param entity Entity to move
	 * @param dt Delta Time
	 */
	virtual void move(IEntity *entity, double dt);

	/**
	 * @brief Check if the trip is completed by seeing if index
	 *        has reached the end of the path
	 *
	 * @return True if complete, false if not complete
	 */
	virtual bool isCompleted();

	/**
	 * @brief Get the total distance of the entire path starting from startPosition
	 *        and the current index
	 *
	 * @return float of total distance to final destination of this path
	 *         starting from startPosition and the current index
	 */
	double currentPathDistance(Vector3 startPosition);

	/**
	 * @brief Get the total distance of the entire path starting from startPosition
	 *        and index 0
	 *
	 * @return double of total distance to final destination of this path
	 *         starting from startPosition
	 */
	double totalPathDistance(Vector3 startPosition);
};

#endif  // PATH_STRATEGY_H_
