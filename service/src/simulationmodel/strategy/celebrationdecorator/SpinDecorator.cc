#include "SpinDecorator.h"

SpinDecorator::SpinDecorator(IStrategy *strategy, double time, double spinSpeed)
    : ICelebrationDecorator(strategy, time), spinSpeed(spinSpeed) {
}

void SpinDecorator::celebrate(IEntity *entity, double dt) {
	entity->rotate(dt * entity->getSpeed() * spinSpeed);
}
