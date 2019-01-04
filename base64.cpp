#include <cstring>
#include <iostream>
#include "base64.h"
using namespace std;
/*
* @param str��ŵ��Ǽ���ǰ�����ġ�
* @param�����������Ϊ���ز�����str����base64���ܺ���ַ����ŵ�outPutStr�С�
* 
*
*/
char data[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

void base64Encode(char *str,char *outPutStr)
{
	int		len = strlen(str);
	int		loopNum;//ѭ������
	int		tempCnt = 0;
	int		index;
	int		i;
	if(len%3==0)
	{
		loopNum = len;
	}
	else if(len%3==1)
	{
		loopNum = len - 1; 
	}
	else
	{
		loopNum = len - 2;
	}
	/** ѭ��loopNum�� */
	for(i=0; i<loopNum; i+=3)
	{
		/** ����λ���ı�Ϊ4λ��Base64���� */
		//��һ������
		outPutStr[tempCnt++] = data[str[i]>>2];
		//�ڶ�������,��һ���ַ��ĺ���λ��ڶ����ַ���ǰ��λ
		index = (str[i]&0x03)<<4;
		index = index|(str[i+1]>>4);
		outPutStr[tempCnt++] = data[index];

		//����������
		index = (str[i+1]&0x0f)<<2;
		index = index|((str[i+2]&0xc0)>>6);
		outPutStr[tempCnt++] = data[index];

		//���ĸ�����
		index = str[i+2]&0x3f;
		outPutStr[tempCnt++] = data[index];
	}
	if(len%3 == 1)
	{//ԭ�ĳ���%3=1.
		outPutStr[tempCnt++] = data[str[loopNum]>>2];
		index = str[loopNum]&0x03;
		index = index<<4;
		outPutStr[tempCnt++] = data[index];
		outPutStr[tempCnt++] = '=';
		outPutStr[tempCnt++] = '=';
	}
	else if(len%3 == 2)
	{
		outPutStr[tempCnt++] = data[str[loopNum]>>2];
		index = (str[loopNum]&0x03)<<4;
		index = index|(str[loopNum+1]>>4);
		outPutStr[tempCnt++] = data[index];

		index = str[loopNum+1]&0x0f;
		index = index<<2;
		outPutStr[tempCnt++] = data[index];
		outPutStr[tempCnt++] = '=';
	}
	outPutStr[tempCnt] = '\0';
	i = i + 3;
}
/*
* @param str��ŵ��ǽ���ǰ�����ġ�
* @param�����������Ϊ���ز�����str����base64���ܺ���ַ����ŵ�outPutStr�С�
* outPutStr��Ҫ����Base64�е�free_memory(char *p)�ͷ��ڴ�
*
*/
void base64Decode(char *str,char *outPutStr)
{
	int len = strlen(str);
	int i = 0;
	int	cnt = 0;
	int arr[4];
	int temp;
	
	for(i=0; i<len; i+=4)
	{
		/*** ���ݼ��ܺ��ַ���ԭ���Ӧ��"�±�ֵ" **/
		arr[0] = GetIndex(str[i]);
		arr[1] = GetIndex(str[i+1]);
		if(str[i+2] == '=')
			break;
		arr[2] = GetIndex(str[i+2]);
		if(str[i+3] == '=')
			break;
		arr[3] = GetIndex(str[i+3]);
		/*** END **/

		temp = (arr[0]<<2) | (arr[1]>>4);
		outPutStr[cnt++] = temp;//��һ���ַ�
		temp = (arr[1]&0x0f);
		temp = temp << 4;
		temp = temp | (arr[2]>>2);
		outPutStr[cnt++] = temp;
		temp = arr[2]&0x03;
		temp = temp << 6;
		temp = temp | (arr[3]&0x3f);
		outPutStr[cnt++] = temp;
	}
	if(str[i+2] == '=')
	{
		temp = (arr[0]<<2) | (arr[1]>>4);
		outPutStr[cnt++] = temp;
		temp = arr[1]&0x0f;
		temp = temp<<4;
	}
	else if(str[i+3] == '=')
	{
		temp = (arr[0]<<2) | (arr[1]>>4);
		outPutStr[cnt++] = temp;
		temp = arr[1]&0x0f;
		temp = temp<<4;
		temp = temp | (arr[2]>>2);
		outPutStr[cnt++] = temp;
	}
	outPutStr[cnt] = '\0';
}

/*** �ҵ����ܺ���ַ����ڵ��±�ֵ ***/
int GetIndex(char c)
{
	int i=0;
	for(i=0; i<strlen(data); i++)
	{
		if(data[i] == c)
		{
			return i;
		}
	}
	return -1;
}