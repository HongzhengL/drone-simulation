/**
Copyright (c) 2019 Dan Orban
*/

#ifndef WEBSERVER_H_
#define WEBSERVER_H_

#include <map>
#include <string>
#include <vector>

#include "libwebsockets.h"
#include "libwebsockets/lws-service.h"

/**
 * @class WebServerBase
 * @brief Base class for web server implementation
 */
class WebServerBase {
   public:
	/**
	 * @brief Constructor for WebServerBase
	 * @param port The port on which the server will listen
	 * @param webDir The directory from which to serve web content
	 */
	WebServerBase(int port = 8081, const std::string &webDir = ".");

	/**
	 * @brief Destructor
	 */
	virtual ~WebServerBase();

	/**
	 * @class Session
	 * @brief Represents a session with a client
	 */
	class Session {
		friend class WebServerBase;

	   public:
		/**
		 * @brief Constructor for Session
		 */
		Session();

		/**
		 * @brief Destructor
		 */
		virtual ~Session();

		/**
		 * @brief Returns the ID of the session
		 */
		virtual int getId() const {
			return id;
		}

		/**
		 * @brief Receives a message from the client
		 * @param msg The message received from the client
		 */
		virtual void receiveMessage(const std::string &msg) {
		}

		/**
		 * @brief Sends a message to the client
		 * @param msg The message to send to the client
		 */
		virtual void sendMessage(const std::string &msg);

		/**
		 * @brief Performs any necessary updates for the session
		 */
		virtual void update() {
		}

		/**
		 * @brief Function called when the session is ready to write
		 */
		virtual void onWrite();

	   private:
		void *state;
		int id;
	};

	/**
	 * @brief Services the server, processing incoming requests
	 * @param time Time for which to service the server
	 */
	void service(int time = 10);

	/**
	 * @brief Creates a session for a new client connection
	 * @param info Pointer to information about the session
	 */
	virtual void createSession(void *info);

   protected:
	/**
	 * @brief Factory method to create a new session
	 */
	virtual Session *createSession() {
		return new Session();
	}

   public:
	lws_context *context = nullptr;
	std::vector<Session *> sessions;
	std::map<int, Session *> sessionMap;
	std::string webDir;
};

/**
 * @class WebServer
 * @brief Templated class for a basic web server that inherits from WebServerBase
 */
template <typename T>
class WebServer : public WebServerBase {
   public:
	/**
	 * @brief Constructor for WebServer that calls WebServerBase's constructor
	 * @param port The port on which the server will listen
	 * @param webDir The directory from which to serve web content
	 */
	WebServer(int port = 8081, const std::string &webDir = ".") : WebServerBase(port, webDir) {
	}

   protected:
	/**
	 * @brief Factory method to create a new session of type T
	 */
	Session *createSession() {
		return new T();
	}
};

/**
 * @class WebServerWithState
 * @brief Templated class for a web server with state that inherits from WebServerBase
 */
template <typename T, typename STATE>
class WebServerWithState : public WebServerBase {
   public:
	/**
	 * @brief Constructor for WebServerWithState that calls WebServerBase's constructor
	 * @param state The initial state of the server
	 * @param port The port on which the server will listen
	 * @param webDir The directory from which to serve web content
	 */
	WebServerWithState(STATE state, int port = 8081, const std::string &webDir = ".")
	    : WebServerBase(port, webDir), state(state) {
	}

   protected:
	/**
	 * @brief Factory method to create a new session of type T with the given state
	 */
	Session *createSession() {
		return new T(state);
	}

   private:
	STATE state;
};

// JSON support
#include "picojson.h"

/**
 * @class JSONSession
 * @brief Abstract class for a session supporting JSON communication
 */
class JSONSession : public WebServerBase::Session {
   public:
	/**
	 * @brief Receives a JSON message from the client
	 * @param val The JSON value received from the client
	 */
	virtual void receiveJSON(picojson::value &val) {
	}

	/**
	 * @brief Sends a JSON message to the client
	 * @param val The JSON value to send to the client
	 */
	virtual void sendJSON(picojson::value &val) {
		sendMessage(val.serialize());
	}

	/**
	 * @brief Receives a message from the client and parses it as JSON
	 * @param msg The message received from the client
	 */
	void receiveMessage(const std::string &msg) {
		static std::string buf = "";
		picojson::value val;
		std::string err = picojson::parse(val, msg);
		if (err.empty() && val.is<picojson::object>()) {
			buf = "";
			receiveJSON(val);
		} else {
			buf += msg;
			err = picojson::parse(val, buf);
			if (err.empty() && val.is<picojson::object>()) {
				buf = "";
				receiveJSON(val);
			}
		}
	}
};

#include "util/json.h"

/**
 * @class JsonSession
 * @brief Abstract class for a session supporting JSON communication with command handling, inherits from JSONSession
 */
class JsonSession : public JSONSession {
   public:
	/**
	 * @brief Receive a command from the web server
	 * @param val: the command (in JSON format)
	 */
	void receiveJSON(picojson::value &val) {
		JsonObject data = JsonValue(val);

		std::string cmd = data["command"];

		JsonObject returnValue;
		returnValue["id"] = data["id"];

		receiveCommand(cmd, data, returnValue);
		JsonValue retVal(returnValue);
		sendJSON(retVal.getValue());
	}

	/**
	 * @brief Handles specific commands from the web server
	 * @param cmd: command
	 * @param data: data (JSON)
	 * @param returnValue: return value (JSON) which will be sent back to the
	 * server
	 */
	virtual void receiveCommand(const std::string &cmd, const JsonObject &data, JsonObject &returnValue) = 0;
};

#endif  // WEBSERVER_H_
