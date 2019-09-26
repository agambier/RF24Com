#include "rf24com_temperatures.h"
#include <string.h>

namespace RF24Com
{

//
//
Temperatures::Temperatures() :
	Object( Object::Temperatures ),
	m_activeMasks( mapMember< uint8_t >( m_activeMasks ) )
{
	*m_activeMasks = 0;
	for( uint8_t i = 0; i < RF24COM_TEMPERATURES_COUNT; i++ )
	{
		mapMember< int16_t >( m_temperatures[ i ] );
		setRawTemperature( i, 0 );
	}
}

//
//
bool Temperatures::isActive( uint8_t id ) const
{
	if( !isValidId( id ) ) 
		return false;

	return ( *m_activeMasks & ( 1 << id ) );
}

//
//
void Temperatures::setActive( uint8_t id, bool active )
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
int16_t Temperatures::rawTemperature( uint8_t id ) const
{
	if( !isValidId( id ) )
		return 0;

	return *m_temperatures[ id ];
}

//
//
void Temperatures::setRawTemperature( uint8_t id, int16_t value )
{
	if( isValidId( id ) )
		*m_temperatures[ id ] = value;
}

}
