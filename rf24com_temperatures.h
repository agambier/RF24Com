#ifndef __rf24com_temperatures_H__
#define __rf24com_temperatures_H__

#include "rf24com_object.h"

namespace RF24Com
{
#define RF24COM_TEMPERATURES_COUNT	7

class Temperatures : public Object
{
	public:
		Temperatures();

		bool isActive( uint8_t id ) const;
		void setActive( uint8_t id, bool active );

		int16_t rawTemperature( uint8_t id ) const;
		void setRawTemperature( uint8_t id, int16_t value );

		inline float temperature( uint8_t id ) const;
		inline void setTemperature( uint8_t id, float value );
	protected:
		inline bool isValidId( uint8_t id ) const;
	private:
		uint8_t *m_activedMasks;	//	Mask of enbaled temperatures
		int16_t *m_temperatures[ RF24COM_TEMPERATURES_COUNT ];
};
//	----- inline functions -----
bool Temperatures::isValidId( uint8_t id ) const
{
	return ( id < RF24COM_TEMPERATURES_COUNT );
}
float Temperatures::temperature( uint8_t id ) const
{
	return 0.01f * rawTemperature( id );
}
void Temperatures::setTemperature( uint8_t id, float value )
{
	setRawTemperature( id, 100 * value );
}

}

#endif