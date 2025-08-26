#ifndef BLUE_DECORATOR_H_
#define BLUE_DECORATOR_H_

#include "PackageColorDecorator.h"

/**
 * @class BlueDecorator
 * @brief Allows for the package to be colored blue
 */
class BlueDecorator : public PackageColorDecorator {
   public:
	/**
	 * @brief Constructor for BlueDecorator
	 * @param Package* Pointer to package to be colored blue
	 */
	BlueDecorator(Package *);
};

#endif  // BLUE_DECORATOR_H_
