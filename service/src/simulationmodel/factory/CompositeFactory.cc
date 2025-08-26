#include "CompositeFactory.h"

IEntity *CompositeFactory::createEntity(const JsonObject &entity) {
	for (int i = 0; i < componentFactories.size(); i++) {
		IEntity *createdEntity = componentFactories.at(i)->createEntity(entity);
		if (createdEntity != nullptr) {
			return createdEntity;
		}
	}
	std::cout << "[!] Error: Type mismatched..." << std::endl;
	return nullptr;
}

void CompositeFactory::addFactory(IEntityFactory *factoryEntity) {
	componentFactories.push_back(factoryEntity);
}

CompositeFactory::~CompositeFactory() {
	for (int i = 0; i < componentFactories.size(); i++) {
		delete componentFactories[i];
	}
}
