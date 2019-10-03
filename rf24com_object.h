#ifndef __rf24com_object_H__
#define __rf24com_object_H__

#include <stdint.h>

namespace RF24Com
{

#define RF24COM_OBJECT_PAYLOADSIZE		16	//	Full payload size
#define RF24COM_OBJECT_DATASIZE			static_cast< uint8_t >( RF24COM_OBJECT_PAYLOADSIZE - 2 ) // Size fo children classes. (payload_size - kind - id)

class Object
{
	public:
		enum Kind
		{
			Dummy = 0,
			PingPong,
			Temperatures,		//	List of temperatures
			GPIOs,				//	List of general-purpose digital inputs-outputs
			//	Application's custom objects
			ApplicationObjects = 0x80
		} __attribute__( ( __packed__ ) ) ;

		Object( Kind kind = Dummy, uint8_t dummyBytes = 0 );

		inline Kind kind() const;
		inline void setKind( Kind kind );

		inline uint8_t id() const;
		inline void setId( uint8_t id );

		inline const uint8_t* data() const;
		inline uint8_t* dataPtr();
		inline uint8_t size() const;

		const Object& operator = ( const Object &object );
		const Object* operator = ( const Object *object );

#if defined( DEBUG )		
		virtual void printDetails() const;
#endif
	protected:
		template< class T > T* mapMember( T* &member );

	private:
		uint8_t *m_memberPtr;
		Kind *m_kind;
		uint8_t *m_Id;
		uint8_t m_data[ RF24COM_OBJECT_PAYLOADSIZE ];
};

//	----- inline functions -----
template< class T > T* Object::mapMember( T* &member )
{
	member = reinterpret_cast< T* >( m_memberPtr );
	m_memberPtr += sizeof( T );
	return member;
}
Object::Kind Object::kind() const 
{
	return *m_kind;
}
uint8_t Object::id() const 
{
	return *m_Id;
}
void Object::setId( uint8_t id ) 
{
	*m_Id = id;
}
const uint8_t* Object::data() const 
{
	return m_data;
}
uint8_t* Object::dataPtr() 
{
	return m_data;
}
uint8_t Object::size() const 
{
	return RF24COM_OBJECT_PAYLOADSIZE;
}
void Object::setKind( Kind kind ) 
{
	*m_kind = kind;
}

}

#endif