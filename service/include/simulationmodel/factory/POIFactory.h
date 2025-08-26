#ifndef POI_FACTORY_H_
#define POI_FACTORY_H_

#include <vector>

#include "IEntityFactory.h"
#include "POI.h"

/**
 * @class POIFactory
 * @brief POI Factory to produce POI class.
 **/
class POIFactory : public IEntityFactory {
   public:
	/**
	 * @brief Destructor for POIFactory class.
	 **/
	virtual ~POIFactory() {
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
