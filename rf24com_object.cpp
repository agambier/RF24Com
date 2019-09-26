#include "rf24com_object.h"
#include <string.h>
#include <Arduino.h>

namespace RF24Com
{

//
//
Object::Object( Kind kind ) :
	m_kind( nullptr )
{
	//	Affect pointers' addresses
	m_kind = reinterpret_cast< Kind*>( &m_data[ RF24COM_OBJECT_KINDIDX ] );
	setKind( kind );
}

//
//
const Object& Object::operator = ( const Object &object )
{
	//	Copy data but do not override the kind of object
	memcpy( &m_data[ RF24COM_OBJECT_DATAIDX ],
			&object.m_data[ RF24COM_OBJECT_DATAIDX ], 
			sizeof( m_data ) - RF24COM_OBJECT_DATAIDX );
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
	for( size_t i = 0; i < RF24COM_OBJECT_DATASIZE; i ++ )
	{
		Serial.print( m_data[ i ] );
		Serial.print( " " );
	}
	Serial.println();
}
#endif
}
