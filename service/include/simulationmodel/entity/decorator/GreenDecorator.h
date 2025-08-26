#ifndef GREEN_DECORATOR_H_
#define GREEN_DECORATOR_H_

#include "PackageColorDecorator.h"

/**
 * @class GreenDecorator
 * @brief Allows for the package to be colored green
 */
class GreenDecorator : public PackageColorDecorator {
   public:
	/**
	 * @brief Constructor for GreenDecorator
	 * @param Package* Pointer to package to be colored green
	 */
	GreenDecorator(Package *);
};

#endif  // GREEN_DECORATOR_H_
