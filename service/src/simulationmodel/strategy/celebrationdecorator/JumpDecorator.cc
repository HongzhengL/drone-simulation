#include "JumpDecorator.h"

JumpDecorator::JumpDecorator(IStrategy *strategy, double time, double jumpHeight)
    : ICelebrationDecorator(strategy, time), jumpHeight(jumpHeight) {
}

void JumpDecorator::celebrate(IEntity *entity, double dt) {
	Vector3 step(0, entity->getSpeed() * dt, 0);
	if (up) {
		h += step.y;
		entity->setPosition(entity->getPosition() + step);
		if (h >= jumpHeight) up = false;
	} else {
		h -= step.y;
		entity->setPosition(entity->getPosition() - step);
		if (h <= 0) up = true;
	}
}
