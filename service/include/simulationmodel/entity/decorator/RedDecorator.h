#ifndef RED_DECORATOR_H_
#define RED_DECORATOR_H_

#include "PackageColorDecorator.h"

/**
 * @class RedDecorator
 * @brief Allows for the package to be colored red
 */
class RedDecorator : public PackageColorDecorator {
   public:
	/**
	 * @brief Constructor for RedDecorator
	 * @param Package* Pointer to package to be colored red
	 */
	RedDecorator(Package *);
};

#endif  // RED_DECORATOR_H_
