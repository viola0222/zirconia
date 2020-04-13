
#include "index.h"

#define _ESC			0x1b	// エスケープシーケンス
#define TRX_BUFFER_SIZE 64 		// 送受信バッファサイズ

struct {
    volatile uint16_t 	head;
    volatile uint16_t	tail;
    volatile uint16_t	remain;
    volatile uint8_t	data[TRX_BUFFER_SIZE];
} tx_buffer, rx_buffer; // FIFOバッファ

uint8_t			tx_data;
uint8_t			rx_data;

/* ---------------------------------------------------------------
	UART1で1文字受信する関数
--------------------------------------------------------------- */
uint8_t Communication_TerminalRecv( void )
{
	uint8_t data[1];
	HAL_UART_Receive( &huart1, (uint8_t*)data, sizeof(data), 1 );
	return (*data);
}

/* ---------------------------------------------------------------
	UART1で1文字送信する関数
--------------------------------------------------------------- */
void Communication_TxPushData( int8_t data )
{
// headに新しく追加する
// tailは次に送信されるデータを指す
// バッファに空きが無い（headがtailに追いついた）場合は待機する

	// バッファ内データ数をカウントし，空きがない場合待機する
	// バッファフルで待機しているときには割り込みを許可するためにwhileループになっている
	while(1) {
		// この関数は多重に実行されるとまずいので割り込みを禁止する
		__disable_irq();

		// DMAを一時的に停止
		HAL_UART_DMAStop(&huart1);

		// バッファに空きがあればループから抜ける
		if( tx_buffer.remain < TRX_BUFFER_SIZE ) {
			break;
		} else;

		// DMA動作再開
		HAL_UART_Transmit_DMA(&huart1, &tx_data, 1);

		// 割り込み許可
		__enable_irq();

		// バッファに空きができるまで待機（この間割り込みが発生してもよい）
		while(tx_buffer.remain == TRX_BUFFER_SIZE);
	}
	// ここの時点でDMACは停止，割り込みは禁止されている

	// 書き込みポインタにデータを格納
	tx_buffer.data[tx_buffer.head++] = data;
	tx_buffer.remain++;
	// 終端に来たら、先頭に戻る
	if(tx_buffer.head >= TRX_BUFFER_SIZE){
		tx_buffer.head = 0;
	} else;

	// DMA動作再開
	HAL_UART_Transmit_DMA(&huart1, &tx_data, 1);

	// 割り込み許可
	__enable_irq();
}

void Communication_TxPopData( void )
{
	// データがない場合
	if( tx_buffer.remain == 0 ) {
		// DMAを停止
		HAL_UART_DMAStop(&huart1);
	} else {
		// 読み出しデータの取り出し
		tx_data = tx_buffer.data[tx_buffer.tail++];
		tx_buffer.remain--;

		// 終端に来たら先頭に戻る
		if(tx_buffer.tail >= TRX_BUFFER_SIZE){
			tx_buffer.tail = 0;
		} else;

		// DMA動作再開
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
	printfとscanfを使用するための設定
--------------------------------------------------------------- */
void Communication_Initialize( void )
{
	setbuf(stdout, NULL);
	setbuf(stdin, NULL);
	setbuf(stderr, NULL);
}

/* ---------------------------------------------------------------
	printfを使用するための設定
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
	scanfを使用するための設定
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
