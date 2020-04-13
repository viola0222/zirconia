
#include "index.h"

#define _ESC			0x1b	// �G�X�P�[�v�V�[�P���X
#define TRX_BUFFER_SIZE 64 		// ����M�o�b�t�@�T�C�Y

struct {
    volatile uint16_t 	head;
    volatile uint16_t	tail;
    volatile uint16_t	remain;
    volatile uint8_t	data[TRX_BUFFER_SIZE];
} tx_buffer, rx_buffer; // FIFO�o�b�t�@

uint8_t			tx_data;
uint8_t			rx_data;

/* ---------------------------------------------------------------
	UART1��1������M����֐�
--------------------------------------------------------------- */
uint8_t Communication_TerminalRecv( void )
{
	uint8_t data[1];
	HAL_UART_Receive( &huart1, (uint8_t*)data, sizeof(data), 1 );
	return (*data);
}

/* ---------------------------------------------------------------
	UART1��1�������M����֐�
--------------------------------------------------------------- */
void Communication_TxPushData( int8_t data )
{
// head�ɐV�����ǉ�����
// tail�͎��ɑ��M�����f�[�^���w��
// �o�b�t�@�ɋ󂫂������ihead��tail�ɒǂ������j�ꍇ�͑ҋ@����

	// �o�b�t�@���f�[�^�����J�E���g���C�󂫂��Ȃ��ꍇ�ҋ@����
	// �o�b�t�@�t���őҋ@���Ă���Ƃ��ɂ͊��荞�݂������邽�߂�while���[�v�ɂȂ��Ă���
	while(1) {
		// ���̊֐��͑��d�Ɏ��s�����Ƃ܂����̂Ŋ��荞�݂��֎~����
		__disable_irq();

		// DMA���ꎞ�I�ɒ�~
		HAL_UART_DMAStop(&huart1);

		// �o�b�t�@�ɋ󂫂�����΃��[�v���甲����
		if( tx_buffer.remain < TRX_BUFFER_SIZE ) {
			break;
		} else;

		// DMA����ĊJ
		HAL_UART_Transmit_DMA(&huart1, &tx_data, 1);

		// ���荞�݋���
		__enable_irq();

		// �o�b�t�@�ɋ󂫂��ł���܂őҋ@�i���̊Ԋ��荞�݂��������Ă��悢�j
		while(tx_buffer.remain == TRX_BUFFER_SIZE);
	}
	// �����̎��_��DMAC�͒�~�C���荞�݂͋֎~����Ă���

	// �������݃|�C���^�Ƀf�[�^���i�[
	tx_buffer.data[tx_buffer.head++] = data;
	tx_buffer.remain++;
	// �I�[�ɗ�����A�擪�ɖ߂�
	if(tx_buffer.head >= TRX_BUFFER_SIZE){
		tx_buffer.head = 0;
	} else;

	// DMA����ĊJ
	HAL_UART_Transmit_DMA(&huart1, &tx_data, 1);

	// ���荞�݋���
	__enable_irq();
}

void Communication_TxPopData( void )
{
	// �f�[�^���Ȃ��ꍇ
	if( tx_buffer.remain == 0 ) {
		// DMA���~
		HAL_UART_DMAStop(&huart1);
	} else {
		// �ǂݏo���f�[�^�̎��o��
		tx_data = tx_buffer.data[tx_buffer.tail++];
		tx_buffer.remain--;

		// �I�[�ɗ�����擪�ɖ߂�
		if(tx_buffer.tail >= TRX_BUFFER_SIZE){
			tx_buffer.tail = 0;
		} else;

		// DMA����ĊJ
		HAL_UART_Transmit_DMA(&huart1, &tx_data, 1);
	}
}

void HAL_UART_TxCpltCallback( UART_HandleTypeDef *huart )
{
    if( huart->Instance == USART1 ) {
        Communication_TxPopData();
    }
}

/* ---------------------------------------------------------------
	printf��scanf���g�p���邽�߂̐ݒ�
--------------------------------------------------------------- */
void Communication_Initialize( void )
{
	setbuf(stdout, NULL);
	setbuf(stdin, NULL);
	setbuf(stderr, NULL);
}

/* ---------------------------------------------------------------
	printf���g�p���邽�߂̐ݒ�
--------------------------------------------------------------- */
#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
PUTCHAR_PROTOTYPE
{
	Communication_TxPushData(ch);
	return 1;
}

/* ---------------------------------------------------------------
	scanf���g�p���邽�߂̐ݒ�
--------------------------------------------------------------- */
#ifdef __GNUC__
#define GETCHAR_PROTOTYPE int __io_getchar(void)
#else
#define GETCHAR_PROTOTYPE int fgetc(FILE *f)
#endif /* __GNUC__ */
GETCHAR_PROTOTYPE
{
	return Communication_TerminalRecv();
}
