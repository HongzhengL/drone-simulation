#include "IPublisher.h"

void IPublisher::addObserver(const IObserver *o) {
	observers.insert(o);
}

void IPublisher::removeObserver(const IObserver *o) {
	observers.erase(o);
}

void IPublisher::notifyObservers(const std::string &message) const {
	for (auto &o : observers) o->notify(message);
}
