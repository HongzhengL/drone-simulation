#ifndef JUMP_DECORATOR_H_
#define JUMP_DECORATOR_H_

#include "ICelebrationDecorator.h"

/**
 * @class JumpDecorator
 * @brief this class inhertis from the IStrategy class and is represents
 * a celebration decorator where the entity will celebrate according to it.
 */
class JumpDecorator : public ICelebrationDecorator {
   public:
	/**
	 * @brief Construct a new Jump Decorator object
	 *
	 * @param[in] strategy the strategy to decorate onto
	 * @param[in] time how long to celebrate
	 * @param[in] jumpHeight how far up to jump
	 */
	JumpDecorator(IStrategy *strategy, double time = 4, double jumpHeight = 10);

	/**
	 * @brief Make the entity celebrate with the jump behavior.
	 *
	 * @param entity Entity to celebrate
	 * @param dt Delta Time
	 */
	void celebrate(IEntity *entity, double dt);

   private:
	double jumpHeight = 10;
	bool up = true;
	double h = 0;
};

#endif  // JUMP_DECORATOR_H_
