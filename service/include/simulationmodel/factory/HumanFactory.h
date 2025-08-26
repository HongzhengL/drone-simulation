#ifndef HUMAN_FACTORY_H_
#define HUMAN_FACTORY_H_

#include <vector>

#include "Human.h"
#include "IEntityFactory.h"

/**
 * @class HumanFactory
 * @brief Human Factory to produce Human class.
 **/
class HumanFactory : public IEntityFactory {
   public:
	/**
	 * @brief Destructor for HumanFactory class.
	 **/
	virtual ~HumanFactory() {
	}

	/**
	 * @brief Creates entity using the given JSON object, if possible.
	 * @param entity - JsonObject to be used to create the new entity.
	 * @return Entity that was created if it was created successfully, or a
	 *nullpointer if creation failed.
	 **/
	IEntity *createEntity(const JsonObject &entity);
};

#endif
