#include "Robot.h"

Robot::Robot(const JsonObject &obj) : IEntity(obj) {
}

void Robot::update(double dt) {
}

void Robot::receive(Package *p) {
	package = p;
}
