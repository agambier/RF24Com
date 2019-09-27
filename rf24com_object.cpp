#include "rf24com_object.h"
#include <string.h>
#include <Arduino.h>

namespace RF24Com
{

//
//
Object::Object( Kind kind, uint8_t dummyBytes ) :
	m_memberPtr( reinterpret_cast< uint8_t* >( &m_data[ 0 ] ) ),
	m_kind( mapMember< Kind >( m_kind ) ),
	m_Id( mapMember< uint8_t >( m_Id ) )
{
	//	map dummy bytes (to align members ?)...
	//	dummy bytes are not initialized with default values
	m_memberPtr += min( dummyBytes, RF24COM_OBJECT_DATASIZE );

	//	default values
	setKind( kind );
	setId( 0 );
}

//
//
const Object& Object::operator = ( const Object &object )
{
	//	Copy data but do not override the kind of object
	memcpy( m_data, object.m_data, RF24COM_OBJECT_PAYLOADSIZE ); 
	return *this;
}

//
//
const Object* Object::operator = ( const Object *object )
{
	if( object )
		*this = *object;
	return this;
}
#if defined( DEBUG )		
//
//
void Object::printDetails() const
{
	Serial.print( "Object(" ); Serial.println( ")" );
	Serial.print( "  kind : " ); Serial.println( kind() );
	Serial.print( "  data : " ); 
	for( size_t i = 0; i < RF24COM_OBJECT_PAYLOADSIZE; i ++ )
	{
		Serial.print( m_data[ i ] );
		Serial.print( " " );
	}
	Serial.println();
}
#endif
}
