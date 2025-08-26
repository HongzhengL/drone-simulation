#ifndef CELEBRATION_DECORATOR_H_
#define CELEBRATION_DECORATOR_H_

#include "IStrategy.h"

/**
 * @class ICelebrationDecorator
 * @brief this class inhertis from the IStrategy class and is represents
 * a celebration decorator where the entity will celebrate according to it.
 */
class ICelebrationDecorator : public IStrategy {
   protected:
	IStrategy *strategy = nullptr;
	float time = 0;

   public:
	/**
	 * @brief Construct a new Celebration Decorator object
	 *
	 * @param[in] strategy the strategy to decorate onto
	 * @param[in] time how long to celebrate
	 */
	ICelebrationDecorator(IStrategy *strategy, double time = 4);

	/**
	 * @brief Celebration Destructor
	 */
	virtual ~ICelebrationDecorator();

	/**
	 * @brief Move the entity with the behavior as described for 4 seconds.
	 *
	 * @param entity Entity to move
	 * @param dt Delta Time
	 */
	virtual void move(IEntity *entity, double dt);

	/**
	 * @brief Check if the movement is completed by checking the time.
	 *
	 * @return True if complete, false if not complete
	 */
	virtual bool isCompleted();

	/**
	 * @brief Make the entity celebrate.
	 *
	 * @param entity Entity to celebrate
	 * @param dt Delta Time
	 */
	virtual void celebrate(IEntity *entity, double dt) = 0;

	double currentPathDistance(Vector3 startPosition);

	double totalPathDistance(Vector3 startPosition);
};

#endif  // CELEBRATION_DECORATOR_H_
