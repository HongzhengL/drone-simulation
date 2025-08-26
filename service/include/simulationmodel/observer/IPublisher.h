#ifndef IPUBLISHER_H_
#define IPUBLISHER_H_

#include <set>
#include <string>

#include "IObserver.h"

/**
 * @class IPublisher
 * @brief Interface for Publisher
 */
class IPublisher {
   public:
	/**
	 * @brief adds an observer to the simulation
	 * @param o The pointer to the specific observer
	 */
	void addObserver(const IObserver *o);

	/**
	 * @brief removes an observer in the simulation
	 * @param o The pointer to the specific observer
	 */
	void removeObserver(const IObserver *o);

	/**
	 * @brief notifies all observers with a specific message
	 * @param message The specific message
	 */
	void notifyObservers(const std::string &message) const;

   private:
	std::set<const IObserver *> observers;
};

#endif  // IPUBLISHER_H_
