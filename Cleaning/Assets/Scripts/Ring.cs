using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Ring
{

    /*リングバッファ*/
    private const int BUFF_SIZE = 64;			//リングバッファの終端アドレス
    int[] buff = new int[BUFF_SIZE];
    int head;				//書込み時の書込みポイント
    int tail;				//読込み時の読込みポイント


    public Ring()
    {
        head = 0;
        tail = 0;
    }

    /*リングバッファ書き込み*/
    public void PutRingBuff(int x)
    {
        //Debug.Log(x.ToString("x"));
        buff[head] = x;

        if (head < BUFF_SIZE - 1)
        {
            head++;
        }
        else
        {
            head = 0;
        }
    }

    /*リングバッファ読み込み*/
    public int GetRingBuff()
    {
        int d = 0;

        if (tail != head)
        {
            d = buff[tail];
            if (tail < BUFF_SIZE - 1)
            {
                tail++;
            }
            else
            {
                tail = 0;
            }
        }
        else
        {
            d = -1;
        }

        return d;
    }
}
