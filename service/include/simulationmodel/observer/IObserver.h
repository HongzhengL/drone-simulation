#ifndef IOBSERVER_H_
#define IOBSERVER_H_

#include <string>

/**
 * @class IObserver
 * @brief Interface for Observer
 */
class IObserver {
   public:
	/**
	 * @brief Notifies observer with specific message
	 * @param message The specific message
	 */
	virtual void notify(const std::string &message) const = 0;
};

#endif  // IOBSERVER_H_
