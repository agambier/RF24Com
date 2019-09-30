#ifndef __rf24com_pingpong_H__
#define __rf24com_pingpong_H__

#include "rf24com_object.h"

namespace RF24Com
{

class PingPong : public Object
{
	public:
		PingPong( bool isPing, uint32_t key = 0 );

		inline bool isPing() const;
		inline void setPing();

		inline bool isPong() const;
		inline void setPong();

		inline uint32_t key() const;

		void preparePong();
	protected:
		void setPingPong( bool isPing );

		inline void setKey( uint32_t key );

	private:
		enum ConfigBit
		{
			IsPing = 0,
		};

		uint8_t *m_config;	//	Config register
		uint32_t *m_key;
};
//	----- inline functions -----
bool PingPong::isPing() const
{
	return ( *m_config & ( 1 << PingPong::IsPing ) );
}
bool PingPong::isPong() const
{
	return !isPing();
}
void PingPong::setPing()
{
	setPingPong( true );
}
void PingPong::setPong()
{
	setPingPong( false );
}
uint32_t PingPong::key() const
{
	return *m_key;
}
void PingPong::setKey( uint32_t key )
{
	*m_key = key;
}

}

#endif