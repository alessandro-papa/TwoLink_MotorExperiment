#include "AState.h"

CMessage AState::sInternalQueue{CMessage{EEvent::DefaultIgnore}};
UInt32   AState::sQueueSize{0U};
