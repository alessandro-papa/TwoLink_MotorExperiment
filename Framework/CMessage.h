#ifndef CMESSAGE_H
#define CMESSAGE_H
#include "EEvent.h"

constexpr auto cMessageSize{128U};

class CMessage
{
public:
	EEvent getEvent() const;
	template<class DataType>
	const DataType& getData() const;
	template<class DataType>
	void setData(const DataType&);
public:
	CMessage();
	CMessage(const EEvent&);
	CMessage& operator=(const CMessage&) = default;
	CMessage(const CMessage&)            = default;
	~CMessage()                          = default;
private:
	EEvent mEvent;
	UInt8  mDataField[cMessageSize];
};

template<class DataType>
const DataType& CMessage::getData() const
{
	static_assert(sizeof(DataType) < cMessageSize,
                  "CMessage: Size of data type exceeds message size.");
    return *reinterpret_cast<const DataType*>(mDataField);
}
template<class DataType>
void CMessage::setData(const DataType& data)
{
	static_assert(sizeof(DataType) < cMessageSize,
              	  "CMessage: Size of data type exceeds message size.");

	*reinterpret_cast<DataType*>(mDataField) = data;
}

#endif
