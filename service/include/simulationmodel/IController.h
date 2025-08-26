#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "IEntity.h"
#include "util/json.h"

//--------------------  Controller Interface ----------------------------

/// Abstract controller class used in the Transit Service.  Uses the Model View
/// Controller Pattern
/**
 * @class IController
 * @brief class for IController used for transit service. Uses the Model View
 **/
class IController {
   public:
	/**
	 * @brief A destructor for IController
	 **/
	virtual ~IController() {
	}

	/**
	 * @brief Add the entity to the program
	 * @param entity Type IEntity contain entity object
	 **/
	virtual void addEntity(const IEntity &entity) = 0;

	/**
	 * @brief To update the entity information and add it to the program
	 * @param entity Type IEntity contain entity object
	 **/
	virtual void updateEntity(const IEntity &entity) = 0;

	/**
	 * @brief To remove the entity from the program
	 * @param id Type int contain the ID of the entity object
	 **/
	virtual void removeEntity(const IEntity &entity) = 0;

	/**
	 * @brief To allow message to be passed back to the view
	 * @param event Type string contain name of the event
	 * @param detail Type JsonObject contain the details of the event
	 **/
	virtual void sendEventToView(const std::string &event, const JsonObject &details) = 0;
};

#endif
