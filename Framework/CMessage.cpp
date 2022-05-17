#include "CMessage.h"

CMessage::CMessage() : mEvent{EEvent::DefaultIgnore},
                       mDataField{0U}
{

}
CMessage::CMessage(const EEvent& event) : mEvent(event),
		                                  mDataField{0U}
{

}
EEvent CMessage::getEvent() const
{
	return mEvent;
}
