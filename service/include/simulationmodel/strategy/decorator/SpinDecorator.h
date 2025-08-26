#ifndef SPIN_DECORATOR_H_
#define SPIN_DECORATOR_H_

#include "ICelebrationDecorator.h"

/**
 * @class SpinDecorator
 * @brief this class inhertis from the IStrategy class and is represents
 * a celebration decorator where the entity will celebrate according to it.
 */
class SpinDecorator : public ICelebrationDecorator {
   public:
	/**
	 * @brief Construct a new Spin Decorator object
	 *
	 * @param[in] strategy the strategy to decorate onto
	 * @param[in] time how long to celebrate
	 * @param[in] spinSpeed multiplier for how fast to spin
	 */
	SpinDecorator(IStrategy *strategy, double time = 4, double spinSpeed = 1);

	/**
	 * @brief Move the entity with the spin behavior for 4 seconds.
	 *
	 * @param entity Entity to move
	 * @param dt Delta Time
	 */
	void celebrate(IEntity *entity, double dt);

   private:
	double spinSpeed = 1;
};

#endif  // SPIN_DECORATOR_H_
