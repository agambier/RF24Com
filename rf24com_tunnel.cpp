#include "rf24com_tunnel.h"

namespace RF24Com
{
//
//
Tunnel::Tunnel( RF24 &rf24, const uint8_t *txPipe, const uint8_t *rxPipe, uint8_t channel ) :
	m_rf24( &rf24 ),
	m_txPipe( txPipe ),
	m_rxPipe( rxPipe ),
	m_channel( channel ),
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
	m_rf24->setPayloadSize( RF24COM_OBJECT_DATASIZE );
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
	if( m_rf24->available() )
	{
		m_rf24->read( obj.dataPtr(), obj.size() );

		//	Process some core object ?
		if( Object::Ping == obj.kind() )
		{	//	Send pong back
			obj.setKind( Object::Pong );
			sendObject( obj );
		}
		else
			return true;	//	Got a object
	}

	//	Core object has been handled or no object received...
	return false;
}

//
//
bool Tunnel::ping() const
{
	//	Send ping...
	Object obj( Object::Ping );
	if( !sendObject( obj ) )
		return false;

	//	Wait for pong back
	unsigned long to = millis();
	bool result = false;
	do
	{
		if( ( result = getObject( obj ) ) )
			result = ( Object::Pong == obj.kind() );
	}
	while( !result && ( ( millis() - to ) < 500 ) );

	return result;
}

}