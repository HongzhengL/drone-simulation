#ifndef PACKAGE_COLOR_DECORATOR_H_
#define PACKAGE_COLOR_DECORATOR_H_

#include "PackageDecorator.h"

/**
 * @class PackageColorDecorator
 * @brief Decorator allowing for packages to become colored in different combinations of colors, inherits from
 * PackageDecorator
 */
class PackageColorDecorator : public PackageDecorator {
   private:
	double hue = 0;
	double saturation = 0;
	double light = 0;

   public:
	/**
	 * @brief Constructor for PackageColorDecorator, calls PackageDecorator constructor
	 * @param Package* Pointer to package to be colored with a specific color
	 * @param double Hue value
	 * @param double Saturation value
	 * @param double Light value
	 */
	PackageColorDecorator(Package *, double = 0, double = 0, double = 0);
	/**
	 * @brief Gets the package's color
	 */
	std::string getColor() const;
};

#endif  // PACKAGE_COLOR_DECORATOR_H_
