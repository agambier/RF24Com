#include "rf24com_tunnel.h"
#include "rf24com_pingpong.h"

namespace RF24Com
{
//
//
Tunnel::Tunnel( RF24 &rf24, const uint8_t *txPipe, const uint8_t *rxPipe, uint8_t channel ) :
	m_rf24( &rf24 ),
	m_txPipe( txPipe ),
	m_rxPipe( rxPipe ),
	m_channel( channel ),
	m_timeOut( 100 ),
	m_isReady( false )
{
	
}

//
//
bool Tunnel::begin()
{
	//	Initialize radio
	if( !m_rf24->begin() )
		return false;

	m_rf24->setPALevel( RF24_PA_MIN );	//	power level
	m_rf24->setDataRate( RF24_250KBPS );
	m_rf24->setChannel( m_channel );
	m_rf24->setAutoAck( true );	//	Auto ACK
	m_rf24->setRetries( 15, 15 );	//	15 retries every 4ms
	m_rf24->setPayloadSize( RF24COM_OBJECT_PAYLOADSIZE );
	m_rf24->openWritingPipe( m_txPipe );
	m_rf24->openReadingPipe( 1, m_rxPipe );

	m_isReady = m_rf24->isChipConnected();
	if( m_isReady )
		m_rf24->startListening();

	return m_isReady;
}

//
//
bool Tunnel::sendObject( const Object &obj ) const
{
	m_rf24->stopListening();
	bool result = m_rf24->write( obj.data(), obj.size() );
	m_rf24->startListening();
	return result;
}

//
//
bool Tunnel::getObject( Object &obj ) const
{
	bool result = false;
	if( m_rf24->available() )
	{
		result = true;
		m_rf24->read( obj.dataPtr(), obj.size() );

		//	Process some core object ?
		if( Object::PingPong == obj.kind() )
		{	//	Get ping object
			PingPong pingPong( true );
			*dynamic_cast< Object* >( &pingPong ) = obj;
			if( pingPong.isPing() )
			{	//	prepare and send pong
				pingPong.preparePong();
				sendObject( *dynamic_cast< Object* >( &pingPong ) );
				//	It was a core object dont give it to the user app layer
				result = false;				
			}
		}
	}

	//	Core object has been handled or no object received...
	return result;
}

//
//
bool Tunnel::sendAndReceive( const Object &sentObj, Object &receivedObj, Object::Kind awaitedKind ) const
{	
	//	tx
	if( !sendObject( sentObj ) )
		return false;

	//	Wait and filter
	unsigned long to = millis();
	bool result = false;
	do
	{
		if( ( result = getObject( receivedObj ) ) )
		{	//	filter it ?
			if( ( Object::Dummy != awaitedKind ) && ( receivedObj.kind() != awaitedKind ) )
				result = false;
		}
	}
	while( !result && ( ( millis() - to ) < timeOut() ) );
	return result;	
}

//
//
bool Tunnel::ping() const
{
	//	Send ping...and wait for pong !
	uint32_t key = millis();
	PingPong pingPong( true, key );
	if( !sendAndReceive( pingPong, pingPong, Object::PingPong ) )
		return false;

	return pingPong.isPong() &&	( ~key == pingPong.key() );
}

}