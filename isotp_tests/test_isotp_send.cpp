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

	// diag sess pos response
	uint8_t diagSessPosResponse[] = {
		0x50, 0x03, 0x0b, 0xb8, 0x01, 0xf4
	};

	uint8_t diagSessPosResponseExpected[] = {
		0x06, 0x50, 0x03, 0x0b, 0xb8, 0x01, 0xf4
	};

	isotp.send(diagSessPosResponse, sizeof(diagSessPosResponse));

	// Check if the sent data matches the expected data
	assert(_arbitration_id == 0x123);
	assert(_size == sizeof(diagSessPosResponseExpected));
	for (uint8_t i = 0; i < sizeof(diagSessPosResponseExpected); i++)
	{
		assert(_data[i] == diagSessPosResponseExpected[i]);
	}
	

	return 0;
}