#ifndef __rf24com_gpios_H__
#define __rf24com_gpios_H__

#include "rf24com_object.h"

namespace RF24Com
{

class GPIOs : public Object
{
	public:
		GPIOs();

		inline uint8_t count() const;

		bool isActive( uint8_t id ) const;
		void setActive( uint8_t id, bool active );

		bool state( uint8_t id ) const;
		void setState( uint8_t id, bool state );

	protected:
		inline bool isValidId( uint8_t id ) const;

	private:
		uint32_t *m_activeMasks;	//	List of active GPIOs
		uint32_t *m_states;			//	List of GPIOs' states (True/False)
};
//	----- inline functions -----
uint8_t GPIOs::count() const
{
	return 32;
}
bool GPIOs::isValidId( uint8_t id ) const 
{
	return ( id < count() );
}

}

#endif