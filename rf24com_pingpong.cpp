#include "rf24com_pingpong.h"

namespace RF24Com
{

//
//
PingPong::PingPong( bool isPing, uint32_t key ) :
	Object( Object::PingPong, 1 ),
	m_config( mapMember< uint8_t >( m_config ) ),
	m_key( mapMember< uint32_t >( m_key ) )
{
	*m_config = 0;
	setPingPong( isPing );
	setKey( key );
}

//
//
void PingPong::setPingPong( bool isPing )
{
	if( isPing )
		*m_config |= ( 1 << PingPong::IsPing );
	else
		*m_config &= ~( 1 << PingPong::IsPing );
}

//
//
void PingPong::preparePong()
{
	//	already pong ?
	if( isPong() )
		return;

	setPong();
	setKey( ~key() );
}

}
