#include "rf24com_gpios.h"

namespace RF24Com
{
	
//
//
GPIOs::GPIOs() :
	Object( Object::GPIOs, 2 ),	//	2 dummy bytes to align for pointers access
	m_activeMasks( mapMember< uint32_t >( m_activeMasks ) ),
	m_states( mapMember< uint32_t >( m_states ) )
{
	*m_activeMasks = 0;
	*m_states = 0;
}

//
//
bool GPIOs::isActive( uint8_t id ) const
{
	if( !isValidId( id ) ) 
		return false;

	return ( *m_activeMasks & ( 1 << id ) );
}

//
//
void GPIOs::setActive( uint8_t id, bool active )
{
	if( isValidId( id ) )
	{
		if( active )
			*m_activeMasks |= ( 1 << id );
		else
			*m_activeMasks &= ~( 1 << id );
	}
}

//
//
bool GPIOs::state( uint8_t id ) const
{
	if( !isValidId( id ) ) 
		return false;

	return ( *m_states & ( 1 << id ) );
}

//
//
void GPIOs::setState( uint8_t id, bool state )
{
	if( isValidId( id ) )
	{
		if( state )
			*m_states |= ( 1 << id );
		else
			*m_states &= ~( 1 << id );
	}
}

}
