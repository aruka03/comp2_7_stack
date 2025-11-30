#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーからほとんど使用されていない部分を除外する
#include "Windows.h"                    // Windows API の機能定義
#include <stdlib.h>

#include "../include/lib_func.h"


// mem_size の容量でスタック用のメモリを確保する
void initialize(STACK* s, size_t mem_size)
{
	if (s == NULL) return;

	// ToDo: mem_sizeでメモリを確保しよう
	s->stack_memory = (int*)malloc(mem_size);
	if (s->stack_memory == NULL) {//現在のスタックの位置
		s->stack_pointer = NULL;//スタック領域の先頭アドレス
		s->end = NULL;//最後に書ける要素の次
		return;
	}

	s->stack_pointer = s->stack_memory;
	s->end = (int*)((char*)s->stack_memory + mem_size);
}


// 確保したメモリを解放する
void finalize(STACK* s)
{
	if (s == NULL)return;
	if (s->stack_memory != NULL) {
		free(s->stack_memory);
		s->stack_pointer = NULL;
		s->stack_memory = NULL;
		s->end = NULL;
	}

	// ToDo: Initializeで確保したメモリを解放しよう
}


// valの値をスタックに積む。実行の成否を返す
bool push(STACK* s, int val)//1つづつ積んでいく
{
	// ToDo: valの値をスタックに保存しよう

	if (s == NULL || s->stack_memory == NULL) return false;//NULLの確認
	if (s->stack_pointer >= s->end)return false;//容量オーバー

	*(s->stack_pointer) = val;//今いるところに代入
	s->stack_pointer++;//ポインタを一つ進める

	return true;
}


// addrから始まるnum個の整数をスタックに積む。実行の成否を返す 配列
bool push_array(STACK* s, int* addr, int num)
{
	// ToDo: addrからはじまるnum個の整数をスタックに保存しよう

	if (s == NULL || s->stack_memory == NULL)return false;
	if (addr == NULL || num <= 0) return false;
	if (s->stack_pointer + num > s->end)return false;

	for (int i = 0; i < num; i++) {
		*(s->stack_pointer) = addr[i];
		s->stack_pointer++;
	}
	return true;
}

// スタックから一つの要素を取り出す
int pop(STACK* s)
{
	// ToDo: スタックの最上位の値を取り出して返そう
	// 不具合時は0を返す

	if (s == NULL || s->stack_memory == NULL)return 0;
	if (s->stack_pointer == s->stack_memory)return 0;

	s->stack_pointer--;
	return *(s->stack_pointer);//出した値を返す？

}

// addrにスタックからnumの要素を取り出す。取り出せた個数を返す
int pop_array(STACK* s, int* addr, int num)//ここがおかしそう
{
	// ToDo: スタックからnum個の値を取り出してaddrから始まるメモリに保存しよう
	// スタックにnum個の要素がたまっていなかったら、積まれている要素を返して、
	// 積んだ要素数を返り値として返そう

	//addr:取り出した値を格納する配列の先頭ポインタ
	//num:取り出したい要素数

	if (s == NULL || s->stack_memory == NULL) return 0;
	if (addr == NULL || num <= 0) return 0;//取り出す数が0以下なら失敗で0を返す

	int available = (int)(s->stack_pointer - s->stack_memory);//次に積む場所からmemory引いていま積まれている個数
	if (available <= 0) return 0;//スタックが空なら何もできない

	if (num > available) num = available;//取り出したい数が積まれている数より多いときはあるだけ出す

	for (int i = 0; i < num; i++) {
		s->stack_pointer--;             //スタックの先頭を1つ前の戻す
		addr[num-1-i] = *(s->stack_pointer);  //その位置の値を配列に格納
	}

	return num;//取り出せら個数かえす
}