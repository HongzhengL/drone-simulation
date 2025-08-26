#include "PackageColorDecorator.h"

PackageColorDecorator::PackageColorDecorator(Package *p, double h, double s, double l)
    : PackageDecorator(p), hue(h), saturation(s), light(l) {
}

std::string PackageColorDecorator::getColor() const {
	auto sub_color = sub->getColor();
	double h, s, l;
	auto format = "hsl(%lf, %lf%%, %lf%%)";
	if (sscanf(sub_color.c_str(), format, &h, &s, &l) == 3) {
		h = (hue + h + 360 * (abs(hue - h) > 180)) / 2;
		if (h > 360) h -= 360;
		s = (saturation + s) / 2;
		l = (light + l) / 2;
	} else {
		h = hue;
		s = saturation;
		l = light;
	}
	char color[100];
	snprintf(color, sizeof(color), format, h, s, l);
	return color;
}
