#ifndef __rf24com_object_H__
#define __rf24com_object_H__

#include <stdint.h>

namespace RF24Com
{

#define RF24COM_OBJECT_DATASIZE		16
#define RF24COM_OBJECT_KINDIDX		0
#define RF24COM_OBJECT_DATAIDX		sizeof( RF24Com::Object::Kind )

class Object
{
	public:
		enum Kind
		{
			Dummy = 0,
			Ping,
			Pong
		} __attribute__( ( __packed__ ) ) ;

		Object( Kind kind = Dummy );

		inline Kind kind() const;
		inline void setKind( Kind kind );
		inline const uint8_t* data() const;
		inline uint8_t* dataPtr();
		inline uint8_t size() const;

		const Object& operator = ( const Object &object );
		const Object* operator = ( const Object *object );
#if defined( DEBUG )		
		void printDetails() const;
#endif
	protected:
		template< class T > T* mapMember( T* &member );

	private:
		uint8_t *m_memberPtr;
		Kind *m_kind;
		uint8_t m_data[ RF24COM_OBJECT_DATASIZE ];
};

//	----- inline functions -----
template< class T > T* Object::mapMember( T* &member )
{
	member = reinterpret_cast< T* >( m_memberPtr );
	m_memberPtr += sizeof( T );
	return member;
}
Object::Kind Object::kind() const {
	return *m_kind;
}
const uint8_t* Object::data() const {
	return m_data;
}
uint8_t* Object::dataPtr() {
	return m_data;
}
uint8_t Object::size() const {
	return RF24COM_OBJECT_DATASIZE;
}
void Object::setKind( Kind kind ) {
	*m_kind = kind;
}

}

#endif