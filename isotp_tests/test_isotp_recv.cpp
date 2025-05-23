#include "isotp.hpp"
#include <cassert>

uint32_t _arbitration_id = 0;
uint8_t _data[256] = {0};
uint8_t _size = 0;


class IsoTpTest : public IsoTp
{
public:
	IsoTpTest() : IsoTp() {}

	IsoTpRet user_send_can(
		const uint32_t arbitration_id,
		const uint8_t* data,
		const uint8_t size
	)
	{
		_arbitration_id = arbitration_id;
		_size = size;
		for (uint8_t i = 0; i < size; i++)
		{
			_data[i] = data[i];
		}
		// Custom send CAN implementation
		return IsoTpRet::OK;
	}
};

int main(void)
{
	uint16_t out_size = 0;
	IsoTpTest isotp;
	uint8_t send_buffer[1024];
	uint8_t recv_buffer[1024];
	isotp.init(
		0x123,
		send_buffer,
		sizeof(send_buffer),
		recv_buffer,
		sizeof(recv_buffer)
	);

	uint8_t diagSessReqExpected[] = {
		0x10, 0x03
	};

	uint8_t diagSessReq[] = {
		0x02, 0x10, 0x03, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc
	};

	isotp.on_can_message(diagSessReq, sizeof(diagSessReq));

	isotp.poll();
	isotp.receive(_data, sizeof(_data), &out_size);

	assert(out_size == sizeof(diagSessReqExpected));
	for (uint8_t i = 0; i < sizeof(diagSessReqExpected); i++)
	{
		assert(_data[i] == diagSessReqExpected[i]);
	}

	return 0;
}