#ifndef __rf24com_tunnel_H__
#define __rf24com_tunnel_H__

#include <RF24.h>
#include "rf24com_object.h"

namespace RF24Com 
{

class Tunnel
{
	public:
		Tunnel( RF24 &rf24, const uint8_t *txPipe, const uint8_t *rxPipe, uint8_t channel = 120 );
		
		bool begin();

		inline bool isReady() const;
		inline void setPALevel( uint8_t level );

		inline unsigned long timeOut() const;
		inline void setTimeOut( unsigned long timeOut );

		bool sendObject( const Object &obj ) const;
		bool getObject( Object &obj ) const;

		//	----- advanced functions -----
		bool sendAndReceive( const Object &sentObj, Object &receivedObj, Object::Kind awaitedKind = Object::Dummy ) const;
		bool ping() const;
	private:
		RF24 *m_rf24;
		const uint8_t *m_txPipe;
		const uint8_t *m_rxPipe;
		uint8_t m_channel;
		unsigned long m_timeOut;
		bool m_isReady;
};

//	----- inline functions -----
bool Tunnel::isReady() const {
	return m_isReady;
}
void Tunnel::setPALevel( uint8_t level ) {
	m_rf24->setPALevel( level );
}
unsigned long Tunnel::timeOut() const {
	return m_timeOut;
}
void Tunnel::setTimeOut( unsigned long timeOut ) {
	m_timeOut = timeOut;
}

}
#endif