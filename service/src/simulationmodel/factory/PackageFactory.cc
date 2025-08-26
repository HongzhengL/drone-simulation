#include "PackageFactory.h"

#include "BlueDecorator.h"
#include "GreenDecorator.h"
#include "RedDecorator.h"

IEntity *PackageFactory::createEntity(const JsonObject &entity) {
	std::string type = entity["type"];
	if (type.compare("package") == 0) {
		std::cout << "Package Created" << std::endl;
		Package *p = new Package(entity);
		auto range = rand() % 6;  // more colors!!!
		for (int i = 0; i < range; i++) {
			switch (rand() % 3) {
				case 0:
					p = new RedDecorator(p);
					break;
				case 1:
					p = new GreenDecorator(p);
					break;
				case 2:
					p = new BlueDecorator(p);
					break;
			}
		}
		return p;
	}
	return nullptr;
}
